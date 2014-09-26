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
 * Scripts for spells with SPELLFAMILY_ROGUE and SPELLFAMILY_GENERIC spells used by rogue players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_rog_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum RogueSpells
{
    SPELL_ROGUE_CRIMSON_TEMPEST                     = 121411,
    SPELL_ROGUE_CRIMSON_TEMPEST_DOT                 = 122233,
    SPELL_ROGUE_CRIPPLING_POISON                    = 3408,
    SPELL_ROGUE_DEADLY_POISON                       = 2823,
    SPELL_ROGUE_DEBILITATING_POISON                 = 115196,
    SPELL_ROGUE_EVESCERATE_AND_ENVENOM_BONUS_DMG    = 37169,
    SPELL_ROGUE_GLYPH_OF_HEMORRHAGE                 = 56807,
    SPELL_ROGUE_HEMORRHAGE_DOT                      = 89775,
    SPELL_ROGUE_LEECH_VITALITY                      = 116921,
    SPELL_ROGUE_LEECHING_POISON                     = 108211,
    SPELL_ROGUE_MASTERY_EXECUTIONER                 = 76808,
    SPELL_ROGUE_MIND_NUMBLING_POISON                = 5761,
    SPELL_ROGUE_MIND_PARALYSIS                      = 115194,
    SPELL_ROGUE_NIGHTSTALKER_AURA                   = 14062,
    SPELL_ROGUE_NIGHTSTALKER_DAMAGE_DONE            = 130493,
    SPELL_ROGUE_PARALYTIC_POISON                    = 108215,
    SPELL_ROGUE_PARALYTIC_POISON_DEBUFF             = 113952,
    SPELL_ROGUE_PARTIAL_PARALYSIS                   = 115197,
    SPELL_ROGUE_RUPTURE_DOT                         = 1943,
    SPELL_ROGUE_SHADOW_FOCUS_AURA                   = 108209,
    SPELL_ROGUE_SHADOW_FOCUS_COST_PCT               = 112942,
    SPELL_ROGUE_SHROUD_OF_CONCEALMENT_AURA          = 115834,
    SPELL_ROGUE_SLICE_AND_DICE                      = 5171,
    SPELL_ROGUE_SMOKE_BOMB                          = 88611,
    SPELL_ROGUE_TOTAL_PARALYSIS                     = 113953,
    SPELL_ROGUE_WOUND_POISON                        = 8679,
};

class spell_rog_smoke_bomb : public SpellScriptLoader
{
public:
	spell_rog_smoke_bomb() : SpellScriptLoader("spell_rog_smoke_bomb") { }

	class spell_rog_smoke_bomb_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_rog_smoke_bomb_AuraScript);

		void EffectPeriodic(AuraEffect const* /*aurEff*/)
		{
			if (DynamicObject* dynObject = GetCaster()->GetDynObject(GetSpellInfo()->Id))
			{
                float x, y, z;
				dynObject->GetPosition(x, y, z);
				GetCaster()->CastSpell(x, y, z, SPELL_ROGUE_SMOKE_BOMB, true);
			}
		}

		void Register()
		{
			OnEffectPeriodic += AuraEffectPeriodicFn(spell_rog_smoke_bomb_AuraScript::EffectPeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
		}    
	};

	AuraScript* GetAuraScript() const
	{
		return new spell_rog_smoke_bomb_AuraScript();
	}
};

class spell_rog_nightstalker : public SpellScriptLoader
{
public:
    spell_rog_nightstalker() : SpellScriptLoader("spell_rog_nightstalker") { }

    class spell_rog_nightstalker_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_nightstalker_SpellScript);

        void HandleOnHit()
        {
            if (!GetCaster())
                return;

            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (_player->HasAura(SPELL_ROGUE_NIGHTSTALKER_AURA))
                    _player->CastSpell(_player, SPELL_ROGUE_NIGHTSTALKER_DAMAGE_DONE, true);

                if (_player->HasAura(SPELL_ROGUE_SHADOW_FOCUS_AURA))
                    _player->CastSpell(_player, SPELL_ROGUE_SHADOW_FOCUS_COST_PCT, true);
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_rog_nightstalker_SpellScript::HandleOnHit);
        }
    };

    class spell_rog_nightstalker_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_rog_nightstalker_AuraScript);

        void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
        {
            if (!GetCaster())
                return;

            if (GetCaster()->HasAura(SPELL_ROGUE_NIGHTSTALKER_DAMAGE_DONE))
                GetCaster()->RemoveAura(SPELL_ROGUE_NIGHTSTALKER_DAMAGE_DONE);

            if (GetCaster()->HasAura(SPELL_ROGUE_SHADOW_FOCUS_COST_PCT))
                GetCaster()->RemoveAura(SPELL_ROGUE_SHADOW_FOCUS_COST_PCT);
        }

        void Register()
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_rog_nightstalker_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_rog_nightstalker_SpellScript();
    }

    AuraScript* GetAuraScript() const
    {
        return new spell_rog_nightstalker_AuraScript();
    }
};

class spell_rog_hemorrhage : public SpellScriptLoader
{
public:
    spell_rog_hemorrhage() : SpellScriptLoader("spell_rog_hemorrhage") { }

    class spell_rog_hemorrhage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_hemorrhage_SpellScript);

        void HandleOnHit()
        {
            if (!GetCaster() || !GetHitUnit())
                return;

            Player* caster = GetCaster()->ToPlayer();
            Unit* target = GetHitUnit();

            if (caster->HasAura(SPELL_ROGUE_GLYPH_OF_HEMORRHAGE))
            {
                if (!target->HasAuraState(AURA_STATE_BLEEDING))
                    return;
            }
            
            int32 bp = GetHitDamage() / 2 / 8;
            caster->CastCustomSpell(target, SPELL_ROGUE_HEMORRHAGE_DOT, &bp, NULL, NULL, true);
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_rog_hemorrhage_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_rog_hemorrhage_SpellScript();
    }
};

class spell_rog_crimson_tempest : public SpellScriptLoader
{
public:
    spell_rog_crimson_tempest() : SpellScriptLoader("spell_rog_crimson_tempest") { }

    class spell_rog_crimson_tempest_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_crimson_tempest_SpellScript);

        void HandleOnHit()
        {
            if (!GetCaster() || !GetHitUnit())
                return;

            Player* caster = GetCaster()->ToPlayer();
            Unit* target = GetHitUnit();

            int32 damage = int32(GetHitDamage() * 0.30f / 6);
            caster->CastCustomSpell(target, SPELL_ROGUE_CRIMSON_TEMPEST_DOT, &damage, NULL, NULL, true);
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_rog_crimson_tempest_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_rog_crimson_tempest_SpellScript();
    }
};

class spell_rog_shiv : public SpellScriptLoader
{
public:
    spell_rog_shiv() : SpellScriptLoader("spell_rog_shiv") { }

    class spell_rog_shiv_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_shiv_SpellScript);

        void HandleOnHit()
        {
            if (!GetCaster() || !GetHitUnit())
                return;

            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {
                    if (_player->HasAura(SPELL_ROGUE_MIND_NUMBLING_POISON))
                        _player->CastSpell(target, SPELL_ROGUE_MIND_PARALYSIS, true);
                    else if (_player->HasAura(SPELL_ROGUE_CRIPPLING_POISON))
                        _player->CastSpell(target, SPELL_ROGUE_DEBILITATING_POISON, true);
                    else if (_player->HasAura(SPELL_ROGUE_LEECHING_POISON))
                        _player->CastSpell(_player, SPELL_ROGUE_LEECH_VITALITY, true);
                    else if (_player->HasAura(SPELL_ROGUE_PARALYTIC_POISON))
                        _player->CastSpell(target, SPELL_ROGUE_PARTIAL_PARALYSIS, true);
                }
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_rog_shiv_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_rog_shiv_SpellScript();
    }
};

class spell_rog_poisons : public SpellScriptLoader
{
public:
    spell_rog_poisons() : SpellScriptLoader("spell_rog_poisons") { }

    class spell_rog_poisons_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_poisons_SpellScript);

        void HandleOnHit()
        {
            if (!GetCaster())
                return;

            Player* caster = GetCaster()->ToPlayer();

            switch (GetSpellInfo()->Id)
            {
                case SPELL_ROGUE_WOUND_POISON:
                {
                    if (caster->HasAura(SPELL_ROGUE_DEADLY_POISON))
                        caster->RemoveAura(SPELL_ROGUE_DEADLY_POISON);
                    break;
                }
                case SPELL_ROGUE_MIND_NUMBLING_POISON:
                {
                    if (caster->HasAura(SPELL_ROGUE_CRIPPLING_POISON))
                        caster->RemoveAura(SPELL_ROGUE_CRIPPLING_POISON);

                    if (caster->HasAura(SPELL_ROGUE_LEECHING_POISON))
                        caster->RemoveAura(SPELL_ROGUE_LEECHING_POISON);

                    if (caster->HasAura(SPELL_ROGUE_PARALYTIC_POISON))
                        caster->RemoveAura(SPELL_ROGUE_PARALYTIC_POISON);
                    break;
                }
                case SPELL_ROGUE_CRIPPLING_POISON:
                {
                    if (caster->HasAura(SPELL_ROGUE_MIND_NUMBLING_POISON))
                        caster->RemoveAura(SPELL_ROGUE_MIND_NUMBLING_POISON);

                    if (caster->HasAura(SPELL_ROGUE_LEECHING_POISON))
                        caster->RemoveAura(SPELL_ROGUE_LEECHING_POISON);

                    if (caster->HasAura(SPELL_ROGUE_PARALYTIC_POISON))
                        caster->RemoveAura(SPELL_ROGUE_PARALYTIC_POISON);
                    break;
                }
                case SPELL_ROGUE_LEECHING_POISON:
                {
                    if (caster->HasAura(SPELL_ROGUE_MIND_NUMBLING_POISON))
                        caster->RemoveAura(SPELL_ROGUE_MIND_NUMBLING_POISON);

                    if (caster->HasAura(SPELL_ROGUE_CRIPPLING_POISON))
                        caster->RemoveAura(SPELL_ROGUE_CRIPPLING_POISON);

                    if (caster->HasAura(SPELL_ROGUE_PARALYTIC_POISON))
                        caster->RemoveAura(SPELL_ROGUE_PARALYTIC_POISON);
                    break;
                }
                case SPELL_ROGUE_PARALYTIC_POISON:
                {
                    if (caster->HasAura(SPELL_ROGUE_MIND_NUMBLING_POISON))
                        caster->RemoveAura(SPELL_ROGUE_MIND_NUMBLING_POISON);

                    if (caster->HasAura(SPELL_ROGUE_CRIPPLING_POISON))
                        caster->RemoveAura(SPELL_ROGUE_CRIPPLING_POISON);

                    if (caster->HasAura(SPELL_ROGUE_LEECHING_POISON))
                        caster->RemoveAura(SPELL_ROGUE_LEECHING_POISON);
                    break;
                }
                case SPELL_ROGUE_DEADLY_POISON:
                {
                    if (caster->HasAura(SPELL_ROGUE_WOUND_POISON))
                        caster->RemoveAura(SPELL_ROGUE_WOUND_POISON);
                    break;
                }
                default:
                    break;
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_rog_poisons_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_rog_poisons_SpellScript();
    }
};

class spell_rog_shroud_of_concealment : public SpellScriptLoader
{
public:
    spell_rog_shroud_of_concealment() : SpellScriptLoader("spell_rog_shroud_of_concealment") { }

    class spell_rog_shroud_of_concealment_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_shroud_of_concealment_SpellScript);

        void HandleOnHit()
        {
            if (!GetCaster() || !GetHitUnit())
                return;

            Player* caster = GetCaster()->ToPlayer();
            Unit* target = GetHitUnit();

            if (Aura* shroudOfConcealment = target->GetAura(SPELL_ROGUE_SHROUD_OF_CONCEALMENT_AURA, caster->GetGUID()))
                if (!target->IsInRaidWith(caster) && !target->IsInPartyWith(caster))
                    target->RemoveAura(SPELL_ROGUE_SHROUD_OF_CONCEALMENT_AURA, caster->GetGUID());
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_rog_shroud_of_concealment_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_rog_shroud_of_concealment_SpellScript();
    }
};

class spell_rog_paralytic_poison : public SpellScriptLoader
{
public:
    spell_rog_paralytic_poison() : SpellScriptLoader("spell_rog_paralytic_poison") { }

    class spell_rog_paralytic_poison_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_paralytic_poison_SpellScript);

        void HandleOnHit()
        {
            if (!GetCaster() || !GetHitUnit())
                return;

            Player* caster = GetCaster()->ToPlayer();
            Unit* target = GetHitUnit();

            if (Aura* paralyticPoison = target->GetAura(SPELL_ROGUE_PARALYTIC_POISON_DEBUFF))
            {
                if (paralyticPoison->GetStackAmount() == 5 && !target->HasAura(SPELL_ROGUE_TOTAL_PARALYSIS))
                {
                    caster->CastSpell(target, SPELL_ROGUE_TOTAL_PARALYSIS, true);
                    target->RemoveAura(SPELL_ROGUE_PARALYTIC_POISON_DEBUFF);
                }
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_rog_paralytic_poison_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_rog_paralytic_poison_SpellScript();
    }
};

class spell_rog_evescerate : public SpellScriptLoader
{
public:
    spell_rog_evescerate() : SpellScriptLoader("spell_rog_evescerate") { }

    class spell_rog_evescerate_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_rog_evescerate_SpellScript);

        void CalculateDamage()
        {
            Unit* caster = GetCaster();
            int32 damage = GetHitDamage();
            int32 comboPoints = GetCaster()->ToPlayer()->GetComboPoints();

            if (comboPoints)
            {
                float ap = caster->GetTotalAttackPowerValue(BASE_ATTACK);
                damage += int32(ap * comboPoints * 0.16f);

                if (caster->HasAura(SPELL_ROGUE_EVESCERATE_AND_ENVENOM_BONUS_DMG))
                    damage += comboPoints * 40;
            }
            
            if (caster->HasAura(SPELL_ROGUE_MASTERY_EXECUTIONER))
            {
                float Mastery = caster->ToPlayer()->GetMasterySpellCoefficient();
                AddPct(damage, Mastery);
            }

            SetHitDamage(damage);
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_rog_evescerate_SpellScript::CalculateDamage);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_rog_evescerate_SpellScript();
    }
};

void AddSC_rogue_spell_scripts()
{
    new spell_rog_smoke_bomb();
    new spell_rog_nightstalker();
    new spell_rog_hemorrhage();
    new spell_rog_crimson_tempest();
    new spell_rog_shiv();
    new spell_rog_poisons();
    new spell_rog_shroud_of_concealment();
    new spell_rog_paralytic_poison();
    new spell_rog_evescerate();
}
