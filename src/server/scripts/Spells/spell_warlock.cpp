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
 * Scripts for spells with SPELLFAMILY_WARLOCK and SPELLFAMILY_GENERIC spells used by warlock players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_warl_".
 */

#include "Player.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "SpellAuras.h"

enum WarlockSpells
{
    SPELL_WARLOCK_IMMOLATE                        = 348,
    SPELL_WARLOCK_IMMOLATE_FIRE_AND_BRIMSTONE     = 108686,
    SPELL_WARLOCK_SHADOWBURN_ENERGIZE             = 125882,
    SPELL_WARLOCK_UNSTABLE_AFFLICTION             = 30108,
    SPELL_WARLOCK_CORRUPTION                      = 172,
    SPELL_WARLOCK_DOOM                            = 603,
    SPELL_WARLOCK_NIGHTFALL                       = 108558,
    SPELL_WARLOCK_GLYPH_OF_SIPHON_LIFE            = 56218,
    SPELL_WARLOCK_SOULBURN_AURA                   = 74434,
    SPELL_WARLOCK_DRAIN_LIFE_HEAL                 = 89653,
    SPELL_WARLOCK_MOLTEN_CORE                     = 122355,
    SPELL_WARLOCK_MOLTEN_CORE_AURA                = 122351,
    SPELL_WARLOCK_DECIMATE_AURA                   = 108869,
    SPELL_WARLOCK_METAMORPHOSIS                   = 103958,
    SPELL_WARLOCK_HARVEST_LIFE_HEAL               = 125314,
    SPELL_WARLOCK_DRAIN_LIFE                      = 689,
    SPELL_WARLOCK_SHADOW_BOLT                     = 686,
};

class spell_warl_rain_of_fire_damage : public SpellScriptLoader
{
public:
    spell_warl_rain_of_fire_damage() : SpellScriptLoader("spell_warl_rain_of_fire_damage") { }

    class spell_warl_rain_of_fire_damage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_rain_of_fire_damage_SpellScript);

        void HandleOnHit()
        {
            if (Player* player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {
                    if (player->GetSpecializationId(player->GetActiveSpec()) == CHAR_SPECIALIZATION_WARLOCK_DESTRUCTION)
                    {
                        if (target->HasAura(SPELL_WARLOCK_IMMOLATE) || target->HasAura(SPELL_WARLOCK_IMMOLATE_FIRE_AND_BRIMSTONE))
                        {
                            int32 damage = GetHitDamage();
                            AddPct(damage, 50);
                            SetHitDamage(damage);

                            if (roll_chance_i(25))
                                player->EnergizeBySpell(player, GetSpellInfo()->Id, 1, POWER_BURNING_EMBERS);
                        }
                    }
                }
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_warl_rain_of_fire_damage_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warl_rain_of_fire_damage_SpellScript();
    }
};

class spell_warl_shadowburn : public SpellScriptLoader
{
public:
    spell_warl_shadowburn() : SpellScriptLoader("spell_warl_shadowburn") { }

    class spell_warl_shadowburn_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_shadowburn_AuraScript);

        void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
        {
            if (GetCaster())
            {
                AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
                if (removeMode == AURA_REMOVE_BY_DEATH)
                    GetCaster()->SetPower(POWER_BURNING_EMBERS, GetCaster()->GetPower(POWER_BURNING_EMBERS) + 20);
                else if (removeMode == AURA_REMOVE_BY_EXPIRE)
                    GetCaster()->CastSpell(GetCaster(), SPELL_WARLOCK_SHADOWBURN_ENERGIZE, true);
            }
        }

        void Register()
        {
            OnEffectRemove += AuraEffectApplyFn(spell_warl_shadowburn_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warl_shadowburn_AuraScript();
    }
};

class spell_warl_burning_embers : public SpellScriptLoader
{
public:
    spell_warl_burning_embers() : SpellScriptLoader("spell_warl_burning_embers") { }

    class spell_warl_burning_embers_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_burning_embers_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {
                    if (GetSpell()->IsCritForTarget(target))
                        _player->SetPower(POWER_BURNING_EMBERS, _player->GetPower(POWER_BURNING_EMBERS) + 2);
                    else
                        _player->SetPower(POWER_BURNING_EMBERS, _player->GetPower(POWER_BURNING_EMBERS) + 1);
                }
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_warl_burning_embers_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warl_burning_embers_SpellScript();
    }
};

class spell_warl_fel_flame : public SpellScriptLoader
{
public:
    spell_warl_fel_flame() : SpellScriptLoader("spell_warl_fel_flame") { }

    class spell_warl_fel_flame_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_fel_flame_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {
                    _player->EnergizeBySpell(_player, GetSpellInfo()->Id, 15, POWER_DEMONIC_FURY);

                    if (_player->GetSpecializationId(_player->GetActiveSpec()) == CHAR_SPECIALIZATION_WARLOCK_AFFLICTION)
                    {
                        if (Aura* unstableAffliction = target->GetAura(SPELL_WARLOCK_UNSTABLE_AFFLICTION, _player->GetGUID()))
                        {
                            unstableAffliction->SetDuration(unstableAffliction->GetDuration() + 6000);
                            unstableAffliction->SetNeedClientUpdateForTargets();
                        }
                        if (Aura* corruption = target->GetAura(SPELL_WARLOCK_CORRUPTION, _player->GetGUID()))
                        {
                            corruption->SetDuration(corruption->GetDuration() + 6000);
                            corruption->SetNeedClientUpdateForTargets();
                        }
                    }
                    else if (_player->GetSpecializationId(_player->GetActiveSpec()) == CHAR_SPECIALIZATION_WARLOCK_DEMONOLOGY)
                    {
                        if (Aura* corruption = target->GetAura(SPELL_WARLOCK_CORRUPTION, _player->GetGUID()))
                        {
                            corruption->SetDuration(corruption->GetDuration() + 6000);
                            corruption->SetNeedClientUpdateForTargets();
                        }
                        else if (Aura* doom = target->GetAura(SPELL_WARLOCK_DOOM, _player->GetGUID()))
                        {
                            doom->SetDuration(doom->GetDuration() + 6000);
                            doom->SetNeedClientUpdateForTargets();
                        }
                    }
                    else if (_player->GetSpecializationId(_player->GetActiveSpec()) == CHAR_SPECIALIZATION_WARLOCK_DESTRUCTION)
                    {
                        if (Aura* corruption = target->GetAura(SPELL_WARLOCK_IMMOLATE, _player->GetGUID()))
                        {
                            corruption->SetDuration(corruption->GetDuration() + 6000);
                            corruption->SetNeedClientUpdateForTargets();
                        }

                        if (GetSpell()->IsCritForTarget(target))
                            _player->SetPower(POWER_BURNING_EMBERS, _player->GetPower(POWER_BURNING_EMBERS) + 2);
                        else
                            _player->SetPower(POWER_BURNING_EMBERS, _player->GetPower(POWER_BURNING_EMBERS) + 1);
                    }
                    else
                    {
                        if (Aura* corruption = target->GetAura(SPELL_WARLOCK_CORRUPTION, _player->GetGUID()))
                        {
                            corruption->SetDuration(corruption->GetDuration() + 6000);
                            corruption->SetNeedClientUpdateForTargets();
                        }
                    }
                }
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_warl_fel_flame_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warl_fel_flame_SpellScript();
    }
};

class spell_warl_nightfall : public SpellScriptLoader
{
public:
    spell_warl_nightfall() : SpellScriptLoader("spell_warl_nightfall") { }

    class spell_warl_nightfall_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_nightfall_AuraScript);

        void OnTick(AuraEffect const* /*aurEff*/ aurEff)
        {
            if (!GetCaster())
                return;

            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (_player->HasAura(SPELL_WARLOCK_NIGHTFALL))
                    if (roll_chance_i(5))
                        _player->SetPower(POWER_SOUL_SHARDS, _player->GetPower(POWER_SOUL_SHARDS) + 100);

                if (_player->HasAura(SPELL_WARLOCK_GLYPH_OF_SIPHON_LIFE))
                    _player->HealBySpell(_player, sSpellMgr->GetSpellInfo(SPELL_WARLOCK_GLYPH_OF_SIPHON_LIFE), int32(_player->GetMaxHealth() / 200), false);
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_nightfall_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warl_nightfall_AuraScript();
    }
};

class spell_warl_drain_soul : public SpellScriptLoader
{
public:
    spell_warl_drain_soul() : SpellScriptLoader("spell_warl_drain_soul") { }

    class spell_warl_drain_soul_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_drain_soul_AuraScript);

        void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
        {
            if (GetCaster())
            {
                AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
                if (removeMode == AURA_REMOVE_BY_DEATH)
                    GetCaster()->SetPower(POWER_SOUL_SHARDS, GetCaster()->GetPower(POWER_SOUL_SHARDS) + 300);
            }
        }

        void Register()
        {
            OnEffectRemove += AuraEffectApplyFn(spell_warl_drain_soul_AuraScript::HandleRemove, EFFECT_4, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warl_drain_soul_AuraScript();
    }
};

class spell_warl_soulburn_drain_life : public SpellScriptLoader
{
public:
    spell_warl_soulburn_drain_life() : SpellScriptLoader("spell_warl_soulburn_drain_life") { }

    class spell_warl_soulburn_drain_life_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_soulburn_drain_life_AuraScript);

        void HandleApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes mode)
        {
            if (GetCaster())
                if (GetCaster()->HasAura(SPELL_WARLOCK_SOULBURN_AURA))
                    GetCaster()->RemoveAura(SPELL_WARLOCK_SOULBURN_AURA);
        }

        void OnTick(AuraEffect const* /*aurEff*/ aurEff)
        {
            if (Unit* caster = GetCaster())
            {
                Player* _player = GetCaster()->ToPlayer();
                if (!_player)
                    return;

                int32 basepoints = _player->CountPctFromMaxHealth(3);

                if (_player->GetSpecializationId(_player->GetActiveSpec()) == CHAR_SPECIALIZATION_WARLOCK_DEMONOLOGY)
                    _player->EnergizeBySpell(_player, SPELL_WARLOCK_DRAIN_LIFE, 10, POWER_DEMONIC_FURY);

                _player->CastCustomSpell(_player, SPELL_WARLOCK_DRAIN_LIFE_HEAL, &basepoints, NULL, NULL, true);
            }
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_warl_soulburn_drain_life_AuraScript::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_soulburn_drain_life_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warl_soulburn_drain_life_AuraScript();
    }
};

class spell_warl_molten_core_dot : public SpellScriptLoader
{
public:
    spell_warl_molten_core_dot() : SpellScriptLoader("spell_warl_molten_core_dot") { }

    class spell_warl_molten_core_dot_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_molten_core_dot_AuraScript);

        void OnTick(AuraEffect const* /*aurEff*/ aurEff)
        {
            if (GetCaster())
            {
                if (GetCaster()->HasAura(SPELL_WARLOCK_MOLTEN_CORE_AURA))
                    if (roll_chance_i(8))
                        GetCaster()->CastSpell(GetCaster(), SPELL_WARLOCK_MOLTEN_CORE, true);

                GetCaster()->EnergizeBySpell(GetCaster(), aurEff->GetSpellInfo()->Id, 2, POWER_DEMONIC_FURY);
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_molten_core_dot_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warl_molten_core_dot_AuraScript();
    }
};

class spell_warl_decimate : public SpellScriptLoader
{
public:
    spell_warl_decimate() : SpellScriptLoader("spell_warl_decimate") { }

    class spell_warl_decimate_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_decimate_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                    if (_player->HasAura(SPELL_WARLOCK_DECIMATE_AURA))
                        if (target->GetHealthPct() < 25.0f)
                            _player->CastSpell(_player, SPELL_WARLOCK_MOLTEN_CORE, true);

                if (_player->GetSpecializationId(_player->GetActiveSpec()) == CHAR_SPECIALIZATION_WARLOCK_DEMONOLOGY)
                    _player->EnergizeBySpell(_player, GetSpellInfo()->Id, GetSpellInfo()->Id == SPELL_WARLOCK_SHADOW_BOLT ? 25 : 30, POWER_DEMONIC_FURY);
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_warl_decimate_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warl_decimate_SpellScript();
    }
};

class spell_warl_metamorphosis_cost : public SpellScriptLoader
{
public:
    spell_warl_metamorphosis_cost() : SpellScriptLoader("spell_warl_metamorphosis_cost") { }

    class spell_warl_metamorphosis_cost_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_metamorphosis_cost_AuraScript);

        void OnTick(AuraEffect const* /*aurEff*/ aurEff)
        {
            if (GetCaster())
                GetCaster()->EnergizeBySpell(GetCaster(), SPELL_WARLOCK_METAMORPHOSIS, -6, POWER_DEMONIC_FURY);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_metamorphosis_cost_AuraScript::OnTick, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warl_metamorphosis_cost_AuraScript();
    }
};

class spell_warl_immolation_aura : public SpellScriptLoader
{
public:
    spell_warl_immolation_aura() : SpellScriptLoader("spell_warl_immolation_aura") { }

    class spell_warl_immolation_aura_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_immolation_aura_AuraScript);

        void OnTick(AuraEffect const* /*aurEff*/ aurEff)
        {
            if (GetCaster())
                GetCaster()->EnergizeBySpell(GetCaster(), GetSpellInfo()->Id, -25, POWER_DEMONIC_FURY);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_immolation_aura_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warl_immolation_aura_AuraScript();
    }
};

class spell_warl_hellfire : public SpellScriptLoader
{
public:
    spell_warl_hellfire() : SpellScriptLoader("spell_warl_hellfire") { }

    class spell_warl_hellfire_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_hellfire_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
                if (Unit* target = GetHitUnit())
                    _player->EnergizeBySpell(_player, GetSpellInfo()->Id, 4, POWER_DEMONIC_FURY);
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_warl_hellfire_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warl_hellfire_SpellScript();
    }
};

class spell_warl_drain_life : public SpellScriptLoader
{
public:
    spell_warl_drain_life() : SpellScriptLoader("spell_warl_drain_life") { }

    class spell_warl_drain_life_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_drain_life_AuraScript);

        void OnTick(AuraEffect const* /*aurEff*/ aurEff)
        {
            if (Unit* caster = GetCaster())
            {
                Player* _player = GetCaster()->ToPlayer();
                if (!_player)
                    return;

                int32 basepoints = _player->GetMaxHealth() / 50;

                if (_player->GetSpecializationId(_player->GetActiveSpec()) == CHAR_SPECIALIZATION_WARLOCK_DEMONOLOGY)
                    _player->EnergizeBySpell(_player, SPELL_WARLOCK_DRAIN_LIFE, 10, POWER_DEMONIC_FURY);

                _player->CastCustomSpell(_player, SPELL_WARLOCK_DRAIN_LIFE_HEAL, &basepoints, NULL, NULL, true);
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_drain_life_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warl_drain_life_AuraScript();
    }
};

class spell_warl_soulburn_harvest_life : public SpellScriptLoader
{
public:
    spell_warl_soulburn_harvest_life() : SpellScriptLoader("spell_warl_soulburn_harvest_life") { }

    class spell_warl_soulburn_harvest_life_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_soulburn_harvest_life_AuraScript);

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (!GetCaster())
                return;

            if (Player* player = GetCaster()->ToPlayer())
                if (player->HasAura(SPELL_WARLOCK_SOULBURN_AURA))
                    player->RemoveAurasDueToSpell(SPELL_WARLOCK_SOULBURN_AURA);
        }

        void OnTick(AuraEffect const* /*aurEff*/ aurEff)
        {
            if (!GetCaster())
                return;

            if (Player* _player = GetCaster()->ToPlayer())
            {
                int32 basepoints = int32(frand(0.03f, 0.045f) * _player->GetMaxHealth());

                AddPct(basepoints, 33);

                if (!_player->HasSpellCooldown(SPELL_WARLOCK_HARVEST_LIFE_HEAL))
                {
                    _player->CastCustomSpell(_player, SPELL_WARLOCK_HARVEST_LIFE_HEAL, &basepoints, NULL, NULL, true);
                    _player->AddSpellCooldown(SPELL_WARLOCK_HARVEST_LIFE_HEAL, 0, time(NULL) + 1);
                }

                _player->EnergizeBySpell(_player, aurEff->GetSpellInfo()->Id, 4, POWER_DEMONIC_FURY);
            }
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_warl_soulburn_harvest_life_AuraScript::OnApply, EFFECT_2, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_soulburn_harvest_life_AuraScript::OnTick, EFFECT_2, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warl_soulburn_harvest_life_AuraScript();
    }
};

class spell_warl_harvest_life : public SpellScriptLoader
{
public:
    spell_warl_harvest_life() : SpellScriptLoader("spell_warl_harvest_life") { }

    class spell_warl_harvest_life_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_harvest_life_AuraScript);

        void OnTick(AuraEffect const* /*aurEff*/ aurEff)
        {
            if (!GetCaster())
                return;

            if (Player* _player = GetCaster()->ToPlayer())
            {
                std::list<Unit*> targetList;
                aurEff->GetTargetList(targetList);
                float coeff = 0.03f;
                uint8 count = 1;
                bool first = true;

                for (auto itr : targetList)
                {
                    if (first)
                        continue;
                    else if (count <= 6)
                    {
                        coeff += 0.0025f;
                        ++count;
                    }
                }

                int32 basepoints = int32(coeff * float(_player->GetMaxHealth()));

                if (!_player->HasSpellCooldown(SPELL_WARLOCK_HARVEST_LIFE_HEAL))
                {
                    _player->CastCustomSpell(_player, SPELL_WARLOCK_HARVEST_LIFE_HEAL, &basepoints, NULL, NULL, true);
                    _player->AddSpellCooldown(SPELL_WARLOCK_HARVEST_LIFE_HEAL, 0, time(NULL) + 1);
                }
                _player->EnergizeBySpell(_player, aurEff->GetSpellInfo()->Id, 4, POWER_DEMONIC_FURY);
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_harvest_life_AuraScript::OnTick, EFFECT_2, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warl_harvest_life_AuraScript();
    }
};

void AddSC_warlock_spell_scripts()
{
    new spell_warl_rain_of_fire_damage();
    new spell_warl_shadowburn();
    new spell_warl_burning_embers();
    new spell_warl_fel_flame();
    new spell_warl_nightfall();
    new spell_warl_drain_soul();
    new spell_warl_soulburn_drain_life();
    new spell_warl_molten_core_dot();
    new spell_warl_decimate();
    new spell_warl_metamorphosis_cost();
    new spell_warl_immolation_aura();
    new spell_warl_hellfire();
    new spell_warl_drain_life();
    new spell_warl_soulburn_harvest_life();
    new spell_warl_harvest_life();
}
