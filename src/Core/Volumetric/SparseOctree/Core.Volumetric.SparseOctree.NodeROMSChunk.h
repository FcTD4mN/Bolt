#pragma once


#include "Core.Volumetric.SparseOctree.ROMSChunk.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cNodeROMSChunk final :
    public cROMSChunk< LOD, Atomic >
{

public:
    // Construction / Destruction
    virtual  ~cNodeROMSChunk();
    cNodeROMSChunk( const  cROMSConfig*  iROMSConfig, eType iDataStartType = eType::kEmpty, const  Atomic& iStartValue = Atomic( 0 ) );
    cNodeROMSChunk( const  cNodeROMSChunk& ) = delete;

private:
    // Private Member Data

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Core.Volumetric.SparseOctree.NodeROMSChunk.tImp.hpp"

