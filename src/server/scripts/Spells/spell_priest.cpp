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
 * Scripts for spells with SPELLFAMILY_PRIEST and SPELLFAMILY_GENERIC spells used by priest players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_pri_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "GridNotifiers.h"

enum PriestSpells
{
    SPELL_PRIEST_BODY_AND_SOUL_TALENT       = 64129,
    SPELL_PRIEST_BODY_AND_SOUL_SPEED        = 65081,
    SPELL_PRIEST_LEAP_OF_FAITH_JUMP         = 92832,
    SPELL_PRIEST_ANGELIC_BULWARK_ABSORB     = 114214,
    SPELL_PRIEST_ANGELIC_BULWARK_HIDDEN_CD  = 114216,
};

enum PriestSpellIcons
{
    PRIEST_ICON_ID_BORROWED_TIME                    = 2899,
    PRIEST_ICON_ID_DIVINE_TOUCH_TALENT              = 3021,
    PRIEST_ICON_ID_PAIN_AND_SUFFERING               = 2874
};

enum MiscSpells
{
    SPELL_GEN_REPLENISHMENT                         = 57669
};

class spell_pri_power_word_shield : public SpellScriptLoader
{
public:
    spell_pri_power_word_shield() : SpellScriptLoader("spell_pri_power_word_shield") { }

    class spell_pri_power_word_shield_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pri_power_word_shield_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PRIEST_BODY_AND_SOUL_TALENT) || !sSpellMgr->GetSpellInfo(SPELL_PRIEST_BODY_AND_SOUL_SPEED))
                return false;
            return true;
        }

        void HandleOnHit()
        {
            if (!GetHitUnit())
                return;

            if (GetCaster()->HasAura(SPELL_PRIEST_BODY_AND_SOUL_TALENT))
                GetCaster()->CastSpell(GetHitUnit(), SPELL_PRIEST_BODY_AND_SOUL_SPEED, true);

        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_pri_power_word_shield_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pri_power_word_shield_SpellScript();
    }
};

class spell_pri_leap_of_faith : public SpellScriptLoader
{
public:
    spell_pri_leap_of_faith() : SpellScriptLoader("spell_pri_leap_of_faith") { }

    class spell_pri_leap_of_faith_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pri_leap_of_faith_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PRIEST_BODY_AND_SOUL_TALENT) || !sSpellMgr->GetSpellInfo(SPELL_PRIEST_BODY_AND_SOUL_SPEED)
                || !sSpellMgr->GetSpellInfo(SPELL_PRIEST_LEAP_OF_FAITH_JUMP))
                return false;
            return true;
        }

        void HandleScript(SpellEffIndex /*effIndex*/)
        {
            if (!GetHitUnit())
                return;

            GetHitUnit()->CastSpell(GetCaster(), SPELL_PRIEST_LEAP_OF_FAITH_JUMP, true);
        }

        void HandleOnHit()
        {
            if (!GetHitUnit())
                return;

            if (GetCaster()->HasAura(SPELL_PRIEST_BODY_AND_SOUL_TALENT))
                GetCaster()->CastSpell(GetHitUnit(), SPELL_PRIEST_BODY_AND_SOUL_SPEED, true);

        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_pri_leap_of_faith_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            OnHit += SpellHitFn(spell_pri_leap_of_faith_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pri_leap_of_faith_SpellScript();
    }
};

class spell_pri_angelic_bulwark : public SpellScriptLoader
{
public:
    spell_pri_angelic_bulwark() : SpellScriptLoader("spell_pri_angelic_bulwark") { }

    class spell_pri_angelic_bulwark_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pri_angelic_bulwark_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PRIEST_ANGELIC_BULWARK_HIDDEN_CD) || !sSpellMgr->GetSpellInfo(SPELL_PRIEST_ANGELIC_BULWARK_ABSORB))
                return false;
            return true;
        }

        bool Load() override
        {
            reqHealthPct = (uint32)GetSpellInfo()->Effects[EFFECT_0].BasePoints;
            return true;
        }

        bool CheckProc(ProcEventInfo& /*eventInfo*/)
        {
            if (!GetOwner() || !GetOwner()->ToUnit())
                return false;

            if (GetOwner()->ToUnit()->HasAura(SPELL_PRIEST_ANGELIC_BULWARK_HIDDEN_CD))
                return false;

            return GetOwner()->ToUnit()->GetHealthPct() < reqHealthPct;
        }

        void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
        {
            Unit* owner = GetOwner() != NULL ? GetOwner()->ToUnit() : NULL;
            if (!owner)
                return;

            int32 healthPct = GetSpellInfo()->Effects[1].BasePoints;
            int32 bp = CalculatePct(owner->GetMaxHealth(), healthPct);
            owner->CastCustomSpell(SPELL_PRIEST_ANGELIC_BULWARK_ABSORB, SPELLVALUE_BASE_POINT0, bp, owner, true);
            owner->CastSpell(owner, SPELL_PRIEST_ANGELIC_BULWARK_HIDDEN_CD, true);
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_pri_angelic_bulwark_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_pri_angelic_bulwark_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);
        }

        uint32 reqHealthPct;
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_pri_angelic_bulwark_AuraScript();
    }
};

void AddSC_priest_spell_scripts()
{
    new spell_pri_power_word_shield();
    new spell_pri_leap_of_faith();
    new spell_pri_angelic_bulwark();
}
