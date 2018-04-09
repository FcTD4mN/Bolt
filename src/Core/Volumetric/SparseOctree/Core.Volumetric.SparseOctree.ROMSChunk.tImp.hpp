#include "Core.Volumetric.SparseOctree.ROMSChunk.h"


#include "Core.Volumetric.SparseOctree.DataIncludes.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template<eLod2N LOD,typename Atomic>
inline  cROMSChunk<LOD,Atomic>::~cROMSChunk()
{
    delete  mData; // Owning
    mROMSConfig = 0; // Non-Owning
}


template< eLod2N LOD, typename Atomic >
inline  cROMSChunk< LOD, Atomic >::cROMSChunk( const  cROMSConfig*  iROMSConfig, eType iDataStartType, const  Atomic& iStartValue ) :
    cDataConverterProtocol(),
    mROMSConfig( iROMSConfig ) // Non-Owning
{
    assert( mROMSConfig );

    switch( iDataStartType )
    {
        case eType::kEmpty:
            mData = new  cEmptyData< LOD, Atomic >( mROMSConfig );
            break;

        case eType::kFull:
            mData = new  cFullData< LOD, Atomic >( mROMSConfig, iStartValue );
            break;

        case eType::kSparse:
            assert( false );
            break;

        case eType::kRaw:
            mData = new  cFullData< LOD, Atomic >( mROMSConfig, iStartValue );
            break;

        case eType::kRLE:
            assert( false );
            break;

        default:
            assert( false );
            break;
    }
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
    ProcessDataReportAnalysis( analysis );

    if( analysis.mProcessOperationStatus == cDataReportAnalysis::eProcessOperationStatus::kProcess )
        mData->Set( iX, iY, iZ, iValue );
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------- Virtual Conversion Protocol Functions Overrides


template< eLod2N LOD, typename Atomic >
inline  void  cROMSChunk< LOD, Atomic >::ConvertToEmpty( const  cDataReportAnalysis&  iDataReportAnalysis )
{
    delete  mData;
    mData = new  cEmptyData< LOD, Atomic >( mROMSConfig );
}


template< eLod2N LOD, typename Atomic >
inline  void  cROMSChunk< LOD, Atomic >::ConvertToFull( const  cDataReportAnalysis&  iDataReportAnalysis )
{
    auto val = mData->Get( 0, 0, 0 );

    if( val == Atomic( 0 ) )
        assert( false );

    delete  mData;
    mData = new  cFullData< LOD, Atomic >( mROMSConfig, val );
}


template< eLod2N LOD, typename Atomic >
inline  void  cROMSChunk< LOD, Atomic >::ConvertToSparse( const  cDataReportAnalysis&  iDataReportAnalysis )
{
    delete  mData;

    switch( iDataReportAnalysis.mFromType )
    {
        case eType::kEmpty:
        {
            mData = new  cSparseData< LOD, Atomic >( mROMSConfig, eType::kEmpty );
            break;
        }

        case eType::kFull:
        {
            auto val = mData->Get( 0, 0, 0 );

            if( val == Atomic( 0 ) )
                assert( false );
            mData = new  cSparseData< LOD, Atomic >( mROMSConfig, eType::kFull, val );
            break;
        }

        default:
        {
            assert( false );
            break;
        }
    }
}


template< eLod2N LOD, typename Atomic >
inline  void  cROMSChunk< LOD, Atomic >::ConvertToRaw( const  cDataReportAnalysis&  iDataReportAnalysis )
{
    switch( iDataReportAnalysis.mFromType )
    {
        case eType::kEmpty:
        {
            mData = new  cRawData< LOD, Atomic >( mROMSConfig, Atomic( 0 ) );
            break;
        }

        case eType::kFull:
        {
            auto val = mData->Get( 0, 0, 0 );

            if( val == Atomic( 0 ) )
                assert( false );
            mData = new  cRawData< LOD, Atomic >( mROMSConfig, val );
            break;
        }

        default:
        {
            assert( false );
            break;
        }
    }
}


template< eLod2N LOD, typename Atomic >
inline  void  cROMSChunk< LOD, Atomic >::ConvertToRLE( const  cDataReportAnalysis&  iDataReportAnalysis )
{
    assert( false );
}


template< eLod2N LOD, typename Atomic >
inline  void  cROMSChunk< LOD, Atomic >::RenderOctDebug()
{
    mData->RenderOctDebug();
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

