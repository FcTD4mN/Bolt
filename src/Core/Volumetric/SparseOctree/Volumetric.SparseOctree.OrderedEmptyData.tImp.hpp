#include "Volumetric.SparseOctree.OrderedEmptyData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N LOD, typename Atomic >
inline  cOrderedEmptyData< LOD, Atomic >::~cOrderedEmptyData()
{
}


template< eLod2N LOD, typename Atomic >
inline  cOrderedEmptyData< LOD, Atomic >::cOrderedEmptyData( const  cROMSConfig*  iROMSConfig ) :
    cOrderedData( iROMSConfig )
{
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------- Virtual Runtime Information Overrides


template< eLod2N LOD, typename Atomic >
inline  eSubType  cOrderedEmptyData< LOD, Atomic >::SubType()  const
{
    return  eSubType::kEmpty;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Data Accessors


template< eLod2N LOD, typename Atomic >
inline  const  Atomic&  cOrderedEmptyData< LOD, Atomic >::Get( tIndex iX, tIndex iY, tIndex iZ )  const
{
    return  Atomic( 0 );
}


template< eLod2N LOD, typename Atomic >
inline  void  cOrderedEmptyData< LOD, Atomic >::Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic& iValue )
{
    // Should never be called on Empty Data
    assert( 0 );
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------- Data Transform Analysis


template< eLod2N LOD, typename Atomic >
inline  cDataReportAnalysis< Atomic >  cOrderedEmptyData< LOD, Atomic >::AnteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
{
    if( LOD > ROMSConfig().MicroscopicLODGranularity() )
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kProcess,
                                     eType::kOrdered, eSubType::kEmpty,
                                     eType::kSparse, eSubType::kNone );
    else if( LOD == ROMSConfig().MicroscopicLODGranularity() )
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kProcess,
                                     eType::kOrdered, eSubType::kEmpty,
                                     eType::kEntropic, eSubType::kRaw );
    else
        assert( false ); // Crash
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

