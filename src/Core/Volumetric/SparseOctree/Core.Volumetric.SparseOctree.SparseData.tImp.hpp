#include "Core.Volumetric.SparseOctree.SparseData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


#define  HALVED( i )  static_cast< eLod2N >( tSize( i ) / 2 )


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N LOD, typename Atomic >
inline  cSparseData< LOD, Atomic >::~cSparseData()
{
    delete  mOct[0];
    delete  mOct[1];
    delete  mOct[2];
    delete  mOct[3];
    delete  mOct[4];
    delete  mOct[5];
    delete  mOct[6];
    delete  mOct[7];
}


template< eLod2N LOD, typename Atomic >
inline  cSparseData< LOD, Atomic >::cSparseData( const  cROMSConfig*  iROMSConfig, eType iDataStartType, const  Atomic& iStartValue ) :
    cData< LOD, Atomic >( iROMSConfig )
{
    mOct[0] = new  cROMSChunk< HALVED( LOD ), Atomic >( iROMSConfig, iDataStartType, iStartValue );
    mOct[1] = new  cROMSChunk< HALVED( LOD ), Atomic >( iROMSConfig, iDataStartType, iStartValue );
    mOct[2] = new  cROMSChunk< HALVED( LOD ), Atomic >( iROMSConfig, iDataStartType, iStartValue );
    mOct[3] = new  cROMSChunk< HALVED( LOD ), Atomic >( iROMSConfig, iDataStartType, iStartValue );
    mOct[4] = new  cROMSChunk< HALVED( LOD ), Atomic >( iROMSConfig, iDataStartType, iStartValue );
    mOct[5] = new  cROMSChunk< HALVED( LOD ), Atomic >( iROMSConfig, iDataStartType, iStartValue );
    mOct[6] = new  cROMSChunk< HALVED( LOD ), Atomic >( iROMSConfig, iDataStartType, iStartValue );
    mOct[7] = new  cROMSChunk< HALVED( LOD ), Atomic >( iROMSConfig, iDataStartType, iStartValue );
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------- Virtual Runtime Information Overrides


template< eLod2N LOD, typename Atomic >
inline  bool  cSparseData< LOD, Atomic >::Compressed()  const
{
    return  false;
}


template< eLod2N LOD, typename Atomic >
inline  eType  cSparseData< LOD, Atomic >::Type()  const
{
    return  eType::kSparse;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Data Accessors


template< eLod2N LOD, typename Atomic >
inline  const  Atomic&  cSparseData< LOD, Atomic >::Get( tIndex iX, tIndex iY, tIndex iZ )  const
{
    // TODO: insert return statement here
    // TEMPORARY:
    return  mOct[0]->Get( iX, iY, iZ );
}


template< eLod2N LOD, typename Atomic >
inline  void  cSparseData< LOD, Atomic >::Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic& iValue )
{
    return  mOct[0]->Set( iX, iY, iZ, iValue );
}


template< eLod2N LOD, typename Atomic >
inline  cDataReportAnalysis  cSparseData< LOD, Atomic >::AnteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
{
    return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                 cDataReportAnalysis::eProcessOperationStatus::kProcess );
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

