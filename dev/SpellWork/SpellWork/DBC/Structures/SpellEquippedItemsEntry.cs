namespace TimelessWork.DBC.Structures
{
    public sealed class SpellEquippedItemsEntry
    {
        public uint Id;
        public uint SpellId;
        public uint UnkMop; // Mop
        public uint EquippedItemClass;
        public uint EquippedItemInventoryTypeMask;
        public uint EquippedItemSubClassMask;
    }
}
