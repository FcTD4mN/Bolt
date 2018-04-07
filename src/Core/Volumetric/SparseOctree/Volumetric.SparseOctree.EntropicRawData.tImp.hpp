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
    mStorage.Get( iX, iY, iZ );
}


template< eLod2N LOD, typename Atomic >
inline  void  cEntropicRawData< LOD, Atomic >::Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic& iValue )
{
    mStorage.Set( iX, iY, iZ, iValue );
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------- Data Transform Analysis


template< eLod2N LOD, typename Atomic >
inline  cDataReportAnalysis< Atomic >  cEntropicRawData< LOD, Atomic >::AnteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
{
    if( Get( iX, iY ,iZ ) == iValue )
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kDiscard );
    else
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kProcess );

}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

