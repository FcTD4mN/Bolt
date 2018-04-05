#include "Volumetric.SparseOctree.OrderedData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N LOD, typename Atomic >
inline  cOrderedData< LOD, Atomic >::~cOrderedData()
{
}


template< eLod2N LOD, typename Atomic >
inline  cOrderedData< LOD, Atomic >::cOrderedData( const  cROMSConfig* iROMSConfig ) :
    cData( iROMSConfig )
{
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------- Virtual Runtime Information Overrides


template< eLod2N LOD, typename Atomic >
inline  bool  cOrderedData< LOD, Atomic >::Compressed()  const
{
    return  true;
}


template< eLod2N LOD, typename Atomic >
inline  eType  cOrderedData< LOD, Atomic >::Type()  const
{
    return  eType::kOrdered;
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

