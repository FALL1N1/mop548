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
    WARRIOR_SPELL_MORTAL_STRIKE_AURA                = 12294,
    WARRIOR_SPELL_SUDDEN_DEATH_DRIVER               = 52437,
    WARRIOR_SPELL_COLOSSUS_SMASH                    = 86346
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
                            _player->CastSpell(_player, WARRIOR_SPELL_OVERPOWER_DRIVER, true);
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

class spell_warr_sudden_death : public SpellScriptLoader
{
public:
    spell_warr_sudden_death() : SpellScriptLoader("spell_warr_sudden_death") { }

    class spell_warr_sudden_death_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_sudden_death_AuraScript);

        void Sudden(AuraEffect const* /*aurEff*/, ProcEventInfo& /*eventInfo*/)
        {
            if (Player* player = GetOwner()->ToPlayer())
            {
                player->CastSpell(player, WARRIOR_SPELL_SUDDEN_DEATH_DRIVER);
                if (player->HasSpellCooldown(WARRIOR_SPELL_COLOSSUS_SMASH))
                    player->RemoveSpellCooldown(WARRIOR_SPELL_COLOSSUS_SMASH, true);
            }
        }

        void Register()
        {
            OnEffectProc += AuraEffectProcFn(spell_warr_sudden_death_AuraScript::Sudden, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warr_sudden_death_AuraScript();
    }
};

enum Charge
{
    SPELL_CHARGE                            = 100,
    SPELL_CHARGE_STUN                       = 7922,
    SPELL_WARBRINGER                        = 103828,
    SPELL_CHARGE_WARBRINGER_STUN            = 105771,
    SPELL_GLYPH_BLITZ                       = 58377,
    SPELL_GLYPH_BULL_RUSH                   = 94372,
    SPELL_RAGE_BONUS_15                     = 109128,
    SPELL_RAGE_BONUS_10                     = 12696,
    SPELL_CHARGE_WARBRINGER_SNARE           = 137637
};

// Charge - 100
class spell_warr_charge : public SpellScriptLoader
{
    public:
        spell_warr_charge() : SpellScriptLoader("spell_warr_charge") { }

        class spell_warr_charge_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_charge_SpellScript);

            bool Validate(SpellInfo const* /*SpellEntry*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_CHARGE))
                    return false;
                return true;
            }

            void HandleCharge(SpellEffIndex /*effIndex*/)
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        _player->Attack(target, true);
                        if (_player->HasAura(SPELL_WARBRINGER))
                        {
                            _player->CastSpell(target, SPELL_CHARGE_WARBRINGER_STUN, true);
                            _player->CastSpell(target, SPELL_CHARGE_WARBRINGER_SNARE, true);
                        }
                        else
                            _player->CastSpell(target, SPELL_CHARGE_STUN, true);

                        if (_player->HasAura(SPELL_GLYPH_BLITZ))
                            if (_player->HasAura(SPELL_WARBRINGER))
                            {
                                _player->CastSpell(target, SPELL_CHARGE_WARBRINGER_STUN, true);
                                _player->CastSpell(target, SPELL_CHARGE_WARBRINGER_SNARE, true);
                            }
                        else
                            _player->CastSpell(target, SPELL_CHARGE_STUN, true);

                        if (_player->HasAura(SPELL_GLYPH_BULL_RUSH))
                            _player->CastSpell(_player, SPELL_RAGE_BONUS_15, true);

                        _player->CastSpell(_player, SPELL_RAGE_BONUS_10, true);
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warr_charge_SpellScript::HandleCharge, EFFECT_0, SPELL_EFFECT_CHARGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_charge_SpellScript();
        }
};
enum ColossuSmash
{
    WARRIOR_SPELL_GLYPH_OF_COLOSSUS_SMASH       = 89003,
    WARRIOR_SPELL_SUNDER_ARMOR                  = 7386,
    WARRIOR_SPELL_PHYSICAL_VULNERABILITY        = 81326
};

// Colossus Smash - 86346
class spell_warr_colossus_smash : public SpellScriptLoader
{
    public:
        spell_warr_colossus_smash() : SpellScriptLoader("spell_warr_colossus_smash") { }

        class spell_warr_colossus_smash_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_colossus_smash_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                    {
                        _player->CastSpell(target, WARRIOR_SPELL_PHYSICAL_VULNERABILITY, true);

                        if (_player->HasAura(WARRIOR_SPELL_GLYPH_OF_COLOSSUS_SMASH))
                            _player->CastSpell(target, WARRIOR_SPELL_SUNDER_ARMOR, true);
                    }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_colossus_smash_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_colossus_smash_SpellScript();
        }
};
enum HeroicLeap
{
    WARRIOR_SPELL_DEATH_FROM_ABOVE_GLYPH        = 63325,
    WARRIOR_SPELL_HEROIC_LEAP_SPEED             = 133278,
    WARRIOR_SPELL_HEROIC_LEAP_DAMAGE            = 52174,
    WARRIOR_SPELL_ITEM_PVP_SET_4P_BONUS         = 133277
};

// Heroic leap - 6544
class spell_warr_heroic_leap : public SpellScriptLoader
{
    public:
        spell_warr_heroic_leap() : SpellScriptLoader("spell_warr_heroic_leap") { }

        class spell_warr_heroic_leap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_heroic_leap_SpellScript);

            std::list<Unit*> targetList;

            SpellCastResult CheckElevation()
            {
                Unit* caster = GetCaster();

                WorldLocation* dest = const_cast<WorldLocation*>(GetExplTargetDest());
                if (!dest)
                    return SPELL_FAILED_DONT_REPORT;
                else if (!caster->IsWithinLOS(dest->GetPositionX(), dest->GetPositionY(), dest->GetPositionZ()))
                    return SPELL_FAILED_LINE_OF_SIGHT;
                else if (dest->GetPositionZ() > caster->GetPositionZ() + 5.0f)
                    return SPELL_FAILED_NOPATH;
                else if (caster->HasAuraType(SPELL_AURA_MOD_ROOT))
                    return SPELL_FAILED_ROOTED;

                return SPELL_CAST_OK;
            }


            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_warr_heroic_leap_SpellScript::CheckElevation);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_heroic_leap_SpellScript();
        }

        class spell_warr_heroic_leap_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_heroic_leap_AuraScript);

            void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                    caster->CastSpell(caster, WARRIOR_SPELL_HEROIC_LEAP_DAMAGE, true);
            }

            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_warr_heroic_leap_AuraScript::OnRemove, EFFECT_2, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_heroic_leap_AuraScript();
        }
};

// Heroic Leap (damage) - 52174
class spell_warr_heroic_leap_damage : public SpellScriptLoader
{
    public:
        spell_warr_heroic_leap_damage() : SpellScriptLoader("spell_warr_heroic_leap_damage") { }

        class spell_warr_heroic_leap_damage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_heroic_leap_damage_SpellScript);

            void HandleAfterCast()
            {
                // Item - Warrior PvP Set 4P Bonus
                if (GetCaster()->HasAura(WARRIOR_SPELL_ITEM_PVP_SET_4P_BONUS))
                    GetCaster()->CastSpell(GetCaster(), WARRIOR_SPELL_HEROIC_LEAP_SPEED, true);
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_warr_heroic_leap_damage_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_heroic_leap_damage_SpellScript();
        }
};

class spell_warr_glyph_of_hamstring : public SpellScriptLoader
{
    public:
        spell_warr_glyph_of_hamstring() : SpellScriptLoader("spell_warr_glyph_of_hamstring") { }

        class spell_warr_glyph_of_hamstring_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_glyph_of_hamstring_SpellScript);

            void HandleOnCast()
            {
                if (Player* caster = GetCaster()->ToPlayer())
                    if (caster->HasAura(58385) && !caster->HasAura(115945)) // proc only from Hamstring if has glyph and if doesnt have reduc aura
                        caster->AddAura(115945, caster);
            }

            void Register()
            {
                OnCast += SpellCastFn(spell_warr_glyph_of_hamstring_SpellScript::HandleOnCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_glyph_of_hamstring_SpellScript();
        }
};
void AddSC_warrior_spell_scripts()
{
    new spell_warr_sword_and_board();
    new spell_warr_shield_block();
    new spell_warr_mortal_strike();
    new spell_warr_sudden_death();
    new spell_warr_charge();
    new spell_warr_colossus_smash();
    new spell_warr_heroic_leap();
    new spell_warr_heroic_leap_damage();
    new spell_warr_glyph_of_hamstring();
}
