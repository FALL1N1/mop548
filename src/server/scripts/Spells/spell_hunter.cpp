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
 * Scripts for spells with SPELLFAMILY_HUNTER, SPELLFAMILY_PET and SPELLFAMILY_GENERIC spells used by hunter players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_hun_".
 */

#include "Pet.h"
#include "ScriptMgr.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum HunterSpells
{
    SPELL_HUNTER_SERPENT_STING              = 1978,
    SPELL_HUNTER_GENERIC_ENERGIZE_FOCUS     = 91954,
    SPELL_HUNTER_CHIMERA_SHOT_HEAL          = 53353,
    SPELL_HUNTER_STEADY_SHOT_FOCUS          = 77443,
};

class spell_hun_cobra_shot : public SpellScriptLoader
{
public:
    spell_hun_cobra_shot() : SpellScriptLoader("spell_hun_cobra_shot") { }

    class spell_hun_cobra_shot_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_cobra_shot_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_GENERIC_ENERGIZE_FOCUS) || !sSpellMgr->GetSpellInfo(SPELL_HUNTER_SERPENT_STING))
                return false;
            return true;
        }

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            GetCaster()->CastSpell(GetCaster(), SPELL_HUNTER_GENERIC_ENERGIZE_FOCUS, true);

            if (Aura* aura = GetHitUnit()->GetAura(SPELL_HUNTER_SERPENT_STING, GetCaster()->GetGUID()))
            {
                int32 newDuration = aura->GetDuration() + GetEffectValue() * IN_MILLISECONDS;
                aura->SetDuration(std::min(newDuration, aura->GetMaxDuration()), true);
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_hun_cobra_shot_SpellScript::HandleScriptEffect, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_cobra_shot_SpellScript();
    }
};

class spell_hun_chimera_shot : public SpellScriptLoader
{
public:
    spell_hun_chimera_shot() : SpellScriptLoader("spell_hun_chimera_shot") { }

    class spell_hun_chimera_shot_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_chimera_shot_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_CHIMERA_SHOT_HEAL) || !sSpellMgr->GetSpellInfo(SPELL_HUNTER_SERPENT_STING))
                return false;
            return true;
        }

        void HandleScriptEffect(SpellEffIndex /*effIndex*/)
        {
            GetCaster()->CastSpell(GetCaster(), SPELL_HUNTER_CHIMERA_SHOT_HEAL, true);

            if (Aura* aur = GetHitUnit()->GetAura(SPELL_HUNTER_SERPENT_STING, GetCaster()->GetGUID()))
                aur->SetDuration(aur->GetSpellInfo()->GetMaxDuration(), true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_hun_chimera_shot_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_chimera_shot_SpellScript();
    }
};

class spell_hun_steady_shot : public SpellScriptLoader
{
public:
    spell_hun_steady_shot() : SpellScriptLoader("spell_hun_steady_shot") { }

    class spell_hun_steady_shot_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_steady_shot_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_HUNTER_STEADY_SHOT_FOCUS))
                return false;
            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            GetCaster()->CastSpell(GetCaster(), SPELL_HUNTER_STEADY_SHOT_FOCUS, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_hun_steady_shot_SpellScript::HandleDummy, EFFECT_2, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_hun_steady_shot_SpellScript();
    }
};

void AddSC_hunter_spell_scripts()
{
    new spell_hun_cobra_shot();
    new spell_hun_chimera_shot();
    new spell_hun_steady_shot();
}
