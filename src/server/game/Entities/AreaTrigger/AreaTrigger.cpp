/*
 * Copyright (C) 2011-2014 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2014 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ObjectAccessor.h"
#include "GridNotifiersImpl.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "Unit.h"
#include "SpellInfo.h"
#include "Log.h"
#include "AreaTrigger.h"

AreaTrigger::AreaTrigger() : WorldObject(false), _duration(0), m_caster(NULL), m_visualRadius(0.0f)
{
    m_objectType |= TYPEMASK_AREATRIGGER;
    m_objectTypeId = TYPEID_AREATRIGGER;

    m_updateFlag = UPDATEFLAG_STATIONARY_POSITION;

    m_valuesCount = AREATRIGGER_END;
}

AreaTrigger::~AreaTrigger()
{
    ASSERT(!m_caster);
}

void AreaTrigger::AddToWorld()
{
    ///- Register the AreaTrigger for guid lookup and for caster
    if (!IsInWorld())
    {
        sObjectAccessor->AddObject(this);
        WorldObject::AddToWorld();
        BindToCaster();
    }
}

void AreaTrigger::RemoveFromWorld()
{
    ///- Remove the AreaTrigger from the accessor and from all lists of objects in world
    if (IsInWorld())
    {
        UnbindFromCaster();
        WorldObject::RemoveFromWorld();
        sObjectAccessor->RemoveObject(this);
    }
}

bool AreaTrigger::CreateAreaTrigger(uint32 guidlow, uint32 triggerEntry, Unit* caster, SpellInfo const* spell, Position const& pos)
{
    SetMap(caster->GetMap());
    Relocate(pos);
    if (!IsPositionValid())
    {
        sLog->outError("misc", "AreaTrigger (spell %u) not created. Invalid coordinates (X: %f Y: %f)", spell->Id, GetPositionX(), GetPositionY());
        return false;
    }

    WorldObject::_Create(guidlow, HIGHGUID_AREATRIGGER, caster->GetPhaseMask());

    SetEntry(triggerEntry);
    SetDuration(spell->GetDuration());
    SetObjectScale(1);

    SetUInt64Value(AREATRIGGER_FIELD_CASTER, caster->GetGUID());
    SetUInt32Value(AREATRIGGER_FIELD_SPELL_ID, spell->Id);
    SetUInt32Value(AREATRIGGER_FIELD_SPELL_VISUAL_ID, spell->SpellVisual[0]);
    SetUInt32Value(AREATRIGGER_FIELD_DURATION, spell->GetDuration());
    SetUInt32Value(AREATRIGGER_FIELD_EXPLICIT_SCALE, 1);

    // TODO: Find a better place for this
    switch (spell->Id)
    {
        case 116011: // Rune of Power
            SetVisualRadius(3.5f);
            break;
    }

    if (!GetMap()->AddToMap(this))
        return false;

    return true;
}

void AreaTrigger::Update(uint32 p_time)
{
    if (GetDuration() > int32(p_time))
        _duration -= p_time;
    else
        Remove(); // expired

    WorldObject::Update(p_time);

    // TODO: Find a better place for this

    SpellInfo const* m_spellInfo = sSpellMgr->GetSpellInfo(GetUInt32Value(AREATRIGGER_FIELD_SPELL_ID));
    if (!m_spellInfo)
        return;

    if (!GetCaster())
    {
        Remove();
        return;
    }

    Unit* caster = GetCaster();
    float radius = 0.0f;

    switch (m_spellInfo->Id)
    {
        case 116011: // Rune of Power
        {
            std::list<Unit*> targetList;
            bool affected = false;
            radius = 2.25f;

            Trinity::AnyFriendlyUnitInRangeCheck u_check(caster, radius);
            Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInRangeCheck> searcher(caster, targetList, u_check);
            caster->VisitNearbyObject(radius, searcher);

            if (!targetList.empty())
            {
                for (auto itr : targetList)
                {
                    if (/*itr->GetGUID() == caster->GetGUID() ||*/ itr->GetEntry() == 60199 && itr->GetOwnerGUID() == caster->GetGUID())
                    {
                        affected = true;

                        if (!caster->HasAura(116014))
                            caster->CastSpell(caster, 116014, true);

                        return;
                    }
                }
            }

            if (!affected && caster->HasAura(116014))
                caster->RemoveAura(116014);

            break;
        }
    }
}

void AreaTrigger::Remove()
{
    if (IsInWorld())
    {
        // TODO: Find a better place for this
        SpellInfo const* m_spellInfo = sSpellMgr->GetSpellInfo(GetUInt32Value(AREATRIGGER_FIELD_SPELL_ID));
        if (!m_spellInfo)
            return;

        switch (m_spellInfo->Id)
        {
            case 116011: // Rune of Power : Remove the buff if caster is still in radius
                if (m_caster && m_caster->HasAura(116014))
                    m_caster->RemoveAura(116014);
                break;
        }

        SendObjectDeSpawnAnim(GetGUID());
        RemoveFromWorld();
        AddObjectToRemoveList();
    }
}

void AreaTrigger::BindToCaster()
{
    m_caster = ObjectAccessor::GetUnit(*this, GetCasterGUID());
    if (m_caster)
        m_caster->_RegisterAreaTrigger(this);
}

void AreaTrigger::UnbindFromCaster()
{
    ASSERT(m_caster);
    m_caster->_UnregisterAreaTrigger(this);
    m_caster = NULL;
}