#include "Core.Volumetric.SparseOctree.ROMSChunk.h"


#include "Core.Volumetric.SparseOctree.DataIncludes.h"


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
inline  cROMSChunk< LOD, Atomic >::cROMSChunk( const  cROMSConfig*  iROMSConfig, eType iDataStartType, const  Atomic& iStartValue ) :
    cDataConverterProtocol(),
    mROMSConfig( iROMSConfig ), // Non-Owning
    mVBO_Capable( false ),
    mVBO_Valid( false )
{
    assert( mROMSConfig );
    InitVBOCapable();

    switch( iDataStartType )
    {
        case eType::kEmpty:
            mData = new  cEmptyData< LOD, Atomic >( this, mROMSConfig );
            break;

        case eType::kFull:
            mData = new  cFullData< LOD, Atomic >( this, mROMSConfig, iStartValue );
            break;

        case eType::kSparse:
            assert( false );
            break;

        case eType::kRaw:
            mData = new  cFullData< LOD, Atomic >( this, mROMSConfig, iStartValue );
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
inline  const  Atomic*
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
    ProcessInvalidStatus( analysis );

    if( analysis.mProcessOperationStatus == cDataReportAnalysis::eProcessOperationStatus::kProcess )
        mData->Set( iX, iY, iZ, iValue );

    analysis = mData->PosteriorReportAnalysisOnSet( iX, iY, iZ, iValue );
    ProcessDataReportAnalysis( analysis );
    ProcessInvalidStatus( analysis );
}


template< eLod2N LOD, typename Atomic >
inline  cData< LOD, Atomic >*  cROMSChunk< LOD, Atomic >::Data()
{
    return  mData;
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------- Virtual Conversion Protocol Functions Overrides


template< eLod2N LOD, typename Atomic >
inline  void  cROMSChunk< LOD, Atomic >::ConvertToEmpty( const  cDataReportAnalysis&  iDataReportAnalysis )
{
    delete  mData;
    mData = new  cEmptyData< LOD, Atomic >( this, mROMSConfig );
}


template< eLod2N LOD, typename Atomic >
inline  void  cROMSChunk< LOD, Atomic >::ConvertToFull( const  cDataReportAnalysis&  iDataReportAnalysis )
{
    auto val = *mData->Get( 0, 0, 0 );

    if( val == Atomic( 0 ) )
        assert( false );

    delete  mData;
    mData = new  cFullData< LOD, Atomic >( this, mROMSConfig, val );
}


template< eLod2N LOD, typename Atomic >
inline  void  cROMSChunk< LOD, Atomic >::ConvertToSparse( const  cDataReportAnalysis&  iDataReportAnalysis )
{

    switch( iDataReportAnalysis.mFromType )
    {
        case eType::kEmpty:
        {
            delete  mData;
            mData = new  cSparseData< LOD, Atomic >( this, mROMSConfig, eType::kEmpty );
            break;
        }

        case eType::kFull:
        {
            auto val = *mData->Get( 0, 0, 0 );

            if( val == Atomic( 0 ) )
                assert( false );

            delete  mData;
            mData = new  cSparseData< LOD, Atomic >( this, mROMSConfig, eType::kFull, val );
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
            mData = new  cRawData< LOD, Atomic >( this, mROMSConfig, Atomic( 0 ) );
            break;
        }

        case eType::kFull:
        {
            auto val = *mData->Get( 0, 0, 0 );
            if( val == Atomic( 0 ) )
                assert( false );
            mData = new  cRawData< LOD, Atomic >( this, mROMSConfig, val );
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


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- VBO Related


template<eLod2N LOD,typename Atomic>
inline void cROMSChunk<LOD,Atomic>::InitVBOCapable()
{
    if( LOD == mROMSConfig->VBOLODGranularity() )
    {
        bool* ptr = const_cast< bool* >( &mVBO_Capable );
        *ptr = true;
    }
}


template<eLod2N LOD,typename Atomic>
inline void cROMSChunk<LOD,Atomic>::InvalidVBO()
{
    mVBO_Valid = false;
}


template< eLod2N LOD, typename Atomic >
inline  void  cROMSChunk< LOD, Atomic >::ProcessInvalidStatus( const  cDataReportAnalysis&  iDataReportAnalysis )
{
    if( !mVBO_Capable )
        return;

    if( iDataReportAnalysis.mConversionOperationStatus == cDataReportAnalysis::eConversionOperationStatus::kRequired ||
        iDataReportAnalysis.mProcessOperationStatus == cDataReportAnalysis::eProcessOperationStatus::kProcess )
        InvalidVBO();
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------- Render


template< eLod2N LOD, typename Atomic >
inline  void  cROMSChunk< LOD, Atomic >::RenderOctDebug()
{
    mData->RenderOctDebug();
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

