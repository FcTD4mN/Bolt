#include "Volumetric.SparseOctree.EntropicRawData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N LOD, typename Atomic >
inline  cEntropicRawData< LOD, Atomic >::~cEntropicRawData()
{
}


template< eLod2N LOD, typename Atomic >
inline  cEntropicRawData< LOD, Atomic >::cEntropicRawData( const  cROMSConfig*  iROMSConfig ) :
    cEntropicData( iROMSConfig )
{
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------- Virtual Runtime Information Overrides


template< eLod2N LOD, typename Atomic >
inline  bool  cEntropicRawData< LOD, Atomic >::Compressed()  const
{
    return  false;
}


template< eLod2N LOD, typename Atomic >
inline  eSubType  cEntropicRawData< LOD, Atomic >::SubType()  const
{
    return  eSubType::kRaw;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Data Accessors


template< eLod2N LOD, typename Atomic >
inline  const  Atomic&  cEntropicRawData< LOD, Atomic >::Get( tIndex iX, tIndex iY, tIndex iZ )  const
{
    // TODO: insert return statement here
}


template< eLod2N LOD, typename Atomic >
inline  void  cEntropicRawData< LOD, Atomic >::Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic& iValue )
{
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

