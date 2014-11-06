namespace TimelessWork.DBC.Structures
{
    public sealed class SpellAuraRestrictionsEntry
    {
        public uint Id;
        public uint SpellId;
        public uint UnkMop; // Mop
        public uint CasterAuraState;
        public uint TargetAuraState;
        public uint CasterAuraStateNot;
        public uint TargetAuraStateNot;
        public uint CasterAuraSpell;
        public uint TargetAuraSpell;
        public uint ExcludeCasterAuraSpell;
        public uint ExcludeTargetAuraSpell;
    }
}
