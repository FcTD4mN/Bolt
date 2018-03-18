#pragma once

#include <limits>

namespace  nBitvolume
{

typedef  unsigned  char         tByte;                  // Consider 8 bits, [0, 255]. Smallest addressable unit.
typedef  unsigned  short  int   t2Byte;                 // Consider 16 bits, [0, 65535]. Typical extended voxel data.
static  const  t2Byte           sgFirstByteMask = 0x00FF;
static  const  t2Byte           sgSecondByteMask = 0xFF00;
typedef  short  int             tKeyComponent;              // Consider 16 bits, [−32,767, +32,767]. See also USHRT_MAX
typedef  long  long  int        tHashableKeySignature;      // Consider 64 bits.
typedef  long  int              tGlobalDataIndex;           // Consider 32 bits, [−2,147,483,647, +2,147,483,647]
typedef  tByte                  tLocalDataIndex;             // Consider 8 bits.
static  const  tByte            sgEmptyMaterial = 0;

enum  eChunkNeighbourIndex : tByte
{
    kTop    = 0,
    kBot    = 1,
    kFront  = 2,
    kBack   = 3,
    kLeft   = 4,
    kRight  = 5,
};

#define  IJK_ITERATION_BEGIN( iSize )     for( tByte  i = 0; i < iSize; ++i )            \
                                            {                                              \
                                                for( tByte  j = 0; j < iSize; ++j )         \
                                                {                                           \
                                                    for( tByte  k = 0; k < iSize; ++k )     \
                                                    {

#define  IJK_ITERATION_END     }}}

#define KEY_EXISTS( iMap, iKey )            ( ! ( iMap.find( iKey ) == iMap.end() ) )

}