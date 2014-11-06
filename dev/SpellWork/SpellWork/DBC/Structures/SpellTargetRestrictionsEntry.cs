namespace TimelessWork.DBC.Structures
{
    public sealed class SpellTargetRestrictionsEntry
    {
        public uint Id;
        public uint SpellId;
        public uint UnkMop; // Mop
        public float Unknown1;
        public float UnkMop2; // Mop
        public uint MaxAffectedTargets;
        public uint MaxTargetLevel;
        public uint TargetCreatureType;
        public uint Targets;
    }
}
