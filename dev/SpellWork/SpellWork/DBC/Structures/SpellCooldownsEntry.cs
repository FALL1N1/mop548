namespace TimelessWork.DBC.Structures
{
    public sealed class SpellCooldownsEntry
    {
        public uint Id;
        public uint SpellId;
        public uint UnkMop; // Mop
        public uint CategoryRecoveryTime;
        public uint RecoveryTime;
        public uint StartRecoveryTime;
    }
}
