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
    SPELL_HUNTER_SERPENT_STING                  = 1978,
    SPELL_HUNTER_GENERIC_ENERGIZE_FOCUS         = 91954,
    SPELL_HUNTER_CHIMERA_SHOT_HEAL              = 53353,
    SPELL_HUNTER_STEADY_SHOT_FOCUS              = 77443,
    SPELL_HUNTER_CAMOUFLAGE                     = 51755,
    SPELL_HUNTER_CAMOUFLAGE_DUMMY               = 51753,
    SPELL_HUNTER_CAMOUFLAGE_STEALTH             = 80325,
    SPELL_HUNTER_CAMOUFLAGE_VISUAL              = 80326,
    SPELL_HUNTER_GLYPH_OF_CAMOUFLAGE            = 119449,
    SPELL_HUNTER_GLYPH_OF_CAMOUFLAGE_STEALTH    = 119450

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

class spell_hun_camouflage : public SpellScriptLoader
{
public:
    spell_hun_camouflage() : SpellScriptLoader("spell_hun_camouflage") { }

    class spell_hun_camouflage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hun_camouflage_SpellScript);

        void HandleEffect(SpellEffIndex /*effIndex*/)
        {
            Aura* playerAura = GetCaster()->AddAura(SPELL_HUNTER_CAMOUFLAGE, GetCaster());

            if (Player* player = GetCaster()->ToPlayer())
            {
                Aura* petAura = NULL;
                Pet* pet = player->GetPet();
                if (pet)
                    petAura = player->AddAura(SPELL_HUNTER_CAMOUFLAGE, pet);

                if (player->IsInCombat() || (pet && pet->IsInCombat()))
                {
                    if (playerAura)
                        playerAura->SetDuration(GetEffectValue() * IN_MILLISECONDS);

                    if (petAura)
                        petAura->SetDuration(GetEffectValue() * IN_MILLISECONDS);
                }
            }

        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_hun_camouflage_SpellScript::HandleEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hun_camouflage_SpellScript();
    }
};

class spell_hun_camouflage_aura : public SpellScriptLoader
{
public:
    spell_hun_camouflage_aura() : SpellScriptLoader("spell_hun_camouflage_aura") { }

    class spell_hun_camouflage_aura_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_camouflage_aura_AuraScript);

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (GetTarget()->HasAura(SPELL_HUNTER_GLYPH_OF_CAMOUFLAGE))
                GetTarget()->CastSpell(GetTarget(), SPELL_HUNTER_GLYPH_OF_CAMOUFLAGE_STEALTH, true);

            GetTarget()->CastSpell(GetTarget(), SPELL_HUNTER_CAMOUFLAGE_VISUAL, true);
        }

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            GetTarget()->RemoveAura(SPELL_HUNTER_CAMOUFLAGE_DUMMY);
            GetTarget()->RemoveAura(SPELL_HUNTER_CAMOUFLAGE_VISUAL);
            GetTarget()->RemoveAura(SPELL_HUNTER_CAMOUFLAGE_STEALTH);
            GetTarget()->RemoveAura(SPELL_HUNTER_GLYPH_OF_CAMOUFLAGE_STEALTH);

            if (Player* player = GetTarget()->ToPlayer())
                if (Pet* playerPet = player->GetPet())
                    playerPet->RemoveAura(SPELL_HUNTER_CAMOUFLAGE);
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_hun_camouflage_aura_AuraScript::OnApply, EFFECT_2, SPELL_AURA_MOD_CAMOUFLAGE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            OnEffectRemove += AuraEffectApplyFn(spell_hun_camouflage_aura_AuraScript::OnRemove, EFFECT_2, SPELL_AURA_MOD_CAMOUFLAGE, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_hun_camouflage_aura_AuraScript();
    }
};

class spell_hun_camouflage_visual : public SpellScriptLoader
{
public:
    spell_hun_camouflage_visual() : SpellScriptLoader("spell_hun_camouflage_visual") { }

    class spell_hun_camouflage_visual_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hun_camouflage_visual_AuraScript);

        void EffectPeriodic(AuraEffect const* /*aurEff*/)
        {
            if (GetTarget()->HasAura(SPELL_HUNTER_GLYPH_OF_CAMOUFLAGE) && !GetTarget()->HasAura(SPELL_HUNTER_GLYPH_OF_CAMOUFLAGE_STEALTH))
                GetTarget()->CastSpell(GetTarget(), SPELL_HUNTER_GLYPH_OF_CAMOUFLAGE_STEALTH, true);
            else if (!GetTarget()->isMoving() && !GetTarget()->HasAura(SPELL_HUNTER_CAMOUFLAGE_STEALTH))
                GetTarget()->CastSpell(GetTarget(), SPELL_HUNTER_CAMOUFLAGE_STEALTH, true);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_hun_camouflage_visual_AuraScript::EffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_hun_camouflage_visual_AuraScript();
    }
};

void AddSC_hunter_spell_scripts()
{
    new spell_hun_cobra_shot();
    new spell_hun_chimera_shot();
    new spell_hun_steady_shot();
    new spell_hun_camouflage();
    new spell_hun_camouflage_aura();
    new spell_hun_camouflage_visual();
}
