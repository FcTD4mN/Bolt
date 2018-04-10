#include "Core.Volumetric.SparseOctree.FullData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N LOD, typename Atomic >
inline  cFullData< LOD, Atomic >::~cFullData()
{
    mValue = Atomic( 0 );
}


template< eLod2N LOD, typename Atomic >
inline  cFullData< LOD, Atomic >::cFullData( cROMSChunk< LOD, Atomic >*  iParent, const  cROMSConfig*  iROMSConfig, const  Atomic& iValue ) :
    cData< LOD, Atomic >( iParent, iROMSConfig ),
    mValue( iValue )
{
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------- Virtual Runtime Information Overrides


template< eLod2N LOD, typename Atomic >
inline  bool  cFullData< LOD, Atomic >::Compressed()  const
{
    return  true;
}


template< eLod2N LOD, typename Atomic >
inline  eType  cFullData< LOD, Atomic >::Type()  const
{
    return  eType::kFull;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Data Accessors


template< eLod2N LOD, typename Atomic >
inline  const  Atomic*  cFullData< LOD, Atomic >::Get( tIndex iX, tIndex iY, tIndex iZ )  const
{
    // The same everywhere
    return  &mValue;
}


template< eLod2N LOD, typename Atomic >
inline  void  cFullData< LOD, Atomic >::Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic& iValue )
{
    // Should never be called on Full Data
    assert( 0 );
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------- Data Transform Analysis


template< eLod2N LOD, typename Atomic >
inline  cDataReportAnalysis  cFullData< LOD, Atomic >::AnteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
{
    if( iValue == *Get( iX, iY ,iZ ) )
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                       cDataReportAnalysis::eProcessOperationStatus::kDiscard );

    if( LOD > cData< LOD, Atomic >::ROMSConfig().MicroscopicLODGranularity() )
    {
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kProcess,
                                     eType::kFull, eType::kSparse );
    }
    else if( LOD == cData< LOD, Atomic >::ROMSConfig().MicroscopicLODGranularity() )
    {
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kProcess,
                                     eType::kFull, eType::kRaw );
    }
    else
    {
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kDiscard );
        assert( false ); // Crash
    }
}


template< eLod2N LOD, typename Atomic >
inline  cDataReportAnalysis  cFullData< LOD, Atomic >::PosteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
{
    return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                 cDataReportAnalysis::eProcessOperationStatus::kProcess );
}


template< eLod2N LOD, typename Atomic >
inline  glm::vec3  cFullData< LOD, Atomic >::OctDebugColor()
{
    return glm::vec3( 1.0f, 0.5f, 0.0f );
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

