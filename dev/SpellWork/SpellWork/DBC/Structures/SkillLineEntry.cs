namespace TimelessWork.DBC.Structures
{
    public sealed class SkillLineEntry
    {
        public uint Id;
        public int CategoryId;
        public string Name;
        public string Description;
        public uint SpellIcon;
        public string AlternateVerb;
        public uint CanLink;
        public uint UnkMop1; // Mop
        public uint UnkMopFlags2; // Mop
    }
}
