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

/*
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "npc_pet_mag_".
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "CombatAI.h"
#include "Pet.h"

enum MageSpells
{
    SPELL_MAGE_CLONE_ME                 = 45204,
    SPELL_MAGE_MASTERS_THREAT_LIST      = 58838,
    SPELL_MAGE_FROZEN_ORB_VISUAL        = 123605,
    SPELL_MAGE_FROZEN_ORB_PERIODIC_AURA = 84717,
    SPELL_MAGE_FROZEN_ORB_VISUAL_DMG    = 113162,
    SPELL_MAGE_FROZEN_ORB_DMG           = 84721,
    SPELL_MAGE_FROZEN_ORB_SELF_SNARE    = 82736,
    SPELL_MAGE_FINGERS_OF_FROST         = 44544
};

class npc_pet_mage_mirror_image : public CreatureScript
{
public:
    npc_pet_mage_mirror_image() : CreatureScript("npc_pet_mage_mirror_image") { }

    struct npc_pet_mage_mirror_imageAI : CasterAI
    {
        npc_pet_mage_mirror_imageAI(Creature* creature) : CasterAI(creature) { }

        void InitializeAI() override
        {
            CasterAI::InitializeAI();
            Unit* owner = me->GetOwner();
            if (!owner)
                return;
            // Inherit Master's Threat List (not yet implemented)
            owner->CastSpell((Unit*) NULL, SPELL_MAGE_MASTERS_THREAT_LIST, true);
            // here mirror image casts on summoner spell (not present in client dbc) 49866
            // here should be auras (not present in client dbc): 35657, 35658, 35659, 35660 selfcasted by mirror images (stats related?)
            // Clone Me!
            owner->CastSpell(me, SPELL_MAGE_CLONE_ME, false);
        }

        // Do not reload Creature templates on evade mode enter - prevent visual lost
        void EnterEvadeMode() override
        {
            if (me->IsInEvadeMode() || !me->IsAlive())
                return;

            Unit* owner = me->GetCharmerOrOwner();

            me->CombatStop(true);
            if (owner && !me->HasUnitState(UNIT_STATE_FOLLOW))
            {
                me->GetMotionMaster()->Clear(false);
                me->GetMotionMaster()->MoveFollow(owner, PET_FOLLOW_DIST, me->GetFollowAngle(), MOTION_SLOT_ACTIVE);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_pet_mage_mirror_imageAI(creature);
    }
};

class npc_mage_frozen_orb : public CreatureScript
{
public:
    npc_mage_frozen_orb() : CreatureScript("npc_mage_frozen_orb") { }

    struct npc_mage_frozen_orbAI : public ScriptedAI
    {
        npc_mage_frozen_orbAI(Creature *creature) : ScriptedAI(creature)
        {
            summoner = me->ToTempSummon()->GetSummoner();
            x = me->GetPositionX();
            y = me->GetPositionY();
            z = summoner->GetPositionZ() + 2;
            o = me->GetOrientation();
            me->NearTeleportTo(x, y, z, o, true);
            angle = summoner->GetAngle(me);
            newx = me->GetPositionX() + 200 * cos(angle);
            newy = me->GetPositionY() + 200 * sin(angle);
            CombatCheck = false;
            DamageTimer = 1000;
        }

        float x, y, z, o, newx, newy, angle;
        bool CombatCheck;
        Unit* summoner;
        uint32 DamageTimer;

        void EnterCombat(Unit* /*target*/) override
        {
            me->CastSpell(me, SPELL_MAGE_FROZEN_ORB_SELF_SNARE, true);
            summoner->CastSpell(summoner, SPELL_MAGE_FINGERS_OF_FROST, true);
            CombatCheck = true;
        }

        void Reset() override
        {
            me->AddUnitMovementFlag(MOVEMENTFLAG_SPLINE_ELEVATION);
            me->CastSpell(me, SPELL_MAGE_FROZEN_ORB_VISUAL, true);
            me->CastSpell(me, SPELL_MAGE_FROZEN_ORB_PERIODIC_AURA, true);
            me->GetMotionMaster()->MovePoint(0, newx, newy, z);
        }

        void MoveInLineOfSight(Unit* /*who*/) override { }

        void EnterEvadeMode() override { }

        void UpdateAI(uint32 diff) override
        {
            if (DamageTimer <= diff)
            {
                if (summoner)
                    summoner->CastSpell(me, SPELL_MAGE_FROZEN_ORB_DMG, true);

                if (CombatCheck)
                    me->CastSpell(me, SPELL_MAGE_FROZEN_ORB_VISUAL_DMG, true);

                DamageTimer = 1000;
            }
            else
                DamageTimer -= diff;


            if (!CombatCheck)
            {
                if (Unit* target = me->SelectNearestTarget(10))
                    AttackStart(target);
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        if (!creature->ToTempSummon())
            return NULL;
        return new npc_mage_frozen_orbAI(creature);
    }
};

void AddSC_mage_pet_scripts()
{
    new npc_pet_mage_mirror_image();
    new npc_mage_frozen_orb();
}
