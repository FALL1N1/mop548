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
 * Scripts for spells with SPELLFAMILY_WARRIOR and SPELLFAMILY_GENERIC spells used by warrior players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_warr_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum WarriorSpells
{
    WARRIOR_SPELL_RALLYING_CRY                      = 97463,
    WARRIOR_SPELL_SWORD_AND_BOARD                   = 50227,
    WARRIOR_SPELL_SHIELD_SLAM                       = 23922,
    WARRIOR_SPELL_SHIELD_BLOCK_TRIGGERED            = 132404,
    WARRIOR_SPELL_GLYPH_OF_MORTAL_STRIKE_AURA       = 58368,
    WARRIOR_SPELL_OVERPOWER_DRIVER_AURA             = 56636,
    WARRIOR_SPELL_OVERPOWER_DRIVER                  = 60503,
    WARRIOR_SPELL_MORTAL_STRIKE_AURA                = 12294
};

// Mortal strike - 12294
class spell_warr_mortal_strike : public SpellScriptLoader
{
    public:
        spell_warr_mortal_strike() : SpellScriptLoader("spell_warr_mortal_strike") { }

        class spell_warr_mortal_strike_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_mortal_strike_SpellScript);

            void HandleOnHit()
            {
                // Fix Apply Mortal strike buff on player only if he has the correct glyph
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (_player->HasAura(WARRIOR_SPELL_MORTAL_STRIKE_AURA))
                            if (!_player->HasAura(WARRIOR_SPELL_GLYPH_OF_MORTAL_STRIKE_AURA))
                                _player->RemoveAura(WARRIOR_SPELL_MORTAL_STRIKE_AURA);

                        if (_player->HasAura(WARRIOR_SPELL_OVERPOWER_DRIVER_AURA))
                        {
                            _player->AddComboPoints(target, 2);
                            _player->StartReactiveTimer(REACTIVE_OVERPOWER);
                            _player->CastSpell(_player, WARRIOR_SPELL_OVERPOWER_DRIVER, true);
                            _player->CastSpell(_player, WARRIOR_SPELL_OVERPOWER_DRIVER, true);
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_mortal_strike_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_mortal_strike_SpellScript();
        }
};
};

class spell_warr_sword_and_board : public SpellScriptLoader
{
public:
    spell_warr_sword_and_board() : SpellScriptLoader("spell_warr_sword_and_board") { }

    class spell_warr_sword_and_board_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_sword_and_board_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {
                    if (roll_chance_i(30))
                    {
                        _player->CastSpell(_player, WARRIOR_SPELL_SWORD_AND_BOARD, true);
                        _player->RemoveSpellCooldown(WARRIOR_SPELL_SHIELD_SLAM, true);
                    }
                }
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_warr_sword_and_board_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_sword_and_board_SpellScript();
    }
};

class spell_warr_shield_block : public SpellScriptLoader
{
public:
    spell_warr_shield_block() : SpellScriptLoader("spell_warr_shield_block") { }

    class spell_warr_shield_block_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warr_shield_block_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
                _player->CastSpell(_player, WARRIOR_SPELL_SHIELD_BLOCK_TRIGGERED, true);
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_warr_shield_block_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warr_shield_block_SpellScript();
    }
};

void AddSC_warrior_spell_scripts()
{
    new spell_warr_sword_and_board();
    new spell_warr_shield_block();
}
