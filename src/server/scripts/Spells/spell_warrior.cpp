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
    WARRIOR_SPELL_COLOSSUS_SMASH                    = 86346,
    WARRIOR_SPELL_OPPORUNITY_STRIKE                 = 76858,
    WARRIOR_SPELL_SWEEPING_STRIKES                  = 12328,
    WARRIOR_SPELL_SWEEPING_STRIKES_STRIKE           = 12723,
    WARRIOR_SPELL_SUDDEN_DEATH                      = 29725,
    WARRIOR_SPELL_SHIELD_BLOCK                      = 2565,
    WARRIOR_SPELL_DEVASTATE                         = 20243,
    WARRIOR_SPELL_MORTAL_STRIKE                     = 12294,
    WARRIOR_SPELL_SLAM_AOE                          = 146361,
    GLYPH_OF_SWEEPING_STRIKES_PASSIVE               = 58384,
    GLYPH_OF_SWEEPING_STRIKES_RAGE_BONUS            = 124333,
    SPELL_CHARGE                                    = 100,
    SPELL_CHARGE_STUN                               = 7922,
    SPELL_WARBRINGER                                = 103828,
    SPELL_CHARGE_WARBRINGER_STUN                    = 105771,
    SPELL_GLYPH_BLITZ                               = 58377,
    SPELL_GLYPH_BULL_RUSH                           = 94372,
    SPELL_RAGE_BONUS_15                             = 109128,
    SPELL_RAGE_BONUS_10                             = 12696,
    SPELL_CHARGE_WARBRINGER_SNARE                   = 137637,
    WARRIOR_SPELL_SECOND_WIND                       = 29838,
    WARRIOR_SPELL_SECOND_WIND_REGEN                 = 16491,
    SPELL_WARRIOR_STAGGERING_SHOUT                  = 107566,
    WARRIOR_SPELL_GLYPH_OF_HINDERING_STRIKES        = 58366,
    WARRIOR_SPELL_SLUGGISH                          = 129923,
    WARRIOR_SPELL_HEROIC_STRIKE                     = 78,
    WARRIOR_SPELL_CLEAVE                            = 845,
    WARRIOR_SPELL_GLYPH_OF_COLOSSUS_SMASH           = 89003,
    WARRIOR_SPELL_SUNDER_ARMOR                      = 7386,
    WARRIOR_SPELL_PHYSICAL_VULNERABILITY            = 81326,
    WARRIOR_SPELL_HEROIC_LEAP                       = 6544,
    WARRIOR_SPELL_DEATH_FROM_ABOVE_GLYPH            = 63325,
    WARRIOR_SPELL_HEROIC_LEAP_SPEED                 = 133278,
    WARRIOR_SPELL_HEROIC_LEAP_DAMAGE                = 52174,
    WARRIOR_SPELL_ITEM_PVP_SET_4P_BONUS             = 133277,
    SPELL_WARRIOR_GLYPH_OF_HAMSTRING_PASSIVE        = 58385,
    SPELL_WARRIOR_GLYPH_OF_HAMSTRING                = 115945,
    WARRIOR_SPELL_SHOCKWAVE_STUN                    = 132168,
    WARRIOR_SPELL_SHOCKWAVE                         = 46968,
    SPELL_WARRIOR_BLOODBATH                         = 12292,
    SPELL_WARRIOR_BLOODBATH_DEBUFF                  = 113344,
    SPELL_WARRIOR_DRAGON_ROAR                       = 118000,
    WARRIOR_SPELL_STORM_BOLT                        = 107570,
    WARRIOR_SPELL_STORM_BOLT_OFFHAND                = 145585,
    WARRIOR_SPELL_STORM_BOLT_STUN                   = 132169,
    WARRIOR_SPELL_OVERPOWER                         = 7384,
    WARRIOR_SPELL_HEROIC_THROW                      = 57755,
    WARRIOR_SPELL_PUMMEL                            = 6552,
    WARRIOR_SPELL_GAG_ORDER_PASSIVE                 = 58357,
    WARRIOR_SPELL_GAG_ORDER                         = 18498,
    WARRIOR_SPELL_SPELL_REFLECTION                  = 23920,
    WARRIOR_SPELL_MASS_REFLECT                      = 114028,
    WARRIOR_SPELL_SHIELD_WALL                       = 871
};

// Mortal strike - 12294
class spell_warr_mortal_strike : public SpellScriptLoader
{
    public:
        spell_warr_mortal_strike() : SpellScriptLoader("spell_warr_mortal_strike") { }

        bool Validate(SpellInfo const* /*SpellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(WARRIOR_SPELL_OVERPOWER_DRIVER_AURA)
                || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_MORTAL_STRIKE_AURA)
                || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_GLYPH_OF_MORTAL_STRIKE_AURA)
                || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_OVERPOWER_DRIVER)
                || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_MORTAL_STRIKE))
                return false;
            return true;
        }

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

        bool Validate(SpellInfo const* /*SpellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(WARRIOR_SPELL_DEVASTATE)
                || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_SWORD_AND_BOARD)
                || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_SHIELD_SLAM))
                return false;
            return true;
        }

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

        bool Validate(SpellInfo const* /*SpellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(WARRIOR_SPELL_SHIELD_BLOCK)
                || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_SHIELD_BLOCK_TRIGGERED))
                return false;
            return true;
        }

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

        bool Validate(SpellInfo const* /*SpellEntry*/)
        {
            if (!sSpellMgr->GetSpellInfo(WARRIOR_SPELL_SUDDEN_DEATH)
                || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_OPPORUNITY_STRIKE)
                || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_SUDDEN_DEATH_DRIVER)
                || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_COLOSSUS_SMASH))
                return false;
            return true;
        }

        void Sudden(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetDamageInfo()->GetSpellInfo())
                if (eventInfo.GetDamageInfo()->GetSpellInfo()->Id != WARRIOR_SPELL_OPPORUNITY_STRIKE)
                    return;

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
                if (!sSpellMgr->GetSpellInfo(SPELL_CHARGE)
                    || !sSpellMgr->GetSpellInfo(SPELL_CHARGE_STUN)
                    || !sSpellMgr->GetSpellInfo(SPELL_WARBRINGER)
                    || !sSpellMgr->GetSpellInfo(SPELL_CHARGE_WARBRINGER_STUN)
                    || !sSpellMgr->GetSpellInfo(SPELL_GLYPH_BLITZ)
                    || !sSpellMgr->GetSpellInfo(SPELL_GLYPH_BULL_RUSH)
                    || !sSpellMgr->GetSpellInfo(SPELL_RAGE_BONUS_15)
                    || !sSpellMgr->GetSpellInfo(SPELL_RAGE_BONUS_10)
                    || !sSpellMgr->GetSpellInfo(SPELL_CHARGE_WARBRINGER_SNARE))
                    return false;
                return true;
            }

            void HandleCharge(SpellEffIndex /*effIndex*/)
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
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

// Second Wind - 29838
class spell_warr_second_wind : public SpellScriptLoader
{
    public:
        spell_warr_second_wind() : SpellScriptLoader("spell_warr_second_wind") { }

        class spell_warr_second_wind_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_second_wind_SpellScript);

            bool Validade(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(WARRIOR_SPELL_SECOND_WIND)
                    || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_SECOND_WIND_REGEN))
                    return false;
                return true;
            }

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    _player->CastSpell(_player, WARRIOR_SPELL_SECOND_WIND_REGEN, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_second_wind_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_second_wind_SpellScript();
        }

        class spell_warr_second_wind_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warr_second_wind_AuraScript);

            bool Validade(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(WARRIOR_SPELL_SECOND_WIND)
                    || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_SECOND_WIND_REGEN))
                    return false;
                return true;
            }

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                    if (caster->HasAura(WARRIOR_SPELL_SECOND_WIND_REGEN))
                        caster->RemoveAura(WARRIOR_SPELL_SECOND_WIND_REGEN);
            }

            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_warr_second_wind_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_second_wind_AuraScript();
        }
};

// Called by Heroic Strike - 78 and Cleave - 845
// Glyph of Hindering Strikes - 58366
class spell_warr_glyph_of_hindering_strikes : public SpellScriptLoader
{
    public:
        spell_warr_glyph_of_hindering_strikes() : SpellScriptLoader("spell_warr_glyph_of_hindering_strikes") { }

        class spell_warr_glyph_of_hindering_strikes_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_glyph_of_hindering_strikes_SpellScript);

            bool Validade(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(WARRIOR_SPELL_HEROIC_STRIKE)
                    || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_CLEAVE)
                    || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_SLUGGISH)
                    || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_GLYPH_OF_HINDERING_STRIKES))
                    return false;
                return true;
            }

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        if (_player->HasAura(WARRIOR_SPELL_GLYPH_OF_HINDERING_STRIKES))
                            _player->CastSpell(target, WARRIOR_SPELL_SLUGGISH, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_glyph_of_hindering_strikes_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_glyph_of_hindering_strikes_SpellScript();
        }
};

// Colossus Smash - 86346
class spell_warr_colossus_smash : public SpellScriptLoader
{
    public:
        spell_warr_colossus_smash() : SpellScriptLoader("spell_warr_colossus_smash") { }

        class spell_warr_colossus_smash_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_colossus_smash_SpellScript);

            bool Validade(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(WARRIOR_SPELL_COLOSSUS_SMASH)
                    || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_PHYSICAL_VULNERABILITY)
                    || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_GLYPH_OF_COLOSSUS_SMASH)
                    || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_SUNDER_ARMOR))
                    return false;
                return true;
            }

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

// Heroic leap - 6544
class spell_warr_heroic_leap : public SpellScriptLoader
{
    public:
        spell_warr_heroic_leap() : SpellScriptLoader("spell_warr_heroic_leap") { }

        class spell_warr_heroic_leap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_heroic_leap_SpellScript);

            bool Validade(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(WARRIOR_SPELL_HEROIC_LEAP)
                    || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_HEROIC_LEAP_DAMAGE))
                    return false;
                return true;
            }

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

            bool Validade(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(WARRIOR_SPELL_ITEM_PVP_SET_4P_BONUS)
                    || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_HEROIC_LEAP_SPEED)
                    || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_HEROIC_LEAP_DAMAGE))
                    return false;
                return true;
            }

            void Recalc()
            {
                int32 dmg = GetHitDamage();
                if (Player* caster = GetCaster()->ToPlayer())
                    if (caster->GetSpecializationId(caster->GetActiveSpec()) == CHAR_SPECIALIZATION_WARRIOR_ARMS)
                        dmg += CalculatePct(caster->GetTotalAttackPowerValue(BASE_ATTACK), 60.0f);
                    else
                        dmg += CalculatePct(caster->GetTotalAttackPowerValue(BASE_ATTACK), 50.0f);

                SetHitDamage(dmg);
            }

            void HandleAfterCast()
            {
                // Item - Warrior PvP Set 4P Bonus
                if (GetCaster()->HasAura(WARRIOR_SPELL_ITEM_PVP_SET_4P_BONUS))
                    GetCaster()->CastSpell(GetCaster(), WARRIOR_SPELL_HEROIC_LEAP_SPEED, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_heroic_leap_damage_SpellScript::Recalc);
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

            bool Validade(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_GLYPH_OF_HAMSTRING_PASSIVE)
                    || sSpellMgr->GetSpellInfo(SPELL_WARRIOR_GLYPH_OF_HAMSTRING))
                    return false;
                return true;
            }

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

// Staggering Shout - 107566
class spell_warr_staggering_shout : public SpellScriptLoader
{
    public:
        spell_warr_staggering_shout() : SpellScriptLoader("spell_warr_staggering_shout") { }

        class spell_warr_staggering_shout_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_staggering_shout_SpellScript);

            bool Validade(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_STAGGERING_SHOUT))
                    return false;
                return true;
            }

            void RemoveInvalidTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(Trinity::UnitAuraTypeCheck(false, SPELL_AURA_MOD_DECREASE_SPEED));
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warr_staggering_shout_SpellScript::RemoveInvalidTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_staggering_shout_SpellScript();
        }
};

// Shockwave - 46968
class spell_warr_shockwave : public SpellScriptLoader
{
    public:
        spell_warr_shockwave() : SpellScriptLoader("spell_warr_shockwave") { }

        class spell_warr_shockwave_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_shockwave_SpellScript);

            bool Load() override
            {
                count = 0;
                return true;
            }

            bool Validade(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(WARRIOR_SPELL_SHOCKWAVE)
                    || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_SHOCKWAVE_STUN))
                    return false;
                return true;
            }

            void Count(std::list<WorldObject*>& targets)
            {
                count = targets.size();
            }

            void HandleOnHit(SpellEffIndex /*eff*/)
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        _player->CastSpell(target, WARRIOR_SPELL_SHOCKWAVE_STUN);
            }

            void HandleReduc(SpellEffIndex eff)
            {
                if (count >= 3)
                    if (Player* _player = GetCaster()->ToPlayer())
                        _player->ModifySpellCooldown(WARRIOR_SPELL_SHOCKWAVE, -int32(GetSpellInfo()->Effects[eff].BasePoints * IN_MILLISECONDS));
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warr_shockwave_SpellScript::Count, EFFECT_0, TARGET_UNIT_CONE_ENEMY_104);
                OnEffectHitTarget += SpellEffectFn(spell_warr_shockwave_SpellScript::HandleOnHit, EFFECT_0, SPELL_EFFECT_DUMMY);
                OnEffectHit += SpellEffectFn(spell_warr_shockwave_SpellScript::HandleReduc, EFFECT_3, SPELL_EFFECT_SCRIPT_EFFECT);
            }

            private:
                uint8 count;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_shockwave_SpellScript();
        }
};

// 12292 Bloodbath
class spell_warr_bloodbath : public SpellScriptLoader
{
public:
    spell_warr_bloodbath() : SpellScriptLoader("spell_warr_bloodbath") { }

    class spell_warr_bloodbath_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_bloodbath_AuraScript);

        bool Validade(SpellInfo const* /*spellInfo*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_BLOODBATH)
                || !sSpellMgr->GetSpellInfo(SPELL_WARRIOR_BLOODBATH_DEBUFF))
                return false;
            return true;
        }

        void Bloodbath(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
        {
            if (!eventInfo.GetDamageInfo()->GetSpellInfo()) // if no proc spell
                return;

            if (!eventInfo.GetDamageInfo()->GetVictim())
                return;

            if (Player* player = GetOwner()->ToPlayer())
            {
                uint32 dmg = eventInfo.GetDamageInfo()->GetDamage();
                int32 bp = int32(CalculatePct(dmg, 30) / 6); // damage / tick_number
                if (Aura* bloodbath = eventInfo.GetDamageInfo()->GetVictim()->GetAura(SPELL_WARRIOR_BLOODBATH_DEBUFF))
                {
                    if (AuraEffect* bloodbath_e = bloodbath->GetEffect(EFFECT_0))
                    {
                        bp += bloodbath_e->GetAmount();
                        bloodbath_e->ChangeAmount(bp);
                        bloodbath->SetNeedClientUpdateForTargets(); // ap doesnt update on aura bar
                    }
                }
                else
                    player->CastCustomSpell(eventInfo.GetDamageInfo()->GetVictim(), SPELL_WARRIOR_BLOODBATH_DEBUFF, &bp, NULL, NULL, true);
            }
        }

        void Register()
        {
            OnEffectProc += AuraEffectProcFn(spell_warr_bloodbath_AuraScript::Bloodbath, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warr_bloodbath_AuraScript();
    }
};

class spell_warr_dragon_roar : public SpellScriptLoader
{
    public:
        spell_warr_dragon_roar() : SpellScriptLoader("spell_warr_dragon_roar") { }

        class spell_warr_dragon_roar_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_dragon_roar_SpellScript);

            bool Validade(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_WARRIOR_DRAGON_ROAR))
                    return false;
                return true;
            }

            void Recalculate()
            {
                int32 dmg = GetHitDamage();
                if (Player* caster = GetCaster()->ToPlayer())
                    if (caster->GetSpecializationId(caster->GetActiveSpec()) == CHAR_SPECIALIZATION_WARRIOR_ARMS)
                        dmg += CalculatePct(caster->GetTotalAttackPowerValue(BASE_ATTACK), 168.0f);
                    else
                        dmg += CalculatePct(caster->GetTotalAttackPowerValue(BASE_ATTACK), 140.0f);

                SetHitDamage(dmg);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_dragon_roar_SpellScript::Recalculate);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_dragon_roar_SpellScript();
        }
};

// 1464
class spell_warr_slam : public SpellScriptLoader
{
    public:
        spell_warr_slam() : SpellScriptLoader("spell_warr_slam") { }

        class spell_warr_slam_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_slam_SpellScript);

            bool Validade(SpellInfo const* /*spellInfo*/)
            {
                if (!sSpellMgr->GetSpellInfo(WARRIOR_SPELL_SWEEPING_STRIKES)
                    || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_COLOSSUS_SMASH)
                    || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_SLAM_AOE))
                    return false;
                return true;
            }

            void HandleOnHit()
            {
                if (GetHitUnit()->HasAura(WARRIOR_SPELL_COLOSSUS_SMASH))
                    SetHitDamage(GetHitDamage() * 1.10f);

                if (GetCaster()->HasAura(WARRIOR_SPELL_SWEEPING_STRIKES))
                {
                    int32 bp = GetHitDamage() * 0.35f;
                    std::list<Unit*> slammable;
                    GetCaster()->GetAttackableUnitListInRange(slammable, 2.0f);
                    slammable.remove(GetHitUnit());
                    for (auto itr : slammable)
                        GetCaster()->CastCustomSpell(itr, WARRIOR_SPELL_SLAM_AOE, &bp, NULL, NULL, false);
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_slam_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_slam_SpellScript();
        }
};

// 12328
class spell_warr_sweeping_strikes : public SpellScriptLoader
{
public:
    spell_warr_sweeping_strikes() : SpellScriptLoader("spell_warr_sweeping_strikes") { }

    class spell_warr_sweeping_strikes_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warr_sweeping_strikes_AuraScript);

        bool Validade(SpellInfo const* /*spellInfo*/)
        {
            if (!sSpellMgr->GetSpellInfo(WARRIOR_SPELL_OPPORUNITY_STRIKE)
                || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_SWEEPING_STRIKES_STRIKE)
                || !sSpellMgr->GetSpellInfo(GLYPH_OF_SWEEPING_STRIKES_RAGE_BONUS)
                || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_SWEEPING_STRIKES)
                || !sSpellMgr->GetSpellInfo(GLYPH_OF_SWEEPING_STRIKES_PASSIVE))
                return false;
            return true;
        }

        void Sweeping(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
        {
            if (eventInfo.GetDamageInfo()->GetSpellInfo())
                if (eventInfo.GetDamageInfo()->GetSpellInfo()->Id != WARRIOR_SPELL_OPPORUNITY_STRIKE)
                    return;

            int32 damage = eventInfo.GetDamageInfo()->GetDamage() / 2;
            if (Unit* target = GetCaster()->SelectNearbyTarget(eventInfo.GetDamageInfo()->GetVictim()))
            {
                GetCaster()->CastCustomSpell(target, WARRIOR_SPELL_SWEEPING_STRIKES_STRIKE, &damage, NULL, NULL, true);

                // Glyph of Sweeping Strikes
                if (GetCaster()->HasAura(GLYPH_OF_SWEEPING_STRIKES_PASSIVE))
                    GetCaster()->CastSpell(GetCaster(), GLYPH_OF_SWEEPING_STRIKES_RAGE_BONUS);
            }
        }

        void Register()
        {
            OnEffectProc += AuraEffectProcFn(spell_warr_sweeping_strikes_AuraScript::Sweeping, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warr_sweeping_strikes_AuraScript();
    }
};

// Storm Bolt - 107570
class spell_warr_storm_bolt : public SpellScriptLoader
{
    public:
        spell_warr_storm_bolt() : SpellScriptLoader("spell_warr_storm_bolt") { }

        class spell_warr_storm_bolt_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_storm_bolt_SpellScript);

            bool Validate(SpellInfo const* /*info*/)
            {
                if (!sSpellMgr->GetSpellInfo(WARRIOR_SPELL_STORM_BOLT_STUN)
                    || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_STORM_BOLT)
                    || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_STORM_BOLT_OFFHAND))
                    return false;
                return true;
            }

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* unitTarget = GetHitUnit())
                    {
                        if (unitTarget->GetDiminishing(DIMINISHING_STUN) == DIMINISHING_LEVEL_IMMUNE
                            || unitTarget->GetDiminishing(DIMINISHING_CONTROLLED_STUN) == DIMINISHING_LEVEL_IMMUNE)
                            SetHitDamage(int32(CalculatePct(GetHitDamage(), 500.0f)));

                        if (GetSpellInfo()->Id == WARRIOR_SPELL_STORM_BOLT)
                            _player->CastSpell(unitTarget, WARRIOR_SPELL_STORM_BOLT_STUN, true);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_storm_bolt_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_storm_bolt_SpellScript();
        }
};

// Overpower - 7384
class spell_warr_overpower : public SpellScriptLoader
{
    public:
        spell_warr_overpower() : SpellScriptLoader("spell_warr_overpower") { }

        class spell_warr_overpower_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_overpower_SpellScript);

            bool Validate(SpellInfo const* /*info*/)
            {
                if (!sSpellMgr->GetSpellInfo(WARRIOR_SPELL_OVERPOWER)
                    || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_MORTAL_STRIKE))
                    return false;
                return true;
            }

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    _player->ModifySpellCooldown(WARRIOR_SPELL_MORTAL_STRIKE, -500);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_overpower_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_overpower_SpellScript();
        }
};

// Glyph of Gag Order (57755, 6552)
class spell_warr_glyph_of_gag_order : public SpellScriptLoader
{
    public:
        spell_warr_glyph_of_gag_order() : SpellScriptLoader("spell_warr_glyph_of_gag_order") { }

        class spell_warr_glyph_of_gag_order_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warr_glyph_of_gag_order_SpellScript);

            bool Validate(SpellInfo const* /*info*/)
            {
                if (!sSpellMgr->GetSpellInfo(WARRIOR_SPELL_HEROIC_THROW)
                    || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_PUMMEL))
                    return false;
                return true;
            }

            void HandleOnHit()
            {
                if (GetCaster()->HasAura(WARRIOR_SPELL_GAG_ORDER_PASSIVE))
                    GetCaster()->CastSpell(GetHitUnit(), WARRIOR_SPELL_GAG_ORDER);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warr_glyph_of_gag_order_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warr_glyph_of_gag_order_SpellScript();
        }
};

enum ShieldVisuals
{
    REFLECT_VISUAL_SHIELD = 146120,
    REFLECT_VISUAL_NO_SHIELD_HORDE = 146122,
    REFLECT_VISUAL_NO_SHIELD_ALLIANCE = 147925,
    SHIELD_WALL_VISUAL_SHIELD = 146128,
    SHIELD_WALL_VISUAL_NO_SHIELD_HORDE = 146127,
    SHIELD_WALL_VISUAL_NO_SHIELD_ALLIANCE = 147925
};

// Shield Wall: 871; Reflects: 23920, 114028
class spell_warr_shields_visual : public SpellScriptLoader
{
    public:
        spell_warr_shields_visual() : SpellScriptLoader("spell_warr_shields_visual") { }

        class spell_warr_shields_visual_Auracript : public AuraScript
        {
            PrepareAuraScript(spell_warr_shields_visual_Auracript);

            bool Validate(SpellInfo const* /*info*/)
            {
                if (!sSpellMgr->GetSpellInfo(WARRIOR_SPELL_SHIELD_WALL)
                    || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_MASS_REFLECT)
                    || !sSpellMgr->GetSpellInfo(WARRIOR_SPELL_SPELL_REFLECTION))
                    return false;
                return true;
            }

            bool HasShieldEquipped(Player* player)
            {
                if (player->haveOffhandWeapon())
                    if (Item* item = player->GetItemByPos(EQUIPMENT_SLOT_OFFHAND))
                        if (item->GetTemplate()->SubClass == ITEM_SUBCLASS_ARMOR_SHIELD)
                            return true;
                return false;
            }

            void Visuals(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    if (Player* target = GetOwner()->ToPlayer())
                    {
                        switch (GetSpellInfo()->Id)
                        {
                            case WARRIOR_SPELL_SHIELD_WALL:
                            {
                                target->CastSpell(target, HasShieldEquipped(target) ? SHIELD_WALL_VISUAL_SHIELD : (target->GetTeam() == ALLIANCE ? SHIELD_WALL_VISUAL_NO_SHIELD_ALLIANCE : SHIELD_WALL_VISUAL_NO_SHIELD_HORDE));
                                break;
                            }
                            case WARRIOR_SPELL_MASS_REFLECT:
                            case WARRIOR_SPELL_SPELL_REFLECTION:
                            {
                                target->CastSpell(target, HasShieldEquipped(target) ? REFLECT_VISUAL_SHIELD : (target->GetTeam() == ALLIANCE ? REFLECT_VISUAL_NO_SHIELD_ALLIANCE : REFLECT_VISUAL_NO_SHIELD_HORDE));
                                break;
                            }
                        }
                    }
                }
            }

            void VisualsRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                switch (GetSpellInfo()->Id)
                {
                    case WARRIOR_SPELL_SHIELD_WALL:
                    {
                        GetOwner()->ToPlayer()->RemoveAurasDueToSpell(SHIELD_WALL_VISUAL_SHIELD);
                        GetOwner()->ToPlayer()->RemoveAurasDueToSpell(SHIELD_WALL_VISUAL_NO_SHIELD_ALLIANCE);
                        GetOwner()->ToPlayer()->RemoveAurasDueToSpell(SHIELD_WALL_VISUAL_NO_SHIELD_HORDE);
                        break;
                    }
                    case WARRIOR_SPELL_MASS_REFLECT:
                    case WARRIOR_SPELL_SPELL_REFLECTION:
                    {
                        GetOwner()->ToPlayer()->RemoveAurasDueToSpell(REFLECT_VISUAL_SHIELD);
                        GetOwner()->ToPlayer()->RemoveAurasDueToSpell(REFLECT_VISUAL_NO_SHIELD_ALLIANCE);
                        GetOwner()->ToPlayer()->RemoveAurasDueToSpell(REFLECT_VISUAL_NO_SHIELD_HORDE);
                        break;
                    }
                }
                
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warr_shields_visual_Auracript::Visuals, EFFECT_0, SPELL_AURA_REFLECT_SPELLS, AURA_EFFECT_HANDLE_REAL);
                OnEffectApply += AuraEffectApplyFn(spell_warr_shields_visual_Auracript::Visuals, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_warr_shields_visual_Auracript::VisualsRemove, EFFECT_0, SPELL_AURA_REFLECT_SPELLS, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_warr_shields_visual_Auracript::VisualsRemove, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warr_shields_visual_Auracript();
        }
};

void AddSC_warrior_spell_scripts()
{
    new spell_warr_sword_and_board();
    new spell_warr_shield_block();
    new spell_warr_mortal_strike();
    new spell_warr_sudden_death();
    new spell_warr_charge();
    new spell_warr_second_wind();
    new spell_warr_glyph_of_hindering_strikes();
    new spell_warr_colossus_smash();
    new spell_warr_heroic_leap();
    new spell_warr_heroic_leap_damage();
    new spell_warr_glyph_of_hamstring();
    new spell_warr_staggering_shout();
    new spell_warr_shockwave();
    new spell_warr_bloodbath();
    new spell_warr_dragon_roar();
    new spell_warr_slam();
    new spell_warr_sweeping_strikes();
    new spell_warr_storm_bolt();
    new spell_warr_overpower();
    new spell_warr_glyph_of_gag_order();
    new spell_warr_shields_visual();
}
