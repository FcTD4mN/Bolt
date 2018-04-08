#include "Core.Volumetric.SparseOctree.ROMSChunk.h"


#include "Core.Volumetric.SparseOctree.DataIncludes.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction



template<eLod2N LOD,typename Atomic>
inline cROMSChunk<LOD,Atomic>::~cROMSChunk()
{
    delete  mData; // Owning
    mROMSConfig = 0; // Non-Owning
}


template< eLod2N LOD, typename Atomic >
inline  cROMSChunk< LOD, Atomic >::cROMSChunk( const  cROMSConfig*  iROMSConfig ) :
    cDataConverterProtocol< LOD, Atomic >(),
    mROMSConfig( iROMSConfig ) // Non-Owning
{
    assert( mROMSConfig );
    mData = new  cEmptyData< LOD, Atomic >( mROMSConfig ); // Owning
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
    cDataReportAnalysis< Atomic >  analysis = mData->AnteriorReportAnalysisOnSet( iX, iY, iZ, iValue );
    cDataConverterProtocol< LOD, Atomic >::ProcessDataReportAnalysis( analysis );
    mData->Set( iX, iY, iZ, iValue );
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

