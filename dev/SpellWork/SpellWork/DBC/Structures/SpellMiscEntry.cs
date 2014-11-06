using System.Linq;
using DBFilesClient.NET;
using System.Text;

namespace TimelessWork.DBC.Structures
{
    public class SpellMiscEntry
    {
        public uint Id;
        public uint SpellId;
        public uint UnkMop; // Mop
        public uint Attributes;
        public uint AttributesEx;
        public uint AttributesEx2;
        public uint AttributesEx3;
        public uint AttributesEx4;
        public uint AttributesEx5;
        public uint AttributesEx6;
        public uint AttributesEx7;
        public uint AttributesEx8;
        public uint AttributesEx9;
        public uint AttributesEx10;
        public uint AttributesEx11;
        public uint AttributesEx12;
        public uint AttributesEx13;
        public uint CastingTimeIndex;
        public uint DurationIndex;
        public uint RangeIndex;
        public float Speed;
        [StoragePresence(StoragePresenceOption.Include, ArraySize = 2)]
        public uint[] SpellVisual;
        public uint SpellIconID;
        public uint ActiveIconID;
        public uint SchoolMask;
    }
}
