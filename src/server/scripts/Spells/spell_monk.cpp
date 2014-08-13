/*
 * Copyright (C) 2011-2014 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2014 MaNGOS <http://getmangos.com/>
 * Copyright (C) 2013-2014 TimelessCore <http://timeless.sk/>
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
 * Scripts for spells with SPELLFAMILY_MONK and SPELLFAMILY_GENERIC spells used by monk players.
 * Scriptnames of files in this file should be prefixed with "spell_monk_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Containers.h"

enum MonkSpells
{
    SPELL_MONK_CRACKLING_JADE_LIGHTNING_HIDDEN_CD   = 117953,
    SPELL_MONK_CRACKLING_JADE_LIGHTNING_AURA        = 117959,
    SPELL_MONK_CRACKLING_JADE_LIGHTNING_KNOCKBACK   = 117962,
    SPELL_MONK_CRACKLING_JADE_LIGHTNING_CHI_PROC    = 123332,
};

// 117952 - Crackling Jade Lightning
class spell_monk_crackling_jade_lightning : public SpellScriptLoader
{
public:
    spell_monk_crackling_jade_lightning() : SpellScriptLoader("spell_monk_crackling_jade_lightning") { }

    class spell_monk_crackling_jade_lightning_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_crackling_jade_lightning_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MONK_CRACKLING_JADE_LIGHTNING_AURA))
                return false;
            return true;
        }

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (GetCaster())
            {
                GetCaster()->CastSpell(GetCaster(), SPELL_MONK_CRACKLING_JADE_LIGHTNING_AURA, true);
                GetCaster()->CastSpell(GetCaster(), SPELL_MONK_CRACKLING_JADE_LIGHTNING_CHI_PROC, true);
            }
        }

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (GetCaster())
            {
                GetCaster()->RemoveAura(SPELL_MONK_CRACKLING_JADE_LIGHTNING_AURA);
                GetCaster()->RemoveAura(SPELL_MONK_CRACKLING_JADE_LIGHTNING_CHI_PROC);
            }
        }

        void Register() override
        {
            AfterEffectApply += AuraEffectRemoveFn(spell_monk_crackling_jade_lightning_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
            AfterEffectRemove += AuraEffectRemoveFn(spell_monk_crackling_jade_lightning_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_crackling_jade_lightning_AuraScript();
    }
};

// 117959 Crackling - Jade Lightning
class spell_monk_crackling_jade_lightning_aura : public SpellScriptLoader
{
public:
    spell_monk_crackling_jade_lightning_aura() : SpellScriptLoader("spell_monk_crackling_jade_lightning_aura") { }

    class spell_monk_crackling_jade_lightning_aura_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_crackling_jade_lightning_aura_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MONK_CRACKLING_JADE_LIGHTNING_HIDDEN_CD))
                return false;
            return true;
        }

        bool CheckProc(ProcEventInfo& /*eventInfo*/)
        {
            return !GetTarget()->HasAura(SPELL_MONK_CRACKLING_JADE_LIGHTNING_HIDDEN_CD);
        }

        void HandleProc(AuraEffect const* aurEff, ProcEventInfo& eventInfo)
        {
            GetTarget()->CastSpell(eventInfo.GetActor(), SPELL_MONK_CRACKLING_JADE_LIGHTNING_KNOCKBACK, true);
            GetTarget()->CastSpell(GetTarget(), SPELL_MONK_CRACKLING_JADE_LIGHTNING_HIDDEN_CD, true);
        }

        void Register() override
        {
            DoCheckProc += AuraCheckProcFn(spell_monk_crackling_jade_lightning_aura_AuraScript::CheckProc);
            OnEffectProc += AuraEffectProcFn(spell_monk_crackling_jade_lightning_aura_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_monk_crackling_jade_lightning_aura_AuraScript();
    }
};

void AddSC_monk_spell_scripts()
{
    new spell_monk_crackling_jade_lightning();
    new spell_monk_crackling_jade_lightning_aura();
}
