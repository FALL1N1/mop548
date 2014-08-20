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
 * Scripts for spells with SPELLFAMILY_DRUID and SPELLFAMILY_GENERIC spells used by druid players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_dru_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Containers.h"

enum DruidSpells
{
    SPELL_DRUID_TREANT_FORM                     = 114282,
    SPELL_DRUID_INCARNATION_KING_OF_THE_JUNGLE  = 102543,
    SPELL_DRUID_INCARNATION_CHOSEN_OF_ELUNE     = 102560,
    SPELL_DRUID_INCARNATION_SON_OF_URSOC        = 102558,
    SPELL_DRUID_CAT_FORM                        = 768,
    SPELL_DRUID_MOONKIN_FORM                    = 24858,
    SPELL_DRUID_BEAR_FORM                       = 5487
};

class spell_druid_glyph_of_the_treant : public SpellScriptLoader
{
public:
    spell_druid_glyph_of_the_treant() : SpellScriptLoader("spell_druid_glyph_of_the_treant") { }

    class spell_druid_glyph_of_the_treant_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_druid_glyph_of_the_treant_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_DRUID_TREANT_FORM))
                return false;
            return true;
        }

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Player* player = GetTarget()->ToPlayer())
                player->AddTemporarySpell(SPELL_DRUID_TREANT_FORM, true);
        }

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Player* player = GetTarget()->ToPlayer())
                player->RemoveTemporarySpell(SPELL_DRUID_TREANT_FORM, true);
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_druid_glyph_of_the_treant_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            OnEffectRemove += AuraEffectApplyFn(spell_druid_glyph_of_the_treant_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_druid_glyph_of_the_treant_AuraScript();
    }
};

class spell_druid_incarnation : public SpellScriptLoader
{
public:
    spell_druid_incarnation(const char* name, AuraType auraType) : SpellScriptLoader(name), _auraType(auraType) { }

    class spell_druid_incarnation_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_druid_incarnation_AuraScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_DRUID_CAT_FORM) || !sSpellMgr->GetSpellInfo(SPELL_DRUID_MOONKIN_FORM) ||
                !sSpellMgr->GetSpellInfo(SPELL_DRUID_BEAR_FORM))
                return false;
            return true;
        }

        bool Load()
        {
            switch (GetSpellInfo()->Id)
            {
                case SPELL_DRUID_INCARNATION_KING_OF_THE_JUNGLE:
                    _spellId = SPELL_DRUID_CAT_FORM;
                    _form = FORM_CAT;
                    break;
                case SPELL_DRUID_INCARNATION_CHOSEN_OF_ELUNE:
                    _spellId = SPELL_DRUID_MOONKIN_FORM;
                    _form = FORM_MOONKIN;
                    break;
                case SPELL_DRUID_INCARNATION_SON_OF_URSOC:
                    _spellId = SPELL_DRUID_BEAR_FORM;
                    _form = FORM_BEAR;
                    break;
                default:
                    return false;
            }

            return true;
        }

        void AfterApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (GetTarget()->GetShapeshiftForm() != _form)
                GetTarget()->CastSpell(GetTarget(), _spellId, true);
            else if (uint32 modelId = GetTarget()->GetModelForForm(_form))
                GetTarget()->SetDisplayId(modelId);
        }

        void AfterRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (GetTarget()->GetShapeshiftForm() == _form)
                if (uint32 modelId = GetTarget()->GetModelForForm(_form))
                    GetTarget()->SetDisplayId(modelId);
        }

        void Register() override
        {
            AfterEffectApply += AuraEffectApplyFn(spell_druid_incarnation_AuraScript::AfterApply, EFFECT_0, _auraType, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
            AfterEffectRemove += AuraEffectApplyFn(spell_druid_incarnation_AuraScript::AfterRemove, EFFECT_0, _auraType, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
        }

        private:
            AuraType _auraType;
            uint32 _spellId;
            ShapeshiftForm _form;

        public:
            spell_druid_incarnation_AuraScript(AuraType auraType) : _auraType(auraType) { }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_druid_incarnation_AuraScript(_auraType);
    }

    private:
        AuraType _auraType;
};

void AddSC_druid_spell_scripts()
{
    new spell_druid_glyph_of_the_treant();
    new spell_druid_incarnation("spell_druid_incarnation_king_of_the_jungle", SPELL_AURA_OVERRIDE_ACTIONBAR_SPELLS);
    new spell_druid_incarnation("spell_druid_incarnation_chosen_of_elune", SPELL_AURA_DUMMY);
    new spell_druid_incarnation("spell_druid_incarnation_son_of_ursoc", SPELL_AURA_ADD_PCT_MODIFIER);
}
