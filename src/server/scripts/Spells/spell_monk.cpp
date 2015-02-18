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
    SPELL_MONK_CRACKLING_JADE_LIGHTNING_CHANNEL     = 117952,
    SPELL_MONK_CRACKLING_JADE_LIGHTNING_HIDDEN_CD   = 117953,
    SPELL_MONK_CRACKLING_JADE_LIGHTNING_AURA        = 117959,
    SPELL_MONK_CRACKLING_JADE_LIGHTNING_KNOCKBACK   = 117962,
    SPELL_MONK_CRACKLING_JADE_LIGHTNING_CHI_PROC    = 123332,
    SPELL_MONK_FORTIFYING_BREW_AURA                 = 120954,
    SPELL_MONK_GLYPH_OF_FORTIFYING_BREW             = 124997,
    SPELL_MONK_BREATH_OF_FIRE_PERIODIC              = 123725,
    SPELL_MONK_BREATH_OF_FIRE_CONFUSE               = 123393,
    SPELL_MONK_GLYPH_OF_BREATH_OF_FIRE              = 123394,
    SPELL_MONK_DIZZYING_HAZE                        = 115180,
    SPELL_MONK_LEGACY_OF_THE_EMPEROR_RAID           = 117666,
    SPELL_MONK_LEGACY_OF_THE_EMPEROR_ALLY           = 117667,
    SPELL_MONK_EXPEL_HARM_AREA_DMG                  = 115129,
    SPELL_MONK_TOUCH_OF_DEATH_PLAYER                = 124490,
    SPELL_MONK_ROLL                                 = 109132,
    SPELL_MONK_ROLL_TRIGGER                         = 107427,
    SPELL_MONK_ITEM_PVP_GLOVES_BONUS                = 124489,
    SPELL_MONK_DISABLE                              = 116095,
    SPELL_MONK_DISABLE_ROOT                         = 116706,
    SPELL_MONK_PARALYSIS                            = 115078,
    SPELL_MONK_SPINNING_CRANE_KICK                  = 107270,
    SPELL_MONK_SPINNING_CRANE_KICK_ENERGIZE         = 129881,
    SPELL_MONK_BREWING_TIGEREYE_BREW                = 123980,
    SPELL_MONK_TIGEREYE_BREW                        = 116740,
    SPELL_MONK_TIGEREYE_BREW_BUFF                   = 125195,
    SPELL_MONK_TIGER_STRIKES                        = 120273,
    SPELL_MONK_ZEN_PILGRIMAGE                       = 126892,
    SPELL_MONK_ZEN_PILGRIMAGE_RETURN                = 126895
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

        void OnApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (GetCaster())
            {
                GetCaster()->CastSpell(GetCaster(), SPELL_MONK_CRACKLING_JADE_LIGHTNING_AURA, true);
                GetCaster()->CastSpell(GetCaster(), SPELL_MONK_CRACKLING_JADE_LIGHTNING_AURA, true, NULL, aurEff);
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
            OnEffectApply += AuraEffectApplyFn(spell_monk_crackling_jade_lightning_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_monk_crackling_jade_lightning_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
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
            if (GetTarget()->HasAura(SPELL_MONK_CRACKLING_JADE_LIGHTNING_HIDDEN_CD))
                return false;

            // Just prevention against buggers
            Spell* currentChanneledSpell = GetTarget()->GetCurrentSpell(CURRENT_CHANNELED_SPELL);
            if (!currentChanneledSpell || currentChanneledSpell->GetSpellInfo()->Id != SPELL_MONK_CRACKLING_JADE_LIGHTNING_CHANNEL)
                return false;

            return true;
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

class spell_monk_fortifying_brew : public SpellScriptLoader
{
public:
    spell_monk_fortifying_brew() : SpellScriptLoader("spell_monk_fortifying_brew") { }

    class spell_monk_fortifying_brew_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_fortifying_brew_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MONK_FORTIFYING_BREW_AURA) || !sSpellMgr->GetSpellInfo(SPELL_MONK_GLYPH_OF_FORTIFYING_BREW))
                return false;
            return true;
        }

        void HandleOnHit(SpellEffIndex /*effIndex*/)
        {
            if (Unit* target = GetHitUnit())
            {
                int32 bp0 = GetEffectValue();
                int32 bp1 = -bp0;

                if (Aura* aura = target->GetAura(SPELL_MONK_GLYPH_OF_FORTIFYING_BREW))
                {
                    bp0 -= aura->GetEffect(EFFECT_1)->GetAmount();
                    bp1 -= aura->GetEffect(EFFECT_0)->GetAmount();
                }

                bp0 = CalculatePct(target->GetMaxHealth(), bp0);
                target->CastCustomSpell(target, SPELL_MONK_FORTIFYING_BREW_AURA, &bp0, &bp1, NULL, true);
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_monk_fortifying_brew_SpellScript::HandleOnHit, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_fortifying_brew_SpellScript();
    }
};

class spell_monk_breath_of_fire : public SpellScriptLoader
{
public:
    spell_monk_breath_of_fire() : SpellScriptLoader("spell_monk_breath_of_fire") { }

    class spell_monk_breath_of_fire_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_breath_of_fire_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MONK_BREATH_OF_FIRE_PERIODIC) || !sSpellMgr->GetSpellInfo(SPELL_MONK_DIZZYING_HAZE))
                return false;
            return true;
        }

        void HandleOnHit(SpellEffIndex /*effIndex*/)
        {
            if (!GetHitUnit())
                return;

            if (GetHitUnit()->HasAura(SPELL_MONK_DIZZYING_HAZE))
            {
                GetCaster()->CastSpell(GetHitUnit(), SPELL_MONK_BREATH_OF_FIRE_PERIODIC, true);
                if (GetCaster()->HasAura(SPELL_MONK_GLYPH_OF_BREATH_OF_FIRE))
                    GetCaster()->CastSpell(GetHitUnit(), SPELL_MONK_BREATH_OF_FIRE_CONFUSE, true);
            }
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_monk_breath_of_fire_SpellScript::HandleOnHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_breath_of_fire_SpellScript();
    }
};

class spell_monk_legacy_of_the_emperor : public SpellScriptLoader
{
public:
    spell_monk_legacy_of_the_emperor() : SpellScriptLoader("spell_monk_legacy_of_the_emperor") { }

    class spell_monk_legacy_of_the_emperor_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_legacy_of_the_emperor_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MONK_LEGACY_OF_THE_EMPEROR_RAID))
                return false;
            return true;
        }

        void HandleDummy(SpellEffIndex /*effIndex*/)
        {
            if (!GetHitUnit())
                return;

            if (GetCaster()->IsInRaidWith(GetHitUnit()))
                GetCaster()->CastSpell(GetCaster(), SPELL_MONK_LEGACY_OF_THE_EMPEROR_RAID, true);
            else
                GetCaster()->CastSpell(GetHitUnit(), SPELL_MONK_LEGACY_OF_THE_EMPEROR_ALLY, true);
        }

        void Register() override
        {
            OnEffectHitTarget += SpellEffectFn(spell_monk_legacy_of_the_emperor_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_legacy_of_the_emperor_SpellScript();
    }
};

class spell_monk_expel_harm : public SpellScriptLoader
{
public:
    spell_monk_expel_harm() : SpellScriptLoader("spell_monk_expel_harm") { }

    class spell_monk_expel_harm_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_expel_harm_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/) override
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MONK_EXPEL_HARM_AREA_DMG))
                return false;
            return true;
        }

        void DealAreaDamage()
        {
            if (!GetHitUnit())
                return;

            int32 dmg = GetHitHeal() / 2;
            if (dmg > 0)
                GetHitUnit()->CastCustomSpell(SPELL_MONK_EXPEL_HARM_AREA_DMG, SPELLVALUE_BASE_POINT0, dmg, GetHitUnit(), true);
        }

        void Register() override
        {
            AfterHit += SpellHitFn(spell_monk_expel_harm_SpellScript::DealAreaDamage);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_expel_harm_SpellScript();
    }
};

class spell_monk_touch_of_death : public SpellScriptLoader
{
public:
    spell_monk_touch_of_death() : SpellScriptLoader("spell_monk_touch_of_death") { }

    class spell_monk_touch_of_death_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_touch_of_death_SpellScript);

        SpellCastResult CheckRequirement()
        {
            if (Unit* caster = GetCaster())
            {
                if (Unit* target = GetExplTargetUnit())
                {
                    if (target->ToPlayer())
                    {
                        if (caster->HasAura(SPELL_MONK_TOUCH_OF_DEATH_PLAYER))
                        {
                            if (target->HealthAbovePct(GetSpellInfo()->Effects[EFFECT_1].BasePoints))
                                return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
                        }
                        else
                            return SPELL_FAILED_TARGET_IS_PLAYER;
                    }
                    else
                    {
                        if (target->GetHealth() > caster->GetHealth())
                            return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;
                    }
                }
            }
            return SPELL_CAST_OK;
        }

        void Register() override
        {
            OnCheckCast += SpellCheckCastFn(spell_monk_touch_of_death_SpellScript::CheckRequirement);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_monk_touch_of_death_SpellScript();
    }
};

// Roll - 109132 or Roll (3 charges) - 121827
class spell_monk_roll : public SpellScriptLoader
{
    public:
        spell_monk_roll() : SpellScriptLoader("spell_monk_roll") { }

        class spell_monk_roll_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_roll_SpellScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MONK_ROLL))
                    return false;
                return true;
            }

            void HandleBeforeCast()
            {
                Aura* aur = GetCaster()->AddAura(SPELL_MONK_ROLL_TRIGGER, GetCaster());
                if (!aur)
                    return;

                AuraApplication* app =  aur->GetApplicationOfTarget(GetCaster()->GetGUID());
                if (!app)
                    return;

                app->ClientUpdate();
            }

            void HandleAfterCast()
            {
                Unit* caster = GetCaster();
                if (!caster || caster->GetTypeId() != TYPEID_PLAYER)
                    return;

                caster->CastSpell(caster, SPELL_MONK_ROLL_TRIGGER, true);

                if (caster->HasAura(SPELL_MONK_ITEM_PVP_GLOVES_BONUS))
                    caster->RemoveAurasByType(SPELL_AURA_MOD_DECREASE_SPEED);
            }

            void Register()
            {
                BeforeCast += SpellCastFn(spell_monk_roll_SpellScript::HandleBeforeCast);
                AfterCast += SpellCastFn(spell_monk_roll_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_roll_SpellScript();
        }
};

// Disable - 116095
class spell_monk_disable : public SpellScriptLoader
{
    public:
        spell_monk_disable() : SpellScriptLoader("spell_monk_disable") { }

    class spell_monk_disable_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_disable_AuraScript);

        bool Validate(SpellInfo const* /*spell*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MONK_DISABLE))
                return false;
            return true;
        }

        void OnPeriodic(AuraEffect const* aurEff)
        {
            if (aurEff->GetTickNumber() % aurEff->GetTotalTicks() != 0) // last tick of duration
                return;

            if (Unit* caster = GetCaster())
                if (Unit* owner = GetUnitOwner())
                    if ((owner->GetDistance2d(caster) < 10.0f) && caster->IsAlive())
                        aurEff->GetBase()->RefreshDuration();         
        }

        void AfterReapply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
                if (Unit* target = GetTarget())
                    caster->CastSpell(target, SPELL_MONK_DISABLE_ROOT, true);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_monk_disable_AuraScript::OnPeriodic, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
            AfterEffectApply += AuraEffectRemoveFn(spell_monk_disable_AuraScript::AfterReapply, EFFECT_0, SPELL_AURA_MOD_DECREASE_SPEED, AURA_EFFECT_HANDLE_REAPPLY);
        }
    };


    AuraScript* GetAuraScript() const
    {
        return new spell_monk_disable_AuraScript();
    }
};

// Paralysis - 115078
class spell_monk_paralysis : public SpellScriptLoader
{
    public:
        spell_monk_paralysis() : SpellScriptLoader("spell_monk_paralysis") { }

        class spell_monk_paralysis_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_monk_paralysis_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MONK_PARALYSIS))
                    return false;
                return true;
            }

            void HandleOnEffectApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetTarget())
                    {
                        if (target->isInBackInMap(caster, 20.0f, M_PI/2))
                        {
                            uint16 duration = aurEff->GetBase()->GetMaxDuration();
                            AddPct(duration, 50);
                            aurEff->GetBase()->SetDuration(duration);
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_monk_paralysis_AuraScript::HandleOnEffectApply, EFFECT_0, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
            }
        };


        AuraScript* GetAuraScript() const
        {
            return new spell_monk_paralysis_AuraScript();
        }
};

// Spinning Crane Kick - 107270
class spell_monk_spinning_crane_kick : public SpellScriptLoader
{
    public:
        spell_monk_spinning_crane_kick() : SpellScriptLoader("spell_monk_spinning_crane_kick") { }

        class spell_monk_spinning_crane_kick_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_spinning_crane_kick_SpellScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MONK_SPINNING_CRANE_KICK))
                    return false;
                return true;
            }

            void HandleOnCast()
            {
                if (Unit* caster = GetCaster())
                {
                    std::list<Unit*> targets;
                    Trinity::AnyUnfriendlyUnitInObjectRangeCheck u_check(caster, caster, 8.0f);
                    Trinity::UnitListSearcher<Trinity::AnyUnfriendlyUnitInObjectRangeCheck> searcher(caster, targets, u_check);
                    caster->VisitNearbyObject(8.0f, searcher);
                    if (targets.size() >= 3)
                        caster->CastSpell(caster, SPELL_MONK_SPINNING_CRANE_KICK_ENERGIZE, true);
                }
            }

            void Register()
            {
                OnCast += SpellCastFn(spell_monk_spinning_crane_kick_SpellScript::HandleOnCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_spinning_crane_kick_SpellScript();
        }
};

// Brewing: Tigereye Brew - 123980
class spell_monk_brewing_tigereye_brew : public SpellScriptLoader
{
    public:
        spell_monk_brewing_tigereye_brew() : SpellScriptLoader("spell_monk_brewing_tigereye_brew") { }

        class spell_monk_brewing_tigereye_brew_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_monk_brewing_tigereye_brew_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MONK_BREWING_TIGEREYE_BREW))
                    return false;
                return true;
            }

            uint32 chiConsumed;

            void HandleOnEffectApply(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                chiConsumed = 0;
            }

            void SetData(uint32 type, uint32 data)
            {
                if (Unit* caster = GetCaster())
                {
                    chiConsumed += data;
                    if (chiConsumed >= 4)
                    {
                        caster->CastSpell(caster, SPELL_MONK_TIGEREYE_BREW_BUFF, true);
                        chiConsumed -= 4;
                    }
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_monk_brewing_tigereye_brew_AuraScript::HandleOnEffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };


        AuraScript* GetAuraScript() const
        {
            return new spell_monk_brewing_tigereye_brew_AuraScript();
        }
};

#define maxStack 10

// Tigereye Brew - 116740
class spell_monk_tigereye_brew : public SpellScriptLoader
{
public:
    spell_monk_tigereye_brew() : SpellScriptLoader("spell_monk_tigereye_brew") { }

    class spell_monk_tigereye_brew_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_tigereye_brew_AuraScript);

        bool Validate(SpellInfo const* /*spell*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_MONK_TIGEREYE_BREW))
                return false;
            return true;
        }

        void CalculateAmount(AuraEffect const* aurEff, int32& amount, bool& /*canBeRecalculated*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (Aura* aur = caster->GetAura(SPELL_MONK_TIGEREYE_BREW_BUFF))
                {
                    uint16 stack = aur->GetStackAmount();

                    // Max bonus = 60%
                    if (stack > maxStack)
                        amount *= maxStack;
                    else
                        amount *= stack;
                }
            }
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_tigereye_brew_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE);
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_tigereye_brew_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_MOD_HEALING_DONE_PERCENT);
        }
    };


    AuraScript* GetAuraScript() const
    {
        return new spell_monk_tigereye_brew_AuraScript();
    }

    class spell_monk_tigereye_brew_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_tigereye_brew_SpellScript);

        void HandleAfterCast()
        {
            if (Unit* caster = GetCaster())
            {
                if (Aura* aur = caster->GetAura(SPELL_MONK_TIGEREYE_BREW_BUFF))
                {
                    uint16 stack = aur->GetStackAmount();
                    // Removes at most 10 stacks
                    if (stack > maxStack)
                    {
                        // One of the stacks is already removed automatically
                        aur->SetStackAmount(stack - maxStack + 1);
                    }
                    else
                        caster->RemoveAura(SPELL_MONK_TIGEREYE_BREW_BUFF);
                }
            }
        }

        void Register()
        {
            AfterCast += SpellCastFn(spell_monk_tigereye_brew_SpellScript::HandleAfterCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_monk_tigereye_brew_SpellScript();
    }
};

// Tiger Strikes - 120273
class spell_monk_tiger_strikes : public SpellScriptLoader
{
    public:
        spell_monk_tiger_strikes() : SpellScriptLoader("spell_monk_tiger_strikes") { }

        class spell_monk_tiger_strikes_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_monk_tiger_strikes_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MONK_TIGER_STRIKES))
                    return false;
                return true;
            }

            void HandleProc(AuraEffect const* /*aurEff*/, ProcEventInfo& eventInfo)
            {
                if (Unit* caster = GetCaster())
                    if (Unit* target = eventInfo.GetDamageInfo()->GetVictim())
                        caster->CastSpell(target, 120274, true);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_monk_tiger_strikes_AuraScript::HandleProc, EFFECT_0, SPELL_AURA_MOD_MELEE_HASTE_3);
            }
        };


        AuraScript* GetAuraScript() const
        {
            return new spell_monk_tiger_strikes_AuraScript();
        }
};

// Zen Pilgrimage - 126892
class spell_monk_zen_pilgrimage : public SpellScriptLoader
{
    public:
        spell_monk_zen_pilgrimage() : SpellScriptLoader("spell_monk_zen_pilgrimage") { }

        class spell_monk_zen_pilgrimage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_zen_pilgrimage_SpellScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MONK_ZEN_PILGRIMAGE))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                    if (Player* player = caster->ToPlayer())
                        player->SaveRecallPosition();      
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_monk_zen_pilgrimage_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_TELEPORT_UNITS);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_zen_pilgrimage_SpellScript();
        }
};

// Zen Pilgrimage: Return - 126895
class spell_monk_zen_pilgrimage_return : public SpellScriptLoader
{
    public:
        spell_monk_zen_pilgrimage_return() : SpellScriptLoader("spell_monk_zen_pilgrimage_return") { }

        class spell_monk_zen_pilgrimage_return_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_zen_pilgrimage_return_SpellScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MONK_ZEN_PILGRIMAGE_RETURN))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                    if (Player* player = caster->ToPlayer())
                        player->TeleportTo(player->m_recallMap, player->m_recallX, player->m_recallY, player->m_recallZ, player->m_recallO);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_monk_zen_pilgrimage_return_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_zen_pilgrimage_return_SpellScript();
        }
};

void AddSC_monk_spell_scripts()
{
    new spell_monk_crackling_jade_lightning();
    new spell_monk_crackling_jade_lightning_aura();
    new spell_monk_fortifying_brew();
    new spell_monk_breath_of_fire();
    new spell_monk_legacy_of_the_emperor();
    new spell_monk_expel_harm();
    new spell_monk_touch_of_death();
    new spell_monk_roll();
    new spell_monk_disable();
    new spell_monk_paralysis();
    new spell_monk_spinning_crane_kick();
    new spell_monk_brewing_tigereye_brew();
    new spell_monk_tigereye_brew();
    new spell_monk_tiger_strikes();
    new spell_monk_zen_pilgrimage();
    new spell_monk_zen_pilgrimage_return();
}
