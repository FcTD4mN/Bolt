#include "Volumetric.SparseOctree.ROMSChunk.h"


#include "Volumetric.SparseOctree.DataIncludes.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N LOD, typename Atomic >
inline  cROMSChunk< LOD, Atomic >::~cROMSChunk()
{
    delete  mData; // Owning
    mROMSConfig = 0; // Non-Owning
}


template< eLod2N LOD, typename Atomic >
inline  cROMSChunk< LOD, Atomic >::cROMSChunk( const  cROMSConfig*  iROMSConfig ) :
    mROMSConfig( iROMSConfig ) // Non-Owning
{
    assert( mROMSConfig );
    mData = new  cOrderedEmptyData< LOD, Atomic >( mROMSConfig ); / Owning
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------- Data Accessors


template< eLod2N LOD, typename Atomic >
inline  const  Atomic&
cROMSChunk<LOD,Atomic>::Get(tIndex iX,tIndex iY,tIndex iZ)  const
{
    return  mData->Get( iX, iY, iZ );
}


template< eLod2N LOD, typename Atomic >
inline  void
cROMSChunk<LOD,Atomic>::Set(tIndex iX,tIndex iY,tIndex iZ,const Atomic & iValue)
{
    cDataReportAnalysis  analysis = mData->AnteriorReportAnalysisOnSet( iX, iY, iZ, iValue );
    eTransformOperationStatus
    AnteriorDataTransformFromReport( analysis );
    mData->Set( iX, iY, iZ, iValue );
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------- Data Sensitive Operation


template< eLod2N LOD, typename Atomic >
inline  void  cROMSChunk< LOD, Atomic >::AnteriorDataTransformFromReport( const  cDataReportAnalysis&  iDataReportAnalysis )
{
    if( iDataReportAnalysis.mTransformOperationStatus == cDataReportAnalysis::eTransformOperationStatus::kNotRequired )
        return;
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

