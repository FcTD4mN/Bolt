#pragma once


#include <cstdint>


namespace  nVolumetric      {
namespace  nSparseOctree    {


typedef  uint8_t    tByte;
typedef  uint16_t   t2Byte;
typedef  uint16_t   tIndex;
typedef  uint16_t   tSize;
typedef  int32_t    tGlobalIndex;
typedef  uint64_t   tVolume;
typedef  uint64_t   tLargeByteSize;

typedef  uint64_t   tHashableKeySignature;
static  const  tHashableKeySignature  sgSignedKeyComponentRangeShift= 0x7FFF;

enum  eLod2N : t2Byte
{
    kLod0 = 1,
    kLod1 = 2,
    kLod2 = 4,
    kLod3 = 8,
    kLod4 = 16,
    kLod5 = 32,
    kLod6 = 64,
    kLod7 = 128,
    kLod8 = 256,
    kLod9 = 512,
};


// Runtime Information Enums
enum  eType
{
    kOrdered,
    kSparse,
    kEntropic
};

enum  eSubType
{
    kEmpty,
    kFull,

    kNone,

    kRaw,
    kRLE
};

}  // namespace  nSparseOctree
}  // namespace  nVolumetric

