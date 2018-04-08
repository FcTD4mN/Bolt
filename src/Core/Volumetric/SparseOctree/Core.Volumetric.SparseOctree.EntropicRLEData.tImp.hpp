#include "Core.Volumetric.SparseOctree.EntropicRLEData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N LOD, typename Atomic >
inline  cEntropicRLEData< LOD, Atomic >::~cEntropicRLEData()
{
}


template< eLod2N LOD, typename Atomic >
inline  cEntropicRLEData< LOD, Atomic >::cEntropicRLEData( const  cROMSConfig*  iROMSConfig ) :
    cEntropicData( iROMSConfig )
{
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------- Virtual Runtime Information Overrides


template< eLod2N LOD, typename Atomic >
inline  bool  cEntropicRLEData< LOD, Atomic >::Compressed()  const
{
    return  true;
}

template< eLod2N LOD, typename Atomic >
inline  eSubType  cEntropicRLEData< LOD, Atomic >::SubType()  const
{
    return  eSubType::kRLE;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Data Accessors


template< eLod2N LOD, typename Atomic >
inline  const  Atomic&  cEntropicRLEData< LOD, Atomic >::Get( tIndex iX, tIndex iY, tIndex iZ )  const
{
    // TODO: insert return statement here
}


template< eLod2N LOD, typename Atomic >
inline  void  cEntropicRLEData< LOD, Atomic >::Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic& iValue )
{
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------- Data Transform Analysis


template< eLod2N LOD, typename Atomic >
inline  cDataReportAnalysis< Atomic >  cEntropicRLEData< LOD, Atomic >::AnteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
{
    if( Get( iX, iY ,iZ ) == iValue )
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kDiscard );
    else
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kProcess,
                                     eType::kEntropic, eSubType::kRLE,
                                     eType::kEntropic, eSubType::kRaw );
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

