#include "Core.Volumetric.SparseOctree.RootROMSChunk.h"


#include "Core.Volumetric.SparseOctree.USROCMap.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N Macro, eLod2N VBO, eLod2N Micro, typename Atomic >
inline  cRootROMSChunk< Macro, VBO, Micro, Atomic >::~cRootROMSChunk()
{
}


template< eLod2N Macro, eLod2N VBO, eLod2N Micro, typename Atomic >
inline  cRootROMSChunk< Macro, VBO, Micro, Atomic >::cRootROMSChunk( cUSROCMap< Macro, VBO, Micro, Atomic >* iParent, const  cROMSConfig*  iROMSConfig, eType iDataStartType, const  Atomic& iStartValue ) :
    cROMSChunk< Macro, Atomic >( iROMSConfig, iDataStartType, iStartValue ),
    mParent( iParent )
{
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

