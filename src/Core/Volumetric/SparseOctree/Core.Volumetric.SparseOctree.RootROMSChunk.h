#pragma once


#include "Core.Volumetric.SparseOctree.ROMSChunk.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N Macro, eLod2N VBO, eLod2N Micro, typename Atomic >
class cUSROCMap;


template< eLod2N Macro, eLod2N VBO, eLod2N Micro, typename Atomic >
class  cRootROMSChunk final :
    public cROMSChunk< Macro, Atomic >
{

public:
    // Construction / Destruction
    virtual  ~cRootROMSChunk();
    cRootROMSChunk( cUSROCMap< Macro, VBO, Micro, Atomic >* iParent, const  cROMSConfig*  iROMSConfig, eType iDataStartType = eType::kEmpty, const  Atomic& iStartValue = Atomic( 0 ) );
    cRootROMSChunk( const  cRootROMSChunk& ) = delete;

private:
    // Private Member Data
    cUSROCMap< Macro, VBO, Micro, Atomic >*  mParent;
};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Core.Volumetric.SparseOctree.RootROMSChunk.tImp.hpp"

