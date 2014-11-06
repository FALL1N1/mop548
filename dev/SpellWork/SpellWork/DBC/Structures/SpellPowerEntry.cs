namespace TimelessWork.DBC.Structures
{
    public sealed class SpellPowerEntry
    {
        public uint Id;
        public uint SpellId;
        public uint UnkMop1; // Mop
        public uint PowerType;
        public uint ManaCost;
        public uint ManaCostPerlevel;
        public uint ManaPerSecond;
        public uint ManaPerSecondPerLevel;
        public uint PowerDisplayId; // Most likely
        public float ManaCostPercentage;
        public float UnknownMop2; // Mop
        public float UnknownMop3; // Mop
        public float UnknownMop4; // Mop
    }
}
