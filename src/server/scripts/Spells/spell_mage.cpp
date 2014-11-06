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
 * Scripts for spells with SPELLFAMILY_MAGE and SPELLFAMILY_GENERIC spells used by mage players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_mage_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Pet.h"

enum MageSpells
{
    SPELL_MAGE_CONJURE_REFRESHMENT_TABLE_R1 = 120056,
    SPELL_MAGE_CONJURE_REFRESHMENT_TABLE_R2 = 120055,
    SPELL_MAGE_CONJURE_REFRESHMENT_TABLE_R3 = 120054,
    SPELL_MAGE_CONJURE_REFRESHMENT_TABLE_R4 = 120053,
    SPELL_MAGE_CAUTERIZE_DAMAGE             = 87023,
    SPELL_MAGE_CAUTERIZED                   = 87024,
    SPELL_MAGE_TEMPORAL_RIPPLES             = 115611,
    SPELL_MAGE_RING_OF_FROST_FREEZE         = 82691,
    SPELL_MAGE_RING_OF_FROST_SUMMON         = 113724,
    SPELL_MAGE_RING_OF_FROST_IMUNITY        = 91264,
    SPELL_MAGE_RING_OF_FROST_INSTANT        = 140384,
    SPELL_MAGE_PRESENCE_OF_MIND             = 12043,
    SPELL_MAGE_MASTERY_ICICLES              = 76613,
    SPELL_MAGE_FINGERS_OF_FROST_PROC        = 44544,
    SPELL_MAGE_FINGERS_OF_FROST             = 112965,
    SPELL_MAGE_FINGERS_OF_FROST_VISUAL      = 126084,
    SPELL_MAGE_ICE_LANCE                    = 30455,
    SPELL_MAGE_COMBUSTION_DOT               = 83853,
    SPELL_MAGE_COMBUSTION_IMPACT            = 118271,
    SPELL_MAGE_INFERNO_BLAST                = 108853,
    SPELL_MAGE_INFERNO_BLAST_IMPACT         = 118280,
    SPELL_MAGE_LIVING_BOMB_TRIGGERED        = 44461,
    SPELL_MAGE_BRAIN_FREEZE                 = 44549,
    SPELL_MAGE_BRAIN_FREEZE_TRIGGERED       = 57761,
    SPELL_MAGE_IGNITE                       = 12654,
    SPELL_MAGE_MASTERY_IGNITE               = 12846,
    SPELL_MAGE_FROSTBOLT                    = 116,
    SPELL_MAGE_FROSTFIRE_BOLT               = 44614,
    SPELL_MAGE_ICICLE_STORE_1               = 148012,
    SPELL_MAGE_ICICLE_STORE_2               = 148013,
    SPELL_MAGE_ICICLE_STORE_3               = 148014,
    SPELL_MAGE_ICICLE_STORE_4               = 148015,
    SPELL_MAGE_ICICLE_STORE_5               = 148016,
    SPELL_MAGE_ICICLE_1                     = 148017,
    SPELL_MAGE_ICICLE_2                     = 148018,
    SPELL_MAGE_ICICLE_3                     = 148019,
    SPELL_MAGE_ICICLE_4                     = 148020,
    SPELL_MAGE_ICICLE_5                     = 148021,
    SPELL_MAGE_ICICLE_DMG                   = 148022,
    SPELL_MAGE_ICICLE_TRIGGER               = 148023,
    SPELL_MAGE_FROSTBOLT_HEAL               = 134660
};

enum MageIcons
{
    ICON_MAGE_SHATTER                            = 976,
    ICON_MAGE_IMPROVED_FLAMESTRIKE               = 37,
    ICON_MAGE_IMPROVED_FREEZE                    = 94,
    ICON_MAGE_INCANTER_S_ABSORPTION              = 2941,
    ICON_MAGE_IMPROVED_MANA_GEM                  = 1036
};

enum MageMinions
{
    PET_MAGE_WATER_ELEMENTAL                    = 510
};

enum MiscSpells
{
    SPELL_PRIEST_SHADOW_WORD_DEATH                  = 32409
};

// 42955 Conjure Refreshment
struct ConjureRefreshmentData
{
    uint32 minLevel;
    uint32 maxLevel;
    uint32 spellId;
};

uint8 const MAX_CONJURE_REFRESHMENT_SPELLS = 8;
ConjureRefreshmentData const _conjureData[MAX_CONJURE_REFRESHMENT_SPELLS] =
{
    { 33, 43, 92739 },
    { 44, 53, 92799 },
    { 54, 63, 92802 },
    { 64, 73, 92805 },
    { 74, 79, 74625 },
    { 80, 84, 92822 },
    { 85, 89, 92727 },
    { 90, 90, 116130 }
};

class spell_mage_conjure_refreshment : public SpellScriptLoader
{
public:
    spell_mage_conjure_refreshment() : SpellScriptLoader("spell_mage_conjure_refreshment") { }

    class spell_mage_conjure_refreshment_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_conjure_refreshment_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            for (uint8 i = 0; i < MAX_CONJURE_REFRESHMENT_SPELLS; ++i)
                if (!sSpellMgr->GetSpellInfo(_conjureData[i].spellId))
                    return false;
            return true;
        }

        bool Load() override
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;
            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            uint8 level = GetHitUnit()->getLevel();
            for (uint8 i = 0; i < MAX_CONJURE_REFRESHMENT_SPELLS; ++i)
            {
                ConjureRefreshmentData const& spellData = _conjureData[i];
                if (level < spellData.minLevel || level > spellData.maxLevel)
                    continue;
                GetHitUnit()->CastSpell(GetHitUnit(), spellData.spellId);
                break;
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_mage_conjure_refreshment_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_mage_conjure_refreshment_SpellScript();
    }
};

class spell_mage_conjure_refreshment_table : public SpellScriptLoader
{
public:
    spell_mage_conjure_refreshment_table() : SpellScriptLoader("spell_mage_conjure_refreshment_table") { }

    class spell_mage_conjure_refreshment_table_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_conjure_refreshment_table_SpellScript);

        void HandleBeforeCast()
        {
            Unit* caster = GetCaster();
            if (caster->getLevel() < 80)
                caster->CastSpell(caster, SPELL_MAGE_CONJURE_REFRESHMENT_TABLE_R1, true);
            else if (caster->getLevel() < 85)
                caster->CastSpell(caster, SPELL_MAGE_CONJURE_REFRESHMENT_TABLE_R2, true);
            else if (caster->getLevel() < 90)
                caster->CastSpell(caster, SPELL_MAGE_CONJURE_REFRESHMENT_TABLE_R3, true);
            else
                caster->CastSpell(caster, SPELL_MAGE_CONJURE_REFRESHMENT_TABLE_R4, true);
        }

        void Register() override
        {
            // Before cast because of shared cooldown between triggering and casted spells
            BeforeCast += SpellCastFn(spell_mage_conjure_refreshment_table_SpellScript::HandleBeforeCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_mage_conjure_refreshment_table_SpellScript();
    }
};

class spell_mage_cauterize : public SpellScriptLoader
{
public:
    spell_mage_cauterize() : SpellScriptLoader("spell_mage_cauterize") { }

    class spell_mage_cauterize_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_cauterize_AuraScript);

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_CAUTERIZE_DAMAGE))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_CAUTERIZED))
                return false;
            return true;
        }

        bool Load() override
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;
            return true;
        }

        void Absorb(AuraEffect* aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount)
        {
            Unit * caster = GetCaster();

            if (!caster)
                return;

            absorbAmount = 0;

            if (caster->ToPlayer()->HasAura(SPELL_MAGE_CAUTERIZED))
                return;

            int32 remainingHealth = caster->GetHealth() - dmgInfo.GetDamage();

            if (remainingHealth <= 0)
            {
                absorbAmount = dmgInfo.GetDamage();
                int32 cauterizeHeal = caster->CountPctFromMaxHealth(50) - caster->GetHealth();
                caster->CastCustomSpell(caster, SPELL_MAGE_CAUTERIZE_DAMAGE, NULL, &cauterizeHeal, NULL, true, NULL, aurEff);
                caster->CastSpell(caster, SPELL_MAGE_CAUTERIZED, true);
            }
        }

        void Register() override
        {
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_mage_cauterize_AuraScript::Absorb, EFFECT_0);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_mage_cauterize_AuraScript();
    }
};

class spell_mage_ice_barrier : public SpellScriptLoader
{
public:
    spell_mage_ice_barrier() : SpellScriptLoader("spell_mage_ice_barrier") { }

    class spell_mage_ice_barrier_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_ice_barrier_AuraScript);

        void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
        {
            canBeRecalculated = false;
            if (Unit* caster = GetCaster())
            {
                int32 sp = caster->SpellBaseDamageBonusDone(GetSpellInfo()->GetSchoolMask());
                sp *= 3.3;
                amount += sp;
            }
        }

        void Register() override
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_ice_barrier_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_mage_ice_barrier_AuraScript();
    }
};

class spell_mage_temporal_shield : public SpellScriptLoader
{
public:
    spell_mage_temporal_shield() :SpellScriptLoader("spell_mage_temporal_shield") { }

    class spell_mage_temporal_shield_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_temporal_shield_AuraScript);

        int32 damagetaken = 0;

        bool Validate(SpellInfo const* /*spellEntry*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_TEMPORAL_RIPPLES))
                return false;
            return true;
        }

        void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
        {
            PreventDefaultAction();

            damagetaken += eventInfo.GetDamageInfo()->GetDamage();
        }

        void AfterRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* owner = GetUnitOwner())
            {
                if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_EXPIRE)
                    return;

                damagetaken = damagetaken / 3 - (owner->getLevel() - 1); //Because of dbc BasePoints
                owner->CastCustomSpell(owner, SPELL_MAGE_TEMPORAL_RIPPLES, &damagetaken, NULL, NULL, true, NULL, aurEff);
            }
        }

        void Register() override
        {
            OnEffectProc += AuraEffectProcFn(spell_mage_temporal_shield_AuraScript::HandleProc, EFFECT_1, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN);
            OnEffectRemove += AuraEffectRemoveFn(spell_mage_temporal_shield_AuraScript::AfterRemove, EFFECT_1, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_mage_temporal_shield_AuraScript();
    }
};

class spell_mage_flameglow : public SpellScriptLoader
{
public:
    spell_mage_flameglow() : SpellScriptLoader("spell_mage_flameglow") { }

    class spell_mage_flameglow_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_flameglow_AuraScript);

        bool Load() override
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;
            return true;
        }

        void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& canBeRecalculated)
        {
            amount = -1;
        }

        void Absorb(AuraEffect* aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount)
        {
            Unit* caster = GetCaster();

            if (!caster)
                return;

            uint32 fullabsorb = caster->SpellBaseDamageBonusDone(GetSpellInfo()->GetSchoolMask()) * GetSpellInfo()->Effects[1].BasePoints / 100;

            absorbAmount = (fullabsorb <= dmgInfo.GetDamage()*GetSpellInfo()->Effects[2].BasePoints / 100) ? fullabsorb : dmgInfo.GetDamage()*GetSpellInfo()->Effects[2].BasePoints / 100;

        }

        void Register() override
        {
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_mage_flameglow_AuraScript::Absorb, EFFECT_0);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_mage_flameglow_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_mage_flameglow_AuraScript();
    }
};

class CastRingOfFrostInstant : public BasicEvent
{
public:
    CastRingOfFrostInstant(Unit* caster, float x, float y, float z) : _caster(caster), _x(x), _y(y), _z(z) { };

    bool Execute(uint64 e_time, uint32 p_time)
    {
        if (_caster->IsAlive())
            _caster->CastSpell(_x, _y, _z, SPELL_MAGE_RING_OF_FROST_INSTANT, true);
        return true;
    }

private:
    Unit* _caster;
    float _x, _y, _z;
};

class spell_mage_ring_of_frost_instant : public SpellScriptLoader
{
public:
    spell_mage_ring_of_frost_instant() : SpellScriptLoader("spell_mage_ring_of_frost_instant") { }

    class spell_mage_ring_of_frost_instant_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_ring_of_frost_instant_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_RING_OF_FROST_INSTANT))
                return false;
            return true;
        }

        bool Load() override
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;
            return true;
        }

        void HandleOnCast()
        {
            if (GetCaster()->HasAura(SPELL_MAGE_PRESENCE_OF_MIND))
                GetCaster()->RemoveAura(SPELL_MAGE_PRESENCE_OF_MIND);
        }

        void HandleAfterCast()
        {
            int32 casttime = sSpellMgr->GetSpellInfo(SPELL_MAGE_RING_OF_FROST_SUMMON)->CastTimeEntry->CastTime;
            GetCaster()->ModSpellCastTime(sSpellMgr->GetSpellInfo(SPELL_MAGE_RING_OF_FROST_SUMMON), casttime);

            WorldLocation const* loc = GetExplTargetDest();

            if (!loc)
                return;

            float x, y, z;
            loc->GetPosition(x, y, z);
            GetCaster()->m_Events.AddEvent(new CastRingOfFrostInstant(GetCaster(), x, y, z), GetCaster()->m_Events.CalculateTime(casttime));
        }

        void Register() override
        {
            AfterCast += SpellCastFn(spell_mage_ring_of_frost_instant_SpellScript::HandleAfterCast);
            OnCast += SpellCastFn(spell_mage_ring_of_frost_instant_SpellScript::HandleOnCast);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_mage_ring_of_frost_instant_SpellScript();
    }
};

class spell_mage_ring_of_frost_periodic : public SpellScriptLoader
{
public:
    spell_mage_ring_of_frost_periodic() : SpellScriptLoader("spell_mage_ring_of_frost_periodic") { }

    class spell_mage_ring_of_frost_periodic_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_ring_of_frost_periodic_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_RING_OF_FROST_FREEZE))
                return false;
            return true;
        }

        bool Load() override
        {
            ringOfFrost = NULL;
            return true;
        }

        void HandleEffectPeriodic(AuraEffect const* /*aurEff*/)
        {

            if (!ringOfFrost)
            {
                std::list<Creature*> MinionList;
                GetTarget()->GetAllMinionsByEntry(MinionList, sSpellMgr->GetSpellInfo(SPELL_MAGE_RING_OF_FROST_SUMMON)->Effects[EFFECT_0].MiscValue);

                // Get the last summoned RoF, save it and despawn older ones
                for (std::list<Creature*>::iterator itr = MinionList.begin(); itr != MinionList.end(); itr++)
                {
                    TempSummon* summon = (*itr)->ToTempSummon();

                    if (ringOfFrost && summon)
                    {
                        if (summon->GetTimer() > ringOfFrost->GetTimer())
                        {
                            ringOfFrost->DespawnOrUnsummon();
                            ringOfFrost = summon;
                        }
                        else
                            summon->DespawnOrUnsummon();
                    }
                    else if (summon)
                        ringOfFrost = summon;
                }
            }

            GetTarget()->CastSpell(ringOfFrost->GetPositionX(), ringOfFrost->GetPositionY(), ringOfFrost->GetPositionZ(), SPELL_MAGE_RING_OF_FROST_FREEZE, true);
        }

        TempSummon* ringOfFrost;

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_mage_ring_of_frost_periodic_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_mage_ring_of_frost_periodic_AuraScript();
    }
};

class spell_mage_ring_of_frost_freeze : public SpellScriptLoader
{
public:
    spell_mage_ring_of_frost_freeze() : SpellScriptLoader("spell_mage_ring_of_frost_freeze") { }

    class spell_mage_ring_of_frost_freeze_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_ring_of_frost_freeze_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_RING_OF_FROST_SUMMON))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_RING_OF_FROST_FREEZE))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_RING_OF_FROST_IMUNITY))
                return false;
            return true;
        }

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            float outRadius = 6.7f;
            float inRadius = 3.7f;

            targets.remove_if([&](WorldObject* target)
            {
                if (Unit* unit = target->ToUnit())
                    return unit->HasAura(SPELL_MAGE_RING_OF_FROST_IMUNITY) || unit->HasAura(SPELL_MAGE_RING_OF_FROST_FREEZE) || unit->GetExactDist(GetExplTargetDest()) > outRadius || unit->GetExactDist(GetExplTargetDest()) < inRadius;

                else
                    return true;
            });

            Unit::AuraList castedRingOfFrostStuns;
            Unit::AuraList& castedAuras = GetCaster()->GetCastedAuras();

            for (Unit::AuraList::iterator itr = castedAuras.begin(); itr != castedAuras.end(); ++itr)
                if ((*itr)->GetId() == SPELL_MAGE_RING_OF_FROST_FREEZE)
                    castedRingOfFrostStuns.push_back((*itr));

            if (castedRingOfFrostStuns.size() + targets.size() > GetSpellInfo()->MaxAffectedTargets)
                Trinity::Containers::RandomResizeList(targets, GetSpellInfo()->MaxAffectedTargets - castedRingOfFrostStuns.size());
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mage_ring_of_frost_freeze_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_mage_ring_of_frost_freeze_SpellScript();
    }

    class spell_mage_ring_of_frost_freeze_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_ring_of_frost_freeze_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_RING_OF_FROST_IMUNITY))
                return false;
            return true;
        }

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (GetTargetApplication()->GetRemoveMode() != AURA_REMOVE_BY_EXPIRE)
                if (GetCaster())
                    GetCaster()->CastSpell(GetTarget(), SPELL_MAGE_RING_OF_FROST_IMUNITY, true);
        }

        void Register() override
        {
            AfterEffectRemove += AuraEffectRemoveFn(spell_mage_ring_of_frost_freeze_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_mage_ring_of_frost_freeze_AuraScript();
    }
};

class spell_mage_frostbolt : public SpellScriptLoader
{
public:
    spell_mage_frostbolt() : SpellScriptLoader("spell_mage_frostbolt") { }

    class spell_mage_frostbolt_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_frostbolt_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_MASTERY_ICICLES))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FINGERS_OF_FROST))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FINGERS_OF_FROST_PROC))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FROSTBOLT_HEAL))
                return false;
            return true;
        }

        SpellCastResult CheckCast()
        {
            Unit* target = GetExplTargetUnit();

            if (target->IsFriendlyTo(GetCaster()))
            {
                if (target->GetEntry() != PET_MAGE_WATER_ELEMENTAL)
                    return SPELL_FAILED_TARGET_FRIENDLY;
            }

            return SPELL_CAST_OK;
        }

        void HandleOnHit()
        {
            Unit* target = GetHitUnit();

            if (target->GetEntry() == PET_MAGE_WATER_ELEMENTAL)
            {
                SetHitDamage(0);
                GetCaster()->CastSpell(target, SPELL_MAGE_FROSTBOLT_HEAL, true);
            }
        }

        void HandleAfterHit()
        {
            if (GetHitUnit()->GetEntry() == PET_MAGE_WATER_ELEMENTAL)
                return;

            if (Unit* caster = GetCaster())
                if (caster->HasAura(SPELL_MAGE_MASTERY_ICICLES))
                    if (roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_MAGE_FINGERS_OF_FROST)->Effects[EFFECT_0].BasePoints))
                        caster->CastSpell(caster, SPELL_MAGE_FINGERS_OF_FROST_PROC, true);
        }

        void Register() override
        {
            AfterHit += SpellHitFn(spell_mage_frostbolt_SpellScript::HandleAfterHit);
            OnCheckCast += SpellCheckCastFn(spell_mage_frostbolt_SpellScript::CheckCast);
            OnHit += SpellHitFn(spell_mage_frostbolt_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_mage_frostbolt_SpellScript();
    }

};

class spell_mage_frostfire_bolt : public SpellScriptLoader
{
public:
    spell_mage_frostfire_bolt() : SpellScriptLoader("spell_mage_frostfire_bolt") { }

    class spell_mage_frostfire_bolt_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_frostfire_bolt_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_MASTERY_ICICLES))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FINGERS_OF_FROST))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FINGERS_OF_FROST_PROC))
                return false;
            return true;
        }

        void HandleAfterHit()
        {
            if (Unit* caster = GetCaster())
                if (caster->HasAura(SPELL_MAGE_MASTERY_ICICLES))
                    if (roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_MAGE_FINGERS_OF_FROST)->Effects[EFFECT_0].BasePoints))
                        caster->CastSpell(caster, SPELL_MAGE_FINGERS_OF_FROST_PROC, true);
        }

        void Register() override
        {
            AfterHit += SpellHitFn(spell_mage_frostfire_bolt_SpellScript::HandleAfterHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_mage_frostfire_bolt_SpellScript();
    }

};

class spell_mage_frozen_orb_dmg : public SpellScriptLoader
{
public:
    spell_mage_frozen_orb_dmg() : SpellScriptLoader("spell_mage_frozen_orb_dmg") { }

    class spell_mage_frozen_orb_dmg_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_frozen_orb_dmg_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_MASTERY_ICICLES))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FINGERS_OF_FROST))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FINGERS_OF_FROST_PROC))
                return false;
            return true;
        }

        void HandleAfterHit()
        {
            if (Unit* caster = GetCaster())
                if (caster->HasAura(SPELL_MAGE_MASTERY_ICICLES))
                    if (roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_MAGE_FINGERS_OF_FROST)->Effects[EFFECT_0].BasePoints))
                        caster->CastSpell(caster, SPELL_MAGE_FINGERS_OF_FROST_PROC, true);
        }

        void Register() override
        {
            AfterHit += SpellHitFn(spell_mage_frozen_orb_dmg_SpellScript::HandleAfterHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_mage_frozen_orb_dmg_SpellScript();
    }

};

class spell_mage_blizzard_dmg : public SpellScriptLoader
{
public:
    spell_mage_blizzard_dmg() : SpellScriptLoader("spell_mage_blizzard_dmg") { }

    class spell_mage_blizzard_dmg_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_blizzard_dmg_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_MASTERY_ICICLES))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FINGERS_OF_FROST))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FINGERS_OF_FROST_PROC))
                return false;
            return true;
        }

        void HandleAfterHit()
        {
            if (Unit* caster = GetCaster())
                if (caster->HasAura(SPELL_MAGE_MASTERY_ICICLES))
                    if (roll_chance_i(sSpellMgr->GetSpellInfo(SPELL_MAGE_FINGERS_OF_FROST)->Effects[EFFECT_1].BasePoints))
                        caster->CastSpell(caster, SPELL_MAGE_FINGERS_OF_FROST_PROC, true);
        }

        void Register() override
        {
            AfterHit += SpellHitFn(spell_mage_blizzard_dmg_SpellScript::HandleAfterHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_mage_blizzard_dmg_SpellScript();
    }

};

class spell_mage_fingers_of_frost_proc : public SpellScriptLoader
{
public:
    spell_mage_fingers_of_frost_proc() : SpellScriptLoader("spell_mage_fingers_of_frost_proc") { }

    class spell_mage_fingers_of_frost_proc_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_fingers_of_frost_proc_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FINGERS_OF_FROST_VISUAL))
                return false;
            return true;
        }
        void AfterApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (GetStackAmount() > 1)
                if (Unit* caster = GetCaster())
                    caster->AddAura(SPELL_MAGE_FINGERS_OF_FROST_VISUAL, caster);
        }
        void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (GetStackAmount() < 2)
                if (Unit* caster = GetCaster())
                    if (caster->HasAura(SPELL_MAGE_FINGERS_OF_FROST_VISUAL))
                        caster->RemoveAura(SPELL_MAGE_FINGERS_OF_FROST_VISUAL);
        }

        void Register() override
        {
            AfterEffectApply += AuraEffectApplyFn(spell_mage_fingers_of_frost_proc_AuraScript::AfterApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            AfterEffectRemove += AuraEffectRemoveFn(spell_mage_fingers_of_frost_proc_AuraScript::AfterRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_mage_fingers_of_frost_proc_AuraScript();
    }
};

class spell_mage_ice_lance : public SpellScriptLoader
{
public:
    spell_mage_ice_lance() : SpellScriptLoader("spell_mage_ice_lance") { }

    class spell_mage_ice_lance_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_ice_lance_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FINGERS_OF_FROST))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FINGERS_OF_FROST_PROC))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_ICICLE_STORE_1))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_ICICLE_TRIGGER))
                return false;
            return true;
        }

        Aura* fofAura;

        void HandleOnCast()
        {
            fofAura = GetCaster()->GetAura(SPELL_MAGE_FINGERS_OF_FROST_PROC);
        }

        void HandleAfterCast()
        {
            Unit* caster = GetCaster();
            if (!caster)
                return;

            if (caster->HasAura(SPELL_MAGE_ICICLE_STORE_1) || caster->HasAura(SPELL_MAGE_ICICLE_STORE_2) || caster->HasAura(SPELL_MAGE_ICICLE_STORE_3) || caster->HasAura(SPELL_MAGE_ICICLE_STORE_4) || caster->HasAura(SPELL_MAGE_ICICLE_STORE_5))
                caster->CastSpell(caster, SPELL_MAGE_ICICLE_TRIGGER, true);
        }

        void RecalculateDamage()
        {
            int32 damage = GetHitDamage();

            if (GetHitUnit()->HasAuraState(AURA_STATE_FROZEN, GetSpellInfo(), GetCaster()) || fofAura)
                damage *= 4;

            if (fofAura)
                AddPct(damage, sSpellMgr->GetSpellInfo(SPELL_MAGE_FINGERS_OF_FROST)->Effects[EFFECT_3].BasePoints);

            SetHitDamage(damage);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_mage_ice_lance_SpellScript::RecalculateDamage);
            OnCast += SpellCastFn(spell_mage_ice_lance_SpellScript::HandleOnCast);
            AfterCast += SpellCastFn(spell_mage_ice_lance_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_mage_ice_lance_SpellScript();
    }
};

class spell_mage_deep_freeze : public SpellScriptLoader
{
public:
    spell_mage_deep_freeze() : SpellScriptLoader("spell_mage_deep_freeze") { }

    class spell_mage_deep_freeze_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_deep_freeze_SpellScript);

        bool Validate(SpellInfo const* /*spellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_FINGERS_OF_FROST_PROC))
                return false;
            return true;
        }

        void HandleOnCast()
        {
            if (Aura* fofAura = GetCaster()->GetAura(SPELL_MAGE_FINGERS_OF_FROST_PROC))
                fofAura->ModStackAmount(-1);
        }

        void Register()
        {
            OnCast += SpellCastFn(spell_mage_deep_freeze_SpellScript::HandleOnCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_mage_deep_freeze_SpellScript();
    }
};

class spell_mage_combustion : public SpellScriptLoader
{
public:
    spell_mage_combustion() : SpellScriptLoader("spell_mage_combustion") { }

    class spell_mage_combustion_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_combustion_SpellScript);

        void HandleOnHit()
        {
            Player* caster = GetCaster()->ToPlayer();
            Unit* target = GetHitUnit();
            if (!caster || !target)
                return;

            caster->CastSpell(target, SPELL_MAGE_COMBUSTION_IMPACT, true);

            if (caster->HasSpellCooldown(SPELL_MAGE_INFERNO_BLAST))
            {
                caster->RemoveSpellCooldown(SPELL_MAGE_INFERNO_BLAST, true);
                caster->RemoveSpellCooldown(SPELL_MAGE_INFERNO_BLAST_IMPACT, true);
            }

            int32 combustionBp = 0;

            Unit::AuraEffectList const& aurasPereodic = target->GetAuraEffectsByType(SPELL_AURA_PERIODIC_DAMAGE);
            for (Unit::AuraEffectList::const_iterator i = aurasPereodic.begin(); i != aurasPereodic.end(); ++i)
            {
                if ((*i)->GetCasterGUID() != caster->GetGUID() || (*i)->GetSpellInfo()->SchoolMask != SPELL_SCHOOL_MASK_FIRE)
                    continue;

                if (!(*i)->GetAmplitude())
                    continue;

                combustionBp += caster->SpellDamageBonusDone(target, (*i)->GetSpellInfo(), (*i)->GetAmount(), DOT) * 1000 / (*i)->GetAmplitude();
            }

            if (combustionBp)
                caster->CastCustomSpell(target, SPELL_MAGE_COMBUSTION_DOT, &combustionBp, NULL, NULL, true);
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_mage_combustion_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_mage_combustion_SpellScript();
    }
};

class spell_mage_living_bomb : public SpellScriptLoader
{
public:
    spell_mage_living_bomb() : SpellScriptLoader("spell_mage_living_bomb") { }

    class spell_mage_living_bomb_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_living_bomb_AuraScript);

        void AfterRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
            if (removeMode != AURA_REMOVE_BY_DEATH && removeMode != AURA_REMOVE_BY_EXPIRE)
                return;

            Unit* caster = GetCaster();
            if (!caster)
                return;

            caster->CastSpell(GetTarget(), SPELL_MAGE_LIVING_BOMB_TRIGGERED, true);

            if (caster->HasAura(SPELL_MAGE_BRAIN_FREEZE))
                caster->CastSpell(caster, SPELL_MAGE_BRAIN_FREEZE_TRIGGERED, true);

        }

        void Register()
        {
            AfterEffectRemove += AuraEffectRemoveFn(spell_mage_living_bomb_AuraScript::AfterRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_mage_living_bomb_AuraScript();
    }
};

class spell_mage_mastery_ignite : public SpellScriptLoader
{
public:
    spell_mage_mastery_ignite() : SpellScriptLoader("spell_mage_mastery_ignite") { }

    class spell_mage_mastery_ignite_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_mastery_ignite_SpellScript);

        void HandleAfterHit()
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();
            if (!caster || !target)
                return;

            if (caster->GetTypeId() == TYPEID_PLAYER && caster->HasAura(SPELL_MAGE_MASTERY_IGNITE))
            {
                uint32 procSpellId = GetSpellInfo()->Id ? GetSpellInfo()->Id : 0;
                if (procSpellId != SPELL_MAGE_IGNITE)
                {
                    float Mastery = caster->ToPlayer()->GetMasterySpellCoefficient() / 100.0f;

                    int32 bp = GetHitDamage();
                    bp = int32(bp * Mastery / 2);

                    if (target->HasAura(SPELL_MAGE_IGNITE, caster->GetGUID()))
                    {
                        bp += target->GetRemainingPeriodicAmount(caster->GetGUID(), SPELL_MAGE_IGNITE, SPELL_AURA_PERIODIC_DAMAGE);
                        bp = int32(bp * 0.66f);
                    }

                    caster->CastCustomSpell(target, SPELL_MAGE_IGNITE, &bp, NULL, NULL, true);
                }
            }
        }

        void Register()
        {
            AfterHit += SpellHitFn(spell_mage_mastery_ignite_SpellScript::HandleAfterHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_mage_mastery_ignite_SpellScript();
    }
};

// 76613 - Mastery: Icicles
class spell_mage_mastery_icicles : public SpellScriptLoader
{
public:
    spell_mage_mastery_icicles() : SpellScriptLoader("spell_mage_mastery_icicles") { }

    class spell_mage_mastery_icicles_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_mastery_icicles_AuraScript);

        bool Validate(SpellInfo const* spellInfo) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_ICICLE_STORE_1))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_ICICLE_STORE_2))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_ICICLE_STORE_3))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_ICICLE_STORE_4))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_ICICLE_STORE_5))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_ICICLE_1))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_ICICLE_2))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_ICICLE_3))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_ICICLE_4))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_ICICLE_5))
                return false;
            return true;
        }

        int lastlaunched;

        bool Load() override
        {
            lastlaunched = 5;

            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;

            return true;
        }

        bool CheckProc(ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetDamageInfo()->GetSpellInfo()->Id == SPELL_MAGE_ICE_LANCE)
                lastlaunched = 5;

            if (eventInfo.GetDamageInfo()->GetSpellInfo()->Id == SPELL_MAGE_FROSTBOLT || eventInfo.GetDamageInfo()->GetSpellInfo()->Id == SPELL_MAGE_FROSTFIRE_BOLT)
                return true;

            else
                return false;
        }

        void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
        {
            Unit* caster = GetCaster();

            if (!caster)
                return;

            int32 damage = CalculatePct(eventInfo.GetDamageInfo()->GetDamage(), caster->ToPlayer()->GetMasterySpellCoefficient());

            if (!damage)
                return;

            if (!caster->HasAura(SPELL_MAGE_ICICLE_STORE_1))
            {
                caster->CastSpell(caster, SPELL_MAGE_ICICLE_STORE_1, true, NULL, aurEff);
                caster->GetAura(SPELL_MAGE_ICICLE_STORE_1)->GetEffect(EFFECT_0)->SetAmount(damage);
            }
                
            else if (!caster->HasAura(SPELL_MAGE_ICICLE_STORE_2))
            {
                caster->CastSpell(caster, SPELL_MAGE_ICICLE_STORE_2, true, NULL, aurEff);
                caster->GetAura(SPELL_MAGE_ICICLE_STORE_2)->GetEffect(EFFECT_0)->SetAmount(damage);
            }

            else if (!caster->HasAura(SPELL_MAGE_ICICLE_STORE_3))
            {
                caster->CastSpell(caster, SPELL_MAGE_ICICLE_STORE_3, true, NULL, aurEff);
                caster->GetAura(SPELL_MAGE_ICICLE_STORE_3)->GetEffect(EFFECT_0)->SetAmount(damage);
            }

            else if (!caster->HasAura(SPELL_MAGE_ICICLE_STORE_4))
            {
                caster->CastSpell(caster, SPELL_MAGE_ICICLE_STORE_4, true, NULL, aurEff);
                caster->GetAura(SPELL_MAGE_ICICLE_STORE_4)->GetEffect(EFFECT_0)->SetAmount(damage);
            }

            else if (!caster->HasAura(SPELL_MAGE_ICICLE_STORE_5))
            {
                caster->CastSpell(caster, SPELL_MAGE_ICICLE_STORE_5, true, NULL, aurEff);
                caster->GetAura(SPELL_MAGE_ICICLE_STORE_5)->GetEffect(EFFECT_0)->SetAmount(damage);
            }

            else
            {
                Unit* victim = eventInfo.GetDamageInfo()->GetVictim();

                if (!victim)
                    return;

                if (lastlaunched == 5)
                {
                    caster->CastSpell(victim, SPELL_MAGE_ICICLE_1, true, NULL, aurEff);
                    caster->CastCustomSpell(SPELL_MAGE_ICICLE_DMG, SPELLVALUE_BASE_POINT0, caster->GetAura(SPELL_MAGE_ICICLE_STORE_1)->GetEffect(EFFECT_0)->GetAmount(), victim, true);
                    caster->RemoveAura(SPELL_MAGE_ICICLE_STORE_1);
                    caster->CastSpell(caster, SPELL_MAGE_ICICLE_STORE_1, true, NULL, aurEff);
                    caster->GetAura(SPELL_MAGE_ICICLE_STORE_1)->GetEffect(EFFECT_0)->SetAmount(damage);
                    lastlaunched = 1;
                }

                else if (lastlaunched == 1)
                {
                    caster->CastSpell(victim, SPELL_MAGE_ICICLE_2, true, NULL, aurEff);
                    caster->CastCustomSpell(SPELL_MAGE_ICICLE_DMG, SPELLVALUE_BASE_POINT0, caster->GetAura(SPELL_MAGE_ICICLE_STORE_2)->GetEffect(EFFECT_0)->GetAmount(), victim, true);
                    caster->RemoveAura(SPELL_MAGE_ICICLE_STORE_2);
                    caster->CastSpell(caster, SPELL_MAGE_ICICLE_STORE_2, true, NULL, aurEff);
                    caster->GetAura(SPELL_MAGE_ICICLE_STORE_2)->GetEffect(EFFECT_0)->SetAmount(damage);
                    lastlaunched = 2;
                }

                else if (lastlaunched == 2)
                {
                    caster->CastSpell(victim, SPELL_MAGE_ICICLE_3, true, NULL, aurEff);
                    caster->CastCustomSpell(SPELL_MAGE_ICICLE_DMG, SPELLVALUE_BASE_POINT0, caster->GetAura(SPELL_MAGE_ICICLE_STORE_3)->GetEffect(EFFECT_0)->GetAmount(), victim, true);
                    caster->RemoveAura(SPELL_MAGE_ICICLE_STORE_3);
                    caster->CastSpell(caster, SPELL_MAGE_ICICLE_STORE_3, true, NULL, aurEff);
                    caster->GetAura(SPELL_MAGE_ICICLE_STORE_3)->GetEffect(EFFECT_0)->SetAmount(damage);
                    lastlaunched = 3;
                }

                else if (lastlaunched == 3)
                {
                    caster->CastSpell(victim, SPELL_MAGE_ICICLE_4, true, NULL, aurEff);
                    caster->CastCustomSpell(SPELL_MAGE_ICICLE_DMG, SPELLVALUE_BASE_POINT0, caster->GetAura(SPELL_MAGE_ICICLE_STORE_4)->GetEffect(EFFECT_0)->GetAmount(), victim, true);
                    caster->RemoveAura(SPELL_MAGE_ICICLE_STORE_4);
                    caster->CastSpell(caster, SPELL_MAGE_ICICLE_STORE_4, true, NULL, aurEff);
                    caster->GetAura(SPELL_MAGE_ICICLE_STORE_4)->GetEffect(EFFECT_0)->SetAmount(damage);
                    lastlaunched = 4;
                }

                else if (lastlaunched == 4)
                {
                    caster->CastSpell(victim, SPELL_MAGE_ICICLE_5, true, NULL, aurEff);
                    caster->CastCustomSpell(SPELL_MAGE_ICICLE_DMG, SPELLVALUE_BASE_POINT0, caster->GetAura(SPELL_MAGE_ICICLE_STORE_5)->GetEffect(EFFECT_0)->GetAmount(), victim, true);
                    caster->RemoveAura(SPELL_MAGE_ICICLE_STORE_5);
                    caster->CastSpell(caster, SPELL_MAGE_ICICLE_STORE_5, true, NULL, aurEff);
                    caster->GetAura(SPELL_MAGE_ICICLE_STORE_5)->GetEffect(EFFECT_0)->SetAmount(damage);
                    lastlaunched = 5;
                }
            }
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_mage_mastery_icicles_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_mage_mastery_icicles_AuraScript::HandleProc, EFFECT_1, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_mage_mastery_icicles_AuraScript();
    }
};

// 148023 - Icicle trigger
class spell_mage_icicle_trigger : public SpellScriptLoader
{
public:
    spell_mage_icicle_trigger() : SpellScriptLoader("spell_mage_icicle_trigger") { }

    class spell_mage_icicle_trigger_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_icicle_trigger_AuraScript);

        bool Validate(SpellInfo const* spellInfo) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_ICICLE_STORE_1))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_ICICLE_STORE_2))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_ICICLE_STORE_3))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_ICICLE_STORE_4))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_ICICLE_STORE_5))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_ICICLE_1))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_ICICLE_2))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_ICICLE_3))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_ICICLE_4))
                return false;
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_ICICLE_5))
                return false;
            return true;
        }

        Unit* target;
        int lastlaunched;

        bool Load() override
        {
            lastlaunched = 5;
            if (target = GetCaster()->ToPlayer()->GetSelectedUnit())
                return true;

            return false;
        }

        void HandleEffectPeriodic(AuraEffect const* aurEff)
        {
            Unit* caster = GetCaster();

            if (!target->CanFreeMove() || target->isDead())
            {
                caster->RemoveAura(SPELL_MAGE_ICICLE_TRIGGER);
                return;
            }

            Aura* store_1 = caster->GetAura(SPELL_MAGE_ICICLE_STORE_1);
            Aura* store_2 = caster->GetAura(SPELL_MAGE_ICICLE_STORE_2);
            Aura* store_3 = caster->GetAura(SPELL_MAGE_ICICLE_STORE_3);
            Aura* store_4 = caster->GetAura(SPELL_MAGE_ICICLE_STORE_4);
            Aura* store_5 = caster->GetAura(SPELL_MAGE_ICICLE_STORE_5);

            if (!store_1 && !store_2 && !store_3 && !store_4 && !store_5)
            {
                caster->RemoveAura(SPELL_MAGE_ICICLE_TRIGGER);
                return;
            }
                
            if (store_1)
                if ((lastlaunched == 5) || (lastlaunched == 1 && (!store_2 && !store_3 && !store_4 && !store_5)) || (lastlaunched == 2 && (!store_3 && !store_4 && !store_5)) || (lastlaunched == 3 && (!store_4 && !store_5)) || (lastlaunched == 4 && !store_5))
                {
                    caster->CastSpell(target, SPELL_MAGE_ICICLE_1, true, NULL, aurEff);
                    caster->CastCustomSpell(SPELL_MAGE_ICICLE_DMG, SPELLVALUE_BASE_POINT0, caster->GetAura(SPELL_MAGE_ICICLE_STORE_1)->GetEffect(EFFECT_0)->GetAmount(), target, true);
                    caster->RemoveAura(SPELL_MAGE_ICICLE_STORE_1);
                    lastlaunched = 1;
                    return;
                }

            if (store_2)
                if ((lastlaunched == 1) || (lastlaunched == 2 && (!store_3 && !store_4 && !store_5 && !store_1)) || (lastlaunched == 3 && (!store_4 && !store_5 && !store_1)) || (lastlaunched == 4 && (!store_5 && !store_1)) || (lastlaunched == 5 && !store_1))
                {
                    caster->CastSpell(target, SPELL_MAGE_ICICLE_2, true, NULL, aurEff);
                    caster->CastCustomSpell(SPELL_MAGE_ICICLE_DMG, SPELLVALUE_BASE_POINT0, caster->GetAura(SPELL_MAGE_ICICLE_STORE_2)->GetEffect(EFFECT_0)->GetAmount(), target, true);
                    caster->RemoveAura(SPELL_MAGE_ICICLE_STORE_2);
                    lastlaunched = 2;
                    return;
                }

            if (store_3)
                if ((lastlaunched == 2) || (lastlaunched == 3 && (!store_4 && !store_5 && !store_1 && !store_2)) || (lastlaunched == 4 && (!store_5 && !store_1 && !store_2)) || (lastlaunched == 5 && (!store_1 && !store_2)) || (lastlaunched == 1 && !store_2))
                {
                    caster->CastSpell(target, SPELL_MAGE_ICICLE_3, true, NULL, aurEff);
                    caster->CastCustomSpell(SPELL_MAGE_ICICLE_DMG, SPELLVALUE_BASE_POINT0, caster->GetAura(SPELL_MAGE_ICICLE_STORE_3)->GetEffect(EFFECT_0)->GetAmount(), target, true);
                    caster->RemoveAura(SPELL_MAGE_ICICLE_STORE_3);
                    lastlaunched = 3;
                    return;
                }

            if (store_4)
                if ((lastlaunched == 3) || (lastlaunched == 4 && (!store_5 && !store_1 && !store_2 && !store_3)) || (lastlaunched == 5 && (!store_1 && !store_2 && !store_3)) || (lastlaunched == 1 && (!store_2 && !store_3)) || (lastlaunched == 2 && !store_3))
                {
                    caster->CastSpell(target, SPELL_MAGE_ICICLE_4, true, NULL, aurEff);
                    caster->CastCustomSpell(SPELL_MAGE_ICICLE_DMG, SPELLVALUE_BASE_POINT0, caster->GetAura(SPELL_MAGE_ICICLE_STORE_4)->GetEffect(EFFECT_0)->GetAmount(), target, true);
                    caster->RemoveAura(SPELL_MAGE_ICICLE_STORE_4);
                    lastlaunched = 4;
                    return;
                }

            if (store_5)
                if ((lastlaunched == 4) || (lastlaunched == 5 && (!store_1 && !store_2 && !store_3 && !store_4)) || (lastlaunched == 1 && (!store_2 && !store_3 && !store_4)) || (lastlaunched == 2 && (!store_3 && !store_4)) || (lastlaunched == 3 && !store_4))
                {
                    caster->CastSpell(target, SPELL_MAGE_ICICLE_5, true, NULL, aurEff);
                    caster->CastCustomSpell(SPELL_MAGE_ICICLE_DMG, SPELLVALUE_BASE_POINT0, caster->GetAura(SPELL_MAGE_ICICLE_STORE_5)->GetEffect(EFFECT_0)->GetAmount(), target, true);
                    caster->RemoveAura(SPELL_MAGE_ICICLE_STORE_5);
                    lastlaunched = 5;
                    return;
                }
        }
        
        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_mage_icicle_trigger_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_mage_icicle_trigger_AuraScript();
    }
};

// 31707 Waterbolt
class spell_mage_waterbolt : public SpellScriptLoader
{
public:
    spell_mage_waterbolt() : SpellScriptLoader("spell_mage_waterbolt") { }

    class spell_mage_waterbolt_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mage_waterbolt_SpellScript);

        bool Validate(SpellInfo const* spellInfo) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MAGE_MASTERY_ICICLES))
                return false;

            return true;
        }

        bool Load() override
        {
            if (GetCaster()->GetEntry() == PET_MAGE_WATER_ELEMENTAL)
                return true;

            return false;
        }

        void RecalculateDamage()
        {
            if (!GetCaster()->GetOwner()->HasAura(SPELL_MAGE_MASTERY_ICICLES))
                return;

            int32 damage = GetHitDamage();

            AddPct(damage, GetCaster()->GetOwner()->ToPlayer()->GetMasterySpellCoefficient());

            SetHitDamage(damage);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_mage_waterbolt_SpellScript::RecalculateDamage);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_mage_waterbolt_SpellScript();
    }
};

void AddSC_mage_spell_scripts()
{
    new spell_mage_conjure_refreshment();
    new spell_mage_conjure_refreshment_table();
    new spell_mage_cauterize();
    new spell_mage_ice_barrier();
    new spell_mage_temporal_shield();
    new spell_mage_flameglow();
    new spell_mage_ring_of_frost_instant();
    new spell_mage_ring_of_frost_periodic();
    new spell_mage_ring_of_frost_freeze();
    new spell_mage_frostbolt();
    new spell_mage_frostfire_bolt();
    new spell_mage_frozen_orb_dmg();
    new spell_mage_blizzard_dmg();
    new spell_mage_fingers_of_frost_proc();
    new spell_mage_ice_lance();
    new spell_mage_deep_freeze();
    new spell_mage_combustion();
    new spell_mage_living_bomb();
    new spell_mage_mastery_ignite();
    new spell_mage_mastery_icicles();
    new spell_mage_icicle_trigger();
    new spell_mage_waterbolt();
}
