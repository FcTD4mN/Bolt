#pragma once


#include "Core.Volumetric.SparseOctree.ROMSChunk.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, eLod2N Micro, typename Atomic >
class cUSROCMap;


template< eLod2N LOD, eLod2N Micro, typename Atomic >
class  cRootROMSChunk final :
    public cROMSChunk< LOD, Atomic >
{

public:
    // Construction / Destruction
    virtual  ~cRootROMSChunk();
    cRootROMSChunk( cUSROCMap< LOD, Micro, Atomic >* iParent, const  cROMSConfig*  iROMSConfig, eType iDataStartType = eType::kEmpty, const  Atomic& iStartValue = Atomic( 0 ) );
    cRootROMSChunk( const  cRootROMSChunk& ) = delete;

private:
    // Private Member Data
    cUSROCMap< LOD, Micro, Atomic >*  mParent;
};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Core.Volumetric.SparseOctree.RootROMSChunk.tImp.hpp"

