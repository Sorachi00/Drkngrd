// GS address permutations, equivalent to the storage-element lookup tables.
uint BlockTableC32(uint i) { return ((i & 8u) >> 2) ^ ((i & 16u) >> 1) ^ (i & 1u) ^ ((i & 2u) << 1) ^ ((i & 4u) << 2); }
uint BlockTableZ32(uint i) { return 24u ^ ((i & 8u) >> 2) ^ ((i & 16u) >> 1) ^ (i & 1u) ^ ((i & 2u) << 1) ^ ((i & 4u) << 2); }
uint BlockTableC16(uint i) { return ((i & 4u) >> 2) ^ ((i & 8u) >> 1) ^ (i & 16u) ^ ((i & 1u) << 1) ^ ((i & 2u) << 2); }
uint BlockTableC16S(uint i) { return ((i & 20u) >> 2) ^ (i & 8u) ^ ((i & 1u) << 1) ^ ((i & 2u) << 3); }
uint BlockTableZ16(uint i) { return 24u ^ ((i & 4u) >> 2) ^ ((i & 8u) >> 1) ^ (i & 16u) ^ ((i & 1u) << 1) ^ ((i & 2u) << 2); }
uint BlockTableZ16S(uint i) { return 24u ^ ((i & 20u) >> 2) ^ (i & 8u) ^ ((i & 1u) << 1) ^ ((i & 2u) << 3); }
uint BlockTableP8(uint i) { return ((i & 8u) >> 2) ^ ((i & 16u) >> 1) ^ (i & 1u) ^ ((i & 2u) << 1) ^ ((i & 4u) << 2); }
uint BlockTableP4(uint i) { return ((i & 4u) >> 2) ^ ((i & 8u) >> 1) ^ (i & 16u) ^ ((i & 1u) << 1) ^ ((i & 2u) << 2); }
uint ColumnTable32(uint i) { return ((i & 8u) >> 2) ^ (i & 49u) ^ ((i & 6u) << 1); }
uint ColumnTable16(uint i) { return ((i & 8u) >> 3) ^ ((i & 16u) >> 2) ^ (i & 96u) ^ ((i & 1u) << 1) ^ ((i & 6u) << 2); }
uint ColumnTable8(uint i) { return ((i & 32u) >> 5) ^ ((i & 8u) >> 2) ^ ((i & 80u) >> 1) ^ (i & 224u) ^ ((i & 1u) << 2) ^ ((i & 6u) << 3); }
uint ColumnTable4(uint i) { return ((i & 64u) >> 6) ^ ((i & 24u) >> 2) ^ ((i & 160u) >> 1) ^ (i & 448u) ^ ((i & 1u) << 3) ^ ((i & 6u) << 4); }
