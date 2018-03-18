#pragma once

#include <limits>

namespace  nVolumetric
{

typedef  unsigned  char         tByte;                      // Consider 8 bits, [0, 255]. Smallest addressable unit.
typedef  unsigned  short  int   t2Byte;                     // Consider 16 bits, [0, 65535]. Typical extended voxel data.
typedef  short  int             tKeyComponent;              // Consider 16 bits, [−32,767, +32,767]. See also USHRT_MAX
typedef  long  long  int        tHashableKeySignature;      // Consider 64 bits.
typedef  long  int              tGlobalDataIndex;           // Consider 32 bits, [−2,147,483,647, +2,147,483,647]
typedef  tByte                  tLocalDataIndex;            // Consider 8 bits.
static  const  tByte            sgEmptyMaterial = 0;

} // namespace  nVolumetric

