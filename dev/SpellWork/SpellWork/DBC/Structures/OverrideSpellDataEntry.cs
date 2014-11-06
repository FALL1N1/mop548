using DBFilesClient.NET;

namespace TimelessWork.DBC.Structures
{
    public sealed class OverrideSpellDataEntry
    {
        public uint Id;
        [StoragePresence(StoragePresenceOption.Include, ArraySize = 10)]
        public uint[] Spells;
        public uint Unk;
        public string Name;
    }
}
