#include "Volumetric.SparseOctree.Data.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template<eLod2N LOD,typename Atomic>
inline cData<LOD,Atomic>::~cData()
{
    mROMSConfig = 0; // Non-Owning
}


template<eLod2N LOD,typename Atomic>
inline cData<LOD,Atomic>::cData( const cROMSConfig * iROMSConfig ) :
    mROMSConfig( iROMSConfig )
{
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------ Template Data Container Accessors


template< eLod2N LOD, typename Atomic >
inline  eLod2N  cData< LOD, Atomic >::LOD()  const
{
    return  LOD;
}


template< eLod2N LOD, typename Atomic >
inline  tSize  cData< LOD, Atomic >::Size()  const
{
    return  tSize( LOD() );
}


template< eLod2N LOD, typename Atomic >
inline  tVolume  cData< LOD, Atomic >::Capacity()  const
{
    return  mCapacity;
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

