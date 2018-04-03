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

static  const  tLargeByteSize  sgGPU_BUS_MAX = 500000;


enum  eLod2N : t2Byte
{
    kLod1   = 1,
    kLod2   = 2,
    kLod4   = 4,
    kLod8   = 8,
    kLod16  = 16,
    kLod32  = 32,
    kLod64  = 64,
    kLod128 = 128,
    kLod256 = 256,
    kLod512 = 512,
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

