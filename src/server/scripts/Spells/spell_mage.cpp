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
    SPELL_MAGE_TEMPORAL_RIPPLES             = 115611
};

enum MageIcons
{
    ICON_MAGE_SHATTER                            = 976,
    ICON_MAGE_IMPROVED_FLAMESTRIKE               = 37,
    ICON_MAGE_IMPROVED_FREEZE                    = 94,
    ICON_MAGE_INCANTER_S_ABSORPTION              = 2941,
    ICON_MAGE_IMPROVED_MANA_GEM                  = 1036
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

// 43987 Conjure Refreshment Table
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

// 86949 Cauterize talent aura
class spell_mage_cauterize : public SpellScriptLoader
{
public:
    spell_mage_cauterize() : SpellScriptLoader("spell_mage_cauterize") {}

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

// 11426 - Ice Barrier
class spell_mage_ice_barrier : public SpellScriptLoader
{
public:
    spell_mage_ice_barrier() : SpellScriptLoader("spell_mage_ice_barrier") { }

    class spell_mage_ice_barrier_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_ice_barrier_AuraScript);

        void CalculateAmount(AuraEffect const * /*aurEff*/, int32 & amount, bool & canBeRecalculated)
        {
            canBeRecalculated = false;
            if (Unit* caster = GetCaster())
            {
                int32 sp = caster->SpellBaseDamageBonusDone(GetSpellInfo()->GetSchoolMask());
                // 330% SP bonus
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

//115610 Temporal Shield
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

// 140468 Flameglow
class spell_mage_flameglow : public SpellScriptLoader
{
public:
    spell_mage_flameglow() : SpellScriptLoader("spell_mage_flameglow") {}

    class spell_mage_flameglow_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_mage_flameglow_AuraScript);

        bool Load() override
        {
            if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                return false;
            return true;
        }

        void CalculateAmount(AuraEffect const * /*aurEff*/, int32 & amount, bool & canBeRecalculated)
        {
            amount = -1;
        }

        void Absorb(AuraEffect* aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount)
        {
            Unit * caster = GetCaster();

            if (!caster)
                return;

            int32 fullabsorb = caster->SpellBaseDamageBonusDone(GetSpellInfo()->GetSchoolMask())*GetSpellInfo()->Effects[1].BasePoints / 100;

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

void AddSC_mage_spell_scripts()
{
    new spell_mage_conjure_refreshment();
    new spell_mage_conjure_refreshment_table();
    new spell_mage_cauterize();
    new spell_mage_ice_barrier();
    new spell_mage_temporal_shield();
    new spell_mage_flameglow();
}
