#include "Core.Volumetric.SparseOctree.EntropicData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N LOD, typename Atomic >
inline  cEntropicData< LOD, Atomic >::~cEntropicData()
{
}


template< eLod2N LOD, typename Atomic >
inline  cEntropicData< LOD, Atomic >::cEntropicData( const  cROMSConfig*  iROMSConfig ) :
    cData( iROMSConfig )
{
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------- Virtual Runtime Information Overrides


template< eLod2N LOD, typename Atomic >
inline  eType  cEntropicData< LOD, Atomic >::Type()  const
{
    return eType::kEntropic;
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

