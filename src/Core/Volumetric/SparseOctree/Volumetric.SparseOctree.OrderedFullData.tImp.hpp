#include "Volumetric.SparseOctree.OrderedFullData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N LOD, typename Atomic >
inline  cOrderedFullData< LOD, Atomic >::~cOrderedFullData()
{
    mValue = Atomic( 0 );

    ~cOrderedData();
}


template< eLod2N LOD, typename Atomic >
inline  cOrderedFullData< LOD, Atomic >::cOrderedFullData( const  cROMSConfig*  iROMSConfig ) :
    cOrderedData( iROMSConfig )
{
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------- Virtual Runtime Information Overrides


template< eLod2N LOD, typename Atomic >
inline  eSubType  cOrderedFullData< LOD, Atomic >::SubType()  const
{
    return  eSubType::kFull;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Data Accessors


template< eLod2N LOD, typename Atomic >
inline  const  Atomic&  cOrderedFullData< LOD, Atomic >::Get( tIndex iX, tIndex iY, tIndex iZ )  const
{
    // The same everywhere
    return  mValue;
}


template< eLod2N LOD, typename Atomic >
inline  void  cOrderedFullData< LOD, Atomic >::Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic& iValue )
{
    // Should never be called on Full Data
    assert( 0 );
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------- Data Transform Analysis


template< eLod2N LOD, typename Atomic >
inline  cDataPreCheckAnalysis  cOrderedData< LOD, Atomic >::PreCheckOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
{
    if( LOD == cData::ROMSConfig() )
        return  cDataPreCheckAnalysis( cDataPreCheckAnalysis::eTransformOperationStatus::kRequired,
                                       eType::kOrdered, eSubType::kEmpty,
                                       eType::kEntropic, eSubType::kRaw );
    else
        return  cDataPreCheckAnalysis( cDataPreCheckAnalysis::eTransformOperationStatus::kRequired,
                                       eType::kOrdered, eSubType::kEmpty,
                                       eType::kSparse, eSubType::kNone );
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

