#include "Volumetric.SparseOctree.OrderedFullData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N LOD, typename Atomic >
inline  cOrderedFullData< LOD, Atomic >::~cOrderedFullData()
{
    mValue = Atomic( 0 );
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
inline  cDataReportAnalysis< Atomic >  cOrderedFullData< LOD, Atomic >::AnteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
{
    if( Get( iX, iY ,iZ ) == iValue )
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                       cDataReportAnalysis::eProcessOperationStatus::kDiscard );

    if( LOD > ROMSConfig().MicroscopicLODGranularity() )
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kProcess,
                                     eType::kOrdered, eSubType::kFull,
                                     eType::kSparse, eSubType::kNone );
    else if( LOD == ROMSConfig().MicroscopicLODGranularity() )
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kProcess,
                                     eType::kOrdered, eSubType::kFull,
                                     eType::kEntropic, eSubType::kRaw );
    else
        assert( false ); // Crash
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

