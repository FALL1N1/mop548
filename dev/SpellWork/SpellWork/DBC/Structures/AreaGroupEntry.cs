using DBFilesClient.NET;

namespace TimelessWork.DBC.Structures
{
    public sealed class AreaGroupEntry
    {
        public uint Id;
        [StoragePresence(StoragePresenceOption.Include, ArraySize = 6)]
        public uint[] AreaId;
        public uint NextGroup;
    }
}
