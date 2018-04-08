#include "Core.Volumetric.SparseOctree.EmptyData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N LOD, typename Atomic >
inline  cEmptyData< LOD, Atomic >::~cEmptyData()
{
}


template< eLod2N LOD, typename Atomic >
inline  cEmptyData< LOD, Atomic >::cEmptyData( const  cROMSConfig*  iROMSConfig ) :
    cOrderedData( iROMSConfig )
{
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------- Virtual Runtime Information Overrides


template< eLod2N LOD, typename Atomic >
inline  bool  cEmptyData< LOD, Atomic >::Compressed()  const
{
    return  true;
}


template< eLod2N LOD, typename Atomic >
inline  eType  cEmptyData< LOD, Atomic >::Type()  const
{
    return  eType::kEmpty;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Data Accessors


template< eLod2N LOD, typename Atomic >
inline  const  Atomic&  cEmptyData< LOD, Atomic >::Get( tIndex iX, tIndex iY, tIndex iZ )  const
{
    return  Atomic( 0 );
}


template< eLod2N LOD, typename Atomic >
inline  void  cEmptyData< LOD, Atomic >::Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic& iValue )
{
    // Should never be called on Empty Data
    assert( 0 );
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------- Data Transform Analysis


template< eLod2N LOD, typename Atomic >
inline  cDataReportAnalysis< Atomic >  cEmptyData< LOD, Atomic >::AnteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
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

