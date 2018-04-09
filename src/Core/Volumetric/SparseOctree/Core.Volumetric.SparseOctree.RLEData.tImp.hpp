#include "Core.Volumetric.SparseOctree.RLEData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N LOD, typename Atomic >
inline  cRLEData< LOD, Atomic >::~cRLEData()
{
}


template< eLod2N LOD, typename Atomic >
inline  cRLEData< LOD, Atomic >::cRLEData( const  cROMSConfig*  iROMSConfig ) :
    cData( iROMSConfig )
{
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------- Virtual Runtime Information Overrides


template< eLod2N LOD, typename Atomic >
inline  bool  cRLEData< LOD, Atomic >::Compressed()  const
{
    return  true;
}

template< eLod2N LOD, typename Atomic >
inline  eType  cRLEData< LOD, Atomic >::Type()  const
{
    return  eType::kRLE;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Data Accessors


template< eLod2N LOD, typename Atomic >
inline  const  Atomic*  cRLEData< LOD, Atomic >::Get( tIndex iX, tIndex iY, tIndex iZ )  const
{
    return  NULL;
}


template< eLod2N LOD, typename Atomic >
inline  void  cRLEData< LOD, Atomic >::Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic& iValue )
{
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------- Data Transform Analysis


template< eLod2N LOD, typename Atomic >
inline  cDataReportAnalysis  cRLEData< LOD, Atomic >::AnteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
{
    if( iValue == Get( iX, iY ,iZ ) )
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kDiscard );
    else
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kProcess,
                                     eType::kRLE, eType::kRaw );
}


template< eLod2N LOD, typename Atomic >
inline  glm::vec3  cRLEData< LOD, Atomic >::OctDebugColor()
{
    return glm::vec3( 0.0f, 1.0f, 1.0f );
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

