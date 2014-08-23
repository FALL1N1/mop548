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
 * Scripts for spells with SPELLFAMILY_PALADIN and SPELLFAMILY_GENERIC spells used by paladin players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_pal_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Group.h"

enum PaladinSpells
{

};

enum MiscSpells
{
    SPELL_GENERIC_ARENA_DAMPENING                = 74410,
    SPELL_GENERIC_BATTLEGROUND_DAMPENING         = 74411
};

enum PaladinSpellIcons
{
    PALADIN_ICON_ID_RETRIBUTION_AURA             = 555
};

enum HolyShockSpells
{
    SPELL_HOLY_SHOCK = 20473,
    SPELL_HOLY_SHOCK_DMG = 25912,
    SPELL_HOLY_SHOCK_HEAL = 25914,
    SPELL_HOLY_SHOCK_ADD_HOLY_POWER = 148976

};
class spell_pal_holy_shock : public SpellScriptLoader
{
public:
    spell_pal_holy_shock() : SpellScriptLoader("spell_pal_holy_shock") { }

    class spell_pal_holy_shock_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_holy_shock_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_HOLY_SHOCK))
                return false;
            return true;
        }


        void HandleDummyHitTarget(SpellEffIndex /*effIndex*/)
        {
            // make caster cast a spell on a unit target of effect
            if (Unit* target = GetHitUnit())
            {
                if (target->IsFriendlyTo(GetCaster()))
                    GetCaster()->CastSpell(target, SPELL_HOLY_SHOCK_HEAL, true);
                else
                    GetCaster()->CastSpell(target, SPELL_HOLY_SHOCK_DMG, true);
                
                GetCaster()->CastSpell(GetCaster(), SPELL_HOLY_SHOCK_ADD_HOLY_POWER, true);
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_pal_holy_shock_SpellScript::HandleDummyHitTarget, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_pal_holy_shock_SpellScript();
    }
};




void AddSC_paladin_spell_scripts()
{
    new spell_pal_holy_shock();
}
