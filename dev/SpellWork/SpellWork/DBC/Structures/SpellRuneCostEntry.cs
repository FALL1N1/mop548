using DBFilesClient.NET;

namespace TimelessWork.DBC.Structures
{
    public sealed class SpellRuneCostEntry
    {
        public uint Id;
        [StoragePresence(StoragePresenceOption.Include, ArraySize = 3)]
        public uint[] RuneCost;
        public uint UnkMop; // Mop - 4th rune ??
        public uint RunicPowerGain;
    }
}
