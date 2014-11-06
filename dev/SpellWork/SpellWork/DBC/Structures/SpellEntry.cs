using System.Linq;
using DBFilesClient.NET;
using System.Text;

namespace TimelessWork.DBC.Structures
{
    public sealed class SpellEntry
    {
        public uint Id;
        public string SpellName;
        public string Rank;
        public string Description;
        public string ToolTip;
        public uint RuneCostID;
        public uint SpellMissileID;
        public uint SpellDescriptionVariableID;
        public uint SpellDifficultyId;
        public uint SpellScalingId;
        public uint SpellAuraOptionsId;
        public uint SpellAuraRestrictionsId;
        public uint SpellCastingRequirementsId;
        public uint SpellCategoriesId;
        public uint SpellClassOptionsId;
        public uint SpellCooldownsId;
        public uint SpellEquippedItemsId;
        public uint SpellInterruptsId;
        public uint SpellLevelsId;
        public uint SpellReagentsId;
        public uint SpellShapeshiftId;
        public uint SpellTargetRestrictionsId;
        public uint SpellTotemsId;
        public uint ResearchProjectId;
        public uint SpellMiscId;

        public SpellAuraOptionsEntry AuraOptions
        {
            get { return SpellAuraOptionsId != 0 && DBC.SpellAuraOptions.ContainsKey(SpellAuraOptionsId) ? DBC.SpellAuraOptions[SpellAuraOptionsId] : null; }
        }

        public SpellAuraRestrictionsEntry AuraRestrictions
        {
            get { return SpellAuraRestrictionsId != 0 && DBC.SpellAuraRestrictions.ContainsKey(SpellAuraRestrictionsId) ? DBC.SpellAuraRestrictions[SpellAuraRestrictionsId] : null; }
        }

        public SpellCastingRequirementsEntry CastingRequirements
        {
            get { return SpellCastingRequirementsId != 0 && DBC.SpellCastingRequirements.ContainsKey(SpellCastingRequirementsId) ? DBC.SpellCastingRequirements[SpellCastingRequirementsId] : null; }
        }

        public SpellCategoriesEntry Category
        {
            get { return SpellCategoriesId != 0 && DBC.SpellCategories.ContainsKey(SpellCategoriesId) ? DBC.SpellCategories[SpellCategoriesId] : null; }
        }

        public SpellClassOptionsEntry ClassOptions
        {
            get { return SpellClassOptionsId != 0 && DBC.SpellClassOptions.ContainsKey(SpellClassOptionsId) ? DBC.SpellClassOptions[SpellClassOptionsId] : null; }
        }

        public SpellCooldownsEntry Cooldowns
        {
            get { return SpellCooldownsId != 0 && DBC.SpellCooldowns.ContainsKey(SpellCooldownsId) ? DBC.SpellCooldowns[SpellCooldownsId] : null; }
        }

        public SpellEquippedItemsEntry EquippedItems
        {
            get { return SpellEquippedItemsId != 0 && DBC.SpellEquippedItems.ContainsKey(SpellEquippedItemsId) ? DBC.SpellEquippedItems[SpellEquippedItemsId] : null; }
        }

        public SpellInterruptsEntry Interrupts
        {
            get { return SpellInterruptsId != 0 && DBC.SpellInterrupts.ContainsKey(SpellInterruptsId) ? DBC.SpellInterrupts[SpellInterruptsId] : null; }
        }

        public SpellLevelsEntry Levels
        {
            get { return SpellLevelsId != 0 && DBC.SpellLevels.ContainsKey(SpellLevelsId) ? DBC.SpellLevels[SpellLevelsId] : null; }
        }


        public SpellPowerEntry Power
        {
            get
            {
                var query = from powerEntry in DBC.SpellPower.Values where powerEntry.SpellId == Id select powerEntry;
                return query.ToList().Count != 0 ? query.ToList()[0] : null;
            }
        }

        public SpellReagentsEntry Reagents
        {
            get { return SpellReagentsId != 0 && DBC.SpellReagents.ContainsKey(SpellReagentsId) ? DBC.SpellReagents[SpellReagentsId] : null; }
        }

        public SpellScalingEntry Scaling
        {
            get { return SpellScalingId != 0 && DBC.SpellScaling.ContainsKey(SpellScalingId) ? DBC.SpellScaling[SpellScalingId] : null; }
        }

        public SpellShapeshiftEntry Shapeshift
        {
            get { return SpellShapeshiftId != 0 && DBC.SpellShapeshift.ContainsKey(SpellShapeshiftId) ? DBC.SpellShapeshift[SpellShapeshiftId] : null; }
        }

        public SpellTargetRestrictionsEntry TargetRestrictions
        {
            get { return SpellTargetRestrictionsId != 0 && DBC.SpellTargetRestrictions.ContainsKey(SpellTargetRestrictionsId) ? DBC.SpellTargetRestrictions[SpellTargetRestrictionsId] : null; }
        }

        public SpellTotemsEntry Totems
        {
            get { return SpellTotemsId != 0 && DBC.SpellTotems.ContainsKey(SpellTotemsId) ? DBC.SpellTotems[SpellTotemsId] : null; }
        }

        public SpellMiscEntry Misc
        {
            get { return SpellMiscId != 0 && DBC.SpellMisc.ContainsKey(SpellMiscId) ? DBC.SpellMisc[SpellMiscId] : null; }
        }
    }
}
