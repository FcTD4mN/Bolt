#pragma once

#include <limits>

namespace  nVoxel
{

typedef  unsigned  char     tByte;                  // Consider 8 bits, [0, 255]. Smallest addressable unit for individual voxel data.
typedef  short  int         tKeyComponent;          // Consider 16 bits, [−32,767, +32,767]. See also USHRT_MAX
typedef  long  long  int    tHashedKeySignature;    // Consider 64 bits.

enum  eBaseMaterials : tByte
{
    kEmpty = 0,
    kSolid = UCHAR_MAX,
};

static  tByte sgChunkMaxNeighbours = 6;
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

}