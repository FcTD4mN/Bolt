#pragma once

#include <limits>

namespace  nVoxel
{

typedef  unsigned  char         tByte;                  // Consider 8 bits, [0, 255]. Smallest addressable unit.
typedef  unsigned  short  int   t2Byte;                 // Consider 16 bits, [0, 65535]. Typical extended voxel data.
static  const  unsigned  int    sgFirstByteMask = 0x00FF;
static  const  unsigned  int    sgSecondByteMask = 0xFF00;

typedef  short  int             tKeyComponent;          // Consider 16 bits, [−32,767, +32,767]. See also USHRT_MAX
typedef  long  long  int        tHashedKeySignature;    // Consider 64 bits.
typedef  long  int              tDataIndex;             // Consider 32 bits.

enum  eBaseMaterials : tByte
{
    kEmpty = 0,
    kSolid = UCHAR_MAX,
};

enum  eChunkNeighbour : tByte
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

template< tByte N >  class  cStaticLodChunkN;
typedef  cStaticLodChunkN< 64 > tStaticLodChunk64;


#define KEY_EXISTS( iMap, iKey )            ( ! ( iMap.find( iKey ) == iMap.end() ) )

}