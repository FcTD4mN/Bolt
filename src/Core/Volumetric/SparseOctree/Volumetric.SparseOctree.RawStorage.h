#pragma once


#include "Volumetric.SparseOctree.Types.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cRawStorage
{

public:
    // Construction / Destruction
    virtual  ~cRawStorage();
    cRawStorage();
    cRawStorage( const  cRawStorage& ) = delete;

private:
    // Private Member Data
    static  const  tSize  mSize = tSize( LOD );
    Atomic  mCore[mSize][mSize][mSize];
};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Volumetric.SparseOctree.RawStorage.hpp"

