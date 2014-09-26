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
    SPELL_HOLY_SHOCK                                = 20473,
    SPELL_HOLY_SHOCK_DMG                            = 25912,
    SPELL_HOLY_SHOCK_HEAL                           = 25914,
    SPELL_HOLY_SHOCK_ADD_HOLY_POWER                 = 148976,
    MASTERY_SPELL_HAND_OF_LIGHT                     = 96172,
    SPELL_PALADIN_MASTERY_HAND_OF_LIGHT             = 76672,
    SPELL_PALADIN_INQUISITION                       = 84963,
    SPELL_PALADIN_DIVINE_PURPOSE                    = 90174,
    SPELL_PALADIN_HOLY_PRISM_DAMAGE_VISUAL          = 114862,
    SPELL_PALADIN_HOLY_PRISM_DAMAGE_VISUAL_2        = 114870,
    SPELL_PALADIN_HOLY_PRISM_HEAL_VISUAL            = 121551,
    SPELL_PALADIN_HOLY_PRISM_HEAL_VISUAL_2          = 121552,
    SPELL_PALADIN_HOLY_PRISM_ALLIES                 = 114871,
    SPELL_PALADIN_HOLY_PRISM_ENNEMIES               = 114852,
    SPELL_PALADIN_WORD_OF_GLORY                     = 85673,
    SPELL_PALADIN_WORD_OF_GLORY_HEAL                = 130551,
    SPELL_PALADIN_GLYPH_OF_WORD_OF_GLORY            = 54936,
    SPELL_PALADIN_GLYPH_OF_WORD_OF_GLORY_DAMAGE     = 115522,
    SPELL_PALADIN_JUDGMENT                          = 20271,
    SPELL_PALADIN_JUDGMENTS_OF_THE_BOLD             = 111529,
    SPELL_PALADIN_JUDGMENTS_OF_THE_WISE             = 105424,
    SPELL_PALADIN_HOLY_AVENGER                      = 105809,
    SPELL_PALADIN_PHYSICAL_VULNERABILITY            = 81326,
    SPELL_PALADIN_LONG_ARM_OF_THE_LAW               = 87172,
    SPELL_PALADIN_LONG_ARM_OF_THE_LAW_RUN_SPEED     = 87173,
    SPELL_PALADIN_BURDEN_OF_GUILT                   = 110301,
    SPELL_PALADIN_BURDEN_OF_GUILT_DECREASE_SPEED    = 110300,
    SPELL_PALADIN_EXORCISM                          = 879,
    SPELL_PALADIN_MASS_EXORCISM                     = 122032,
    SPELL_PALADIN_SACRED_SHIELD                     = 65148,
    SPELL_PALADIN_DIVINE_SHIELD                     = 642,
    SPELL_PALADIN_LAY_ON_HANDS                      = 633,
    SPELL_PALADIN_DIVINE_PROTECTION                 = 498,

    PALADIN_ITEM_PVP_HOLY_4P_BONUS               = 131665,
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

class spell_mastery_hand_of_light : public SpellScriptLoader
{
public:
    spell_mastery_hand_of_light() : SpellScriptLoader("spell_mastery_hand_of_light") { }

    class spell_mastery_hand_of_light_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mastery_hand_of_light_SpellScript);

        void HandleAfterHit()
        {
            if (Unit* caster = GetCaster())
            {
                if (Unit* target = GetHitUnit())
                {
                    if (caster->GetTypeId() == TYPEID_PLAYER && caster->HasAura(SPELL_PALADIN_MASTERY_HAND_OF_LIGHT) && caster->getLevel() >= 80)
                    {
                        uint32 procSpellId = GetSpellInfo()->Id ? GetSpellInfo()->Id : 0;

                        if (procSpellId != MASTERY_SPELL_HAND_OF_LIGHT)
                        {
                            float Mastery = caster->ToPlayer()->GetMasterySpellCoefficient();
                            int32 bp = int32(GetHitDamage() * Mastery / 100);

                            caster->CastCustomSpell(target, MASTERY_SPELL_HAND_OF_LIGHT, &bp, NULL, NULL, true);
                        }
                    }
                }
            }
        }

        void Register()
        {
            AfterHit += SpellHitFn(spell_mastery_hand_of_light_SpellScript::HandleAfterHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_mastery_hand_of_light_SpellScript();
    }
};

class spell_pal_inquisition : public SpellScriptLoader
{
public:
    spell_pal_inquisition() : SpellScriptLoader("spell_pal_inquisition") { }

    class spell_pal_inquisition_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_inquisition_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (Aura* inquisition = _player->GetAura(SPELL_PALADIN_INQUISITION))
                {
                    int32 holyPower = _player->GetPower(POWER_HOLY_POWER);

                    if (holyPower > 2)
                        holyPower = 2;

                    if (_player->HasAura(SPELL_PALADIN_DIVINE_PURPOSE))
                        holyPower = 2;

                    int32 maxDuration = inquisition->GetMaxDuration();
                    int32 newDuration = inquisition->GetDuration() + maxDuration * holyPower;
                    inquisition->SetDuration(newDuration);

                    if (newDuration > maxDuration)
                        inquisition->SetMaxDuration(newDuration);

                    if (!_player->HasAura(SPELL_PALADIN_DIVINE_PURPOSE))
                        _player->SetPower(POWER_HOLY_POWER, _player->GetPower(POWER_HOLY_POWER) - holyPower);
                }
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_pal_inquisition_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_inquisition_SpellScript();
    }
};

class spell_pal_holy_prism : public SpellScriptLoader
{
public:
    spell_pal_holy_prism() : SpellScriptLoader("spell_pal_holy_prism") { }

    class spell_pal_holy_prism_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_holy_prism_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {
                    if (_player->IsValidAttackTarget(target))
                    {
                        _player->CastSpell(target, SPELL_PALADIN_HOLY_PRISM_DAMAGE_VISUAL, true);
                        _player->CastSpell(target, SPELL_PALADIN_HOLY_PRISM_DAMAGE_VISUAL_2, true);
                    }
                    else
                    {
                        _player->CastSpell(target, SPELL_PALADIN_HOLY_PRISM_HEAL_VISUAL, true);
                        _player->CastSpell(target, SPELL_PALADIN_HOLY_PRISM_HEAL_VISUAL_2, true);
                    }
                }
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_pal_holy_prism_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_holy_prism_SpellScript();
    }
};

class spell_pal_holy_prism_visual : public SpellScriptLoader
{
public:
    spell_pal_holy_prism_visual() : SpellScriptLoader("spell_pal_holy_prism_visual") { }

    class spell_pal_holy_prism_visual_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_holy_prism_visual_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {
                    if (_player->IsValidAttackTarget(target))
                    {
                        _player->CastSpell(target, SPELL_PALADIN_HOLY_PRISM_DAMAGE_VISUAL_2, true);
                        _player->CastSpell(target, SPELL_PALADIN_HOLY_PRISM_DAMAGE_VISUAL_2, true);
                    }
                    else
                    {
                        _player->CastSpell(target, SPELL_PALADIN_HOLY_PRISM_HEAL_VISUAL_2, true);
                        _player->CastSpell(target, SPELL_PALADIN_HOLY_PRISM_HEAL_VISUAL_2, true);
                    }
                }
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_pal_holy_prism_visual_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_holy_prism_visual_SpellScript();
    }
};

class spell_pal_holy_prism_effect : public SpellScriptLoader
{
public:
    spell_pal_holy_prism_effect() : SpellScriptLoader("spell_pal_holy_prism_effect") { }

    class spell_pal_holy_prism_effect_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_holy_prism_effect_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (Unit* target = GetHitUnit())
                {
                    if (GetSpellInfo()->Id == SPELL_PALADIN_HOLY_PRISM_DAMAGE_VISUAL)
                        _player->CastSpell(target, SPELL_PALADIN_HOLY_PRISM_ENNEMIES, true);

                    else if (GetSpellInfo()->Id == SPELL_PALADIN_HOLY_PRISM_HEAL_VISUAL)
                        _player->CastSpell(target, SPELL_PALADIN_HOLY_PRISM_ALLIES, true);
                }
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_pal_holy_prism_effect_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_holy_prism_effect_SpellScript();
    }
};

class spell_pal_hand_of_purity : public SpellScriptLoader
{
public:
    spell_pal_hand_of_purity() : SpellScriptLoader("spell_pal_hand_of_purity") { }

    class spell_pal_hand_of_purity_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_hand_of_purity_AuraScript);

        uint32 healtPct;

        bool Load()
        {
            healtPct = GetSpellInfo()->Effects[EFFECT_0].CalcValue(GetCaster());
            return GetUnitOwner()->ToPlayer();
        }

        void CalculateAmount(AuraEffect const* /*auraEffect*/, int32& amount, bool& /*canBeRecalculated*/)
        {
            amount = -1;
        }

        void Absorb(AuraEffect* /*auraEffect*/, DamageInfo& dmgInfo, uint32& absorbAmount)
        {
            Unit* target = GetTarget();
            if (!target)
                return;

            SpellInfo const* procSpell = dmgInfo.GetSpellInfo();
            if (!procSpell)
                return;

            if (!procSpell->HasAura(SPELL_AURA_PERIODIC_DAMAGE) && !procSpell->HasAura(SPELL_AURA_PERIODIC_DAMAGE_PERCENT))
                return;

            absorbAmount = CalculatePct(dmgInfo.GetDamage(), healtPct);
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_hand_of_purity_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            OnEffectAbsorb += AuraEffectAbsorbFn(spell_pal_hand_of_purity_AuraScript::Absorb, EFFECT_0);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_pal_hand_of_purity_AuraScript();
    }
};

class spell_pal_word_of_glory : public SpellScriptLoader
{
public:
    spell_pal_word_of_glory() : SpellScriptLoader("spell_pal_word_of_glory") { }

    class spell_pal_word_of_glory_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_word_of_glory_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_WORD_OF_GLORY))
                return false;
            return true;
        }

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (Unit* unitTarget = GetHitUnit())
                {
                    if ((unitTarget->GetTypeId() != TYPEID_PLAYER && !unitTarget->IsPet()) || unitTarget->IsHostileTo(_player))
                        unitTarget = _player;

                    int32 holyPower = _player->GetPower(POWER_HOLY_POWER);

                    if (holyPower > 2)
                        holyPower = 2;

                    _player->CastSpell(unitTarget, SPELL_PALADIN_WORD_OF_GLORY_HEAL, true);

                    if (_player->HasAura(SPELL_PALADIN_GLYPH_OF_WORD_OF_GLORY))
                    {
                        Aura* aura = _player->AddAura(SPELL_PALADIN_GLYPH_OF_WORD_OF_GLORY_DAMAGE, _player);

                        if (aura)
                        {
                            aura->GetEffect(0)->ChangeAmount(aura->GetEffect(0)->GetAmount() * (holyPower + 1));
                            aura->SetNeedClientUpdateForTargets();
                        }
                    }

                    if (!_player->HasAura(SPELL_PALADIN_DIVINE_PURPOSE))
                        _player->ModifyPower(POWER_HOLY_POWER, -holyPower);

                    if (_player->HasAura(PALADIN_ITEM_PVP_HOLY_4P_BONUS) && holyPower == 2)
                        _player->ModifyPower(POWER_HOLY_POWER, 1);
                }
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_pal_word_of_glory_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_word_of_glory_SpellScript();
    }
};

class spell_pal_judgment : public SpellScriptLoader
{
public:
    spell_pal_judgment() : SpellScriptLoader("spell_pal_judgment") { }

    class spell_pal_judgment_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_judgment_SpellScript);

        bool Validate(SpellInfo const* /*spellInfo*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_PALADIN_JUDGMENT))
                return false;
            return true;
        }

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (Unit* unitTarget = GetHitUnit())
                {
                    if (_player->HasAura(SPELL_PALADIN_JUDGMENTS_OF_THE_BOLD) || _player->HasAura(SPELL_PALADIN_JUDGMENTS_OF_THE_WISE))
                    {
                        int32 power = 1;
                        if (_player->HasAura(SPELL_PALADIN_HOLY_AVENGER))
                            power = 3;

                        _player->SetPower(POWER_HOLY_POWER, _player->GetPower(POWER_HOLY_POWER) + power);
                    }

                    if (_player->HasAura(SPELL_PALADIN_JUDGMENTS_OF_THE_BOLD))
                        _player->CastSpell(unitTarget, SPELL_PALADIN_PHYSICAL_VULNERABILITY, true);

                    if (_player->HasAura(SPELL_PALADIN_LONG_ARM_OF_THE_LAW))
                        _player->CastSpell(_player, SPELL_PALADIN_LONG_ARM_OF_THE_LAW_RUN_SPEED, true);

                    if (_player->HasAura(SPELL_PALADIN_BURDEN_OF_GUILT))
                        _player->CastSpell(unitTarget, SPELL_PALADIN_BURDEN_OF_GUILT_DECREASE_SPEED, true);
                }
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_pal_judgment_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_judgment_SpellScript();
    }
};

class spell_pal_art_of_war : public SpellScriptLoader
{
public:
    spell_pal_art_of_war() : SpellScriptLoader("spell_pal_art_of_war") { }

    class spell_pal_art_of_war_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_pal_art_of_war_SpellScript);

        void HandleOnHit()
        {
            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (_player->HasSpellCooldown(SPELL_PALADIN_EXORCISM))
                    _player->RemoveSpellCooldown(SPELL_PALADIN_EXORCISM, true);

                if (_player->HasSpellCooldown(SPELL_PALADIN_MASS_EXORCISM))
                    _player->RemoveSpellCooldown(SPELL_PALADIN_MASS_EXORCISM, true);
            }
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_pal_art_of_war_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_pal_art_of_war_SpellScript();
    }
};

class spell_pal_sacred_shield : public SpellScriptLoader
{
public:
    spell_pal_sacred_shield() : SpellScriptLoader("spell_pal_sacred_shield") { }

    class spell_pal_sacred_shield_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_sacred_shield_AuraScript);

        void OnTick(AuraEffect const* aurEff)
        {
            if (Unit* _player = GetCaster())
                if (Unit* target = GetTarget())
                    _player->CastSpell(target, SPELL_PALADIN_SACRED_SHIELD, true);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_pal_sacred_shield_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_pal_sacred_shield_AuraScript();
    }
};

class spell_pal_sacred_shield_absorb : public SpellScriptLoader
{
public:
    spell_pal_sacred_shield_absorb() : SpellScriptLoader("spell_pal_sacred_shield_absorb") { }

    class spell_pal_sacred_shield_absorb_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_sacred_shield_absorb_AuraScript);

        void CalculateAmount(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
        {
            if (GetCaster())
                amount = int32(30 + GetCaster()->SpellBaseDamageBonusDone(SPELL_SCHOOL_MASK_HOLY) * 1.17f);
        }

        void Register()
        {
            DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_pal_sacred_shield_absorb_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_pal_sacred_shield_absorb_AuraScript();
    }
};

class spell_pal_unbreakable_spirit : public SpellScriptLoader
{
public:
    spell_pal_unbreakable_spirit() : SpellScriptLoader("spell_pal_unbreakable_spirit") { }

    class spell_pal_unbreakable_spirit_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_pal_unbreakable_spirit_AuraScript);

        uint32 holyPowerConsumed;

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            holyPowerConsumed = 0;
        }

        void SetData(uint32 type, uint32 data)
        {
            if (!GetCaster())
                return;

            if (Player* _player = GetCaster()->ToPlayer())
            {
                holyPowerConsumed = data;

                if (_player->HasSpellCooldown(SPELL_PALADIN_DIVINE_SHIELD))
                {
                    uint32 newCooldownDelay = _player->GetSpellCooldownDelay(SPELL_PALADIN_DIVINE_SHIELD) * IN_MILLISECONDS;
                    uint32 totalCooldown = sSpellMgr->GetSpellInfo(SPELL_PALADIN_DIVINE_SHIELD)->RecoveryTime;
                    int32 lessCooldown = CalculatePct(totalCooldown, holyPowerConsumed);
                    uint32 maxCooldownReduction = CalculatePct(totalCooldown, 50);
                    newCooldownDelay -= lessCooldown;

                    if (newCooldownDelay > maxCooldownReduction)
                    {
                        _player->AddSpellCooldown(SPELL_PALADIN_DIVINE_SHIELD, 0, uint32(time(NULL) + newCooldownDelay / IN_MILLISECONDS));
                        _player->ToPlayer()->ModifySpellCooldown(SPELL_PALADIN_DIVINE_SHIELD, -lessCooldown);
                    }
                }
                if (_player->HasSpellCooldown(SPELL_PALADIN_LAY_ON_HANDS))
                {
                    uint32 newCooldownDelay = _player->GetSpellCooldownDelay(SPELL_PALADIN_LAY_ON_HANDS) * IN_MILLISECONDS;
                    uint32 totalCooldown = sSpellMgr->GetSpellInfo(SPELL_PALADIN_LAY_ON_HANDS)->CategoryRecoveryTime;
                    int32 lessCooldown = CalculatePct(totalCooldown, holyPowerConsumed);
                    uint32 maxCooldownReduction = CalculatePct(totalCooldown, 50);

                    newCooldownDelay -= lessCooldown;

                    if (newCooldownDelay > maxCooldownReduction)
                    {
                        _player->AddSpellCooldown(SPELL_PALADIN_LAY_ON_HANDS, 0, uint32(time(NULL) + newCooldownDelay / IN_MILLISECONDS));
                        _player->ToPlayer()->ModifySpellCooldown(SPELL_PALADIN_LAY_ON_HANDS, -lessCooldown);
                    }
                }
                if (_player->HasSpellCooldown(SPELL_PALADIN_DIVINE_PROTECTION))
                {
                    uint32 newCooldownDelay = _player->GetSpellCooldownDelay(SPELL_PALADIN_DIVINE_PROTECTION) * IN_MILLISECONDS;
                    uint32 totalCooldown = sSpellMgr->GetSpellInfo(SPELL_PALADIN_DIVINE_PROTECTION)->RecoveryTime;
                    int32 lessCooldown = CalculatePct(totalCooldown, holyPowerConsumed);
                    uint32 maxCooldownReduction = CalculatePct(totalCooldown, 50);

                    newCooldownDelay -= lessCooldown;

                    if (newCooldownDelay > maxCooldownReduction)
                    {
                        _player->AddSpellCooldown(SPELL_PALADIN_DIVINE_PROTECTION, 0, uint32(time(NULL) + newCooldownDelay / IN_MILLISECONDS));
                        _player->ToPlayer()->ModifySpellCooldown(SPELL_PALADIN_DIVINE_PROTECTION, -lessCooldown);
                    }
                }
            }
        }

        void Register()
        {
            AfterEffectApply += AuraEffectApplyFn(spell_pal_unbreakable_spirit_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_pal_unbreakable_spirit_AuraScript();
    }
};


void AddSC_paladin_spell_scripts()
{
    new spell_pal_holy_shock();
    new spell_mastery_hand_of_light();
    new spell_pal_inquisition();
    new spell_pal_holy_prism();
    new spell_pal_holy_prism_visual();
    new spell_pal_holy_prism_effect();
    new spell_pal_hand_of_purity();
    new spell_pal_word_of_glory();
    new spell_pal_judgment();
    new spell_pal_art_of_war();
    new spell_pal_sacred_shield();
    new spell_pal_sacred_shield_absorb();
    new spell_pal_unbreakable_spirit();
}
