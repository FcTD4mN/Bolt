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
    cData< LOD, Atomic >( iROMSConfig )
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
inline  const  Atomic*  cEmptyData< LOD, Atomic >::Get( tIndex iX, tIndex iY, tIndex iZ )  const
{
    return  NULL;
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
inline  cDataReportAnalysis  cEmptyData< LOD, Atomic >::AnteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
{
    if( iValue == Atomic( 0 ) )
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kDiscard );

    if( LOD > cData< LOD, Atomic >::ROMSConfig().MicroscopicLODGranularity() )
    {
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kProcess,
                                     eType::kEmpty, eType::kSparse );
    }
    else if( LOD == cData< LOD, Atomic >::ROMSConfig().MicroscopicLODGranularity() )
    {
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kProcess,
                                     eType::kEmpty, eType::kRaw );
    }
    else
    {
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kDiscard );
        assert( false ); // Crash
    }
}


template< eLod2N LOD, typename Atomic >
inline  cDataReportAnalysis  cEmptyData< LOD, Atomic >::PosteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
{
    return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                 cDataReportAnalysis::eProcessOperationStatus::kProcess );
}


template< eLod2N LOD, typename Atomic >
inline  glm::vec3  cEmptyData< LOD, Atomic >::OctDebugColor()
{
    return glm::vec3( 1.0f, 1.0f, 0.0f );
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

