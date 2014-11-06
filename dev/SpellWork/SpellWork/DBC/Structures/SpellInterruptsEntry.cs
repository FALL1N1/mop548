namespace TimelessWork.DBC.Structures
{
    public sealed class SpellInterruptsEntry
    {
        public uint Id;
        public uint SpellId;
        public uint UnkMop; // Mop
        public uint AuraInterruptFlags;
        public uint Unknown1;
        public uint ChannelInterruptFlags;
        public uint Unknown2;
        public uint InterruptFlags;
    }
}
