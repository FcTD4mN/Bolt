#pragma once


#include "Core.Volumetric.SparseOctree.ROMSChunk.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class cSparseData;


template< eLod2N ParentLOD, eLod2N LOD, typename Atomic >
class  cNodeROMSChunk final :
    public cROMSChunk< LOD, Atomic >
{

public:
    // Construction / Destruction
    virtual  ~cNodeROMSChunk();
    cNodeROMSChunk( cSparseData< ParentLOD, Atomic >* iParent, const  cROMSConfig*  iROMSConfig, eType iDataStartType = eType::kEmpty, const  Atomic& iStartValue = Atomic( 0 ) );
    cNodeROMSChunk( const  cNodeROMSChunk& ) = delete;

private:
    // Private Member Data
    cSparseData< ParentLOD, Atomic >* mParent;

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#undef  DOUBLED


#include "Core.Volumetric.SparseOctree.NodeROMSChunk.tImp.hpp"

