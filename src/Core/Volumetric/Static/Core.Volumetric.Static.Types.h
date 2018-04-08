#pragma once

#include <limits>

namespace  nVolumetric
{

typedef  unsigned  char                 tByte;                      // Consider 8 bits, [0, 255]. Smallest addressable unit.
typedef  unsigned  short  int           t2Byte;                     // Consider 16 bits, [0, 65535]. Typical extended voxel data.
typedef  short  int                     tKeyComponent;              // Consider 16 bits, [−32,767, +32,767]. See also USHRT_MAX
typedef  short  int                     tUKeyComponent;             // Consider 16 bits, [0, 65535]. Extended range for signed data field handling
typedef  long  long  unsigned  int      tHashableKeySignature;      // Consider 64 bits, [0, +18,446,744,073,709,551,615]
typedef  long  int                      tGlobalDataIndex;           // Consider 32 bits, [−2,147,483,647, +2,147,483,647]
typedef  tByte                          tLocalDataIndex;            // Consider 8 bits.
static  const  tByte                    sgEmptyMaterial = 0;
static  const  tHashableKeySignature    sgSignedKeyComponentRangeShift= 0x7FFF;

#ifndef BUFFER_OFFSET
    #define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif

enum  eNF_Flag: tByte
{
    kFlagNone       = 0,    // 0000 0000    // -
    kFlagTop        = 1,    // 0000 0001    // 2^0
    kFlagBot        = 2,    // 0000 0010    // 2^1
    kFlagFront      = 4,    // 0000 0100    // 2^2
    kFlagBack       = 8,    // 0000 1000    // 2^3
    kFlagLeft       = 16,   // 0001 0000    // 2^4
    kFlagRight      = 32,   // 0010 0000    // 2^5
};

enum  eNF_Index : tByte
{
    kIndexTop       = 0,
    kIndexBot       = 1,
    kIndexFront     = 2,
    kIndexBack      = 3,
    kIndexLeft      = 4,
    kIndexRight     = 5,
};

} // namespace  nVolumetric

