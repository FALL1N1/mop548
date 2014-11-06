using DBFilesClient.NET;

namespace TimelessWork.DBC.Structures
{
    public sealed class SpellScalingEntry
    {
        public uint Id;
        public int MinCastTime;
        public int MaxCastTime;
        public uint MaxCastTimeLevel;   // player level at which cast time reaches max value
        public int PlayerClass;
        public float CoefBase;
        public uint CoefLevelBase;
        public uint UnkMop1; // Mop
        public uint UnkMop2; // Mop
    }
}
