#include "Core.Volumetric.SparseOctree.RawData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N LOD, typename Atomic >
inline  cRawData< LOD, Atomic >::~cRawData()
{
}


template< eLod2N LOD, typename Atomic >
inline  cRawData< LOD, Atomic >::cRawData( const  cROMSConfig*  iROMSConfig ) :
    cEntropicData( iROMSConfig )
{
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------- Virtual Runtime Information Overrides


template< eLod2N LOD, typename Atomic >
inline  bool  cRawData< LOD, Atomic >::Compressed()  const
{
    return  false;
}


template< eLod2N LOD, typename Atomic >
inline  eType  cRawData< LOD, Atomic >::Type()  const
{
    return  eType::kRaw;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Data Accessors


template< eLod2N LOD, typename Atomic >
inline  const  Atomic&  cRawData< LOD, Atomic >::Get( tIndex iX, tIndex iY, tIndex iZ )  const
{
    mStorage.Get( iX, iY, iZ );
}


template< eLod2N LOD, typename Atomic >
inline  void  cRawData< LOD, Atomic >::Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic& iValue )
{
    mStorage.Set( iX, iY, iZ, iValue );
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------- Data Transform Analysis


template< eLod2N LOD, typename Atomic >
inline  cDataReportAnalysis  cRawData< LOD, Atomic >::AnteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
{
    if( iValue == Get( iX, iY ,iZ ) )
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kDiscard );
    else
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kProcess );

}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

