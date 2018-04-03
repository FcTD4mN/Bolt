#pragma once


#include "Volumetric.SparseOctree.Types.h"
#include "Volumetric.SparseOctree.Data.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


class  cROMSConfig;


template< eLod2N LOD, typename Atomic >
class  cROMSChunk
{

protected:
    // Construction / Destruction
    virtual  ~cROMSChunk();
    cROMSChunk();
    cROMSChunk( const  cROMSChunk& ) = delete;

private:
    // Private Member Data
    cData< LOD, Atomic >*  mData;
    cROMSConfig*  mROMSConfig;
};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Volumetric.SparseOctree.ROMSChunk.hpp"

