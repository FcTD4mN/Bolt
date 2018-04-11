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
    mVBO_Valid( false ),
    mVBO_ID( 0 )
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
        glGenBuffers( 1, &mVBO_ID );
        glBindBuffer( GL_ARRAY_BUFFER, mVBO_ID );
        glBufferData( GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW );
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
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


template< eLod2N LOD, typename Atomic >
inline  void  cROMSChunk< LOD, Atomic >::BuildVBODebug()
{
    if( !mVBO_Capable )
    {
        if( mData->Type() == eType::kSparse )
        {
            cSparseData< LOD, Atomic >* sparseData = dynamic_cast< cSparseData< LOD, Atomic >* >( mData );
            assert( sparseData );
            sparseData->BuildVBODebug();
        }

        return;
    }

    if( !mVBO_Valid )
        return;

    if(glIsBuffer( mVBO_ID ) == GL_TRUE)
        glDeleteBuffers( 1, &mVBO_ID );

    glGenBuffers( 1, &mVBO_ID );

/*
    int index = 0;
    std::vector< sf::Vector3f > vertices;
    vertices.resize( mNVerticesVBOElem );
    int memsize = msElementSize * mNVerticesVBOElem;

    int colorstride = 6;
    mNColorsVBOElem = OccupiedVolume() * colorstride;
    int colorindex = 0;
    std::vector< sf::Vector3f > colors;
    colors.resize( mNColorsVBOElem );
    int memcolorsize = msElementSize * mNColorsVBOElem;

    eNF_Flag neighbourFlag = NF_IndexToFlag( iVBO_ID_index );

    for( tLocalDataIndex  i = 0; i < msSize; ++i )
    {
        for( tLocalDataIndex  j = 0; j < msSize; ++j )
        {
            for( tLocalDataIndex  k = 0; k < msSize; ++k )
            {
                cData* data = DataHandle( i, j, k );
                if( data->IsSolid() && !data->HasNeighbour( neighbourFlag ) )
                {
                    GenFace( iVBO_ID_index, index, vertices, i, j, k );
                    sf::Vector3f color = ColorFromVGAMaterial( data->GetMaterialField() );
                    colors[index + 0] = color;
                    colors[index + 1] = color;
                    colors[index + 2] = color;
                    colors[index + 3] = color;
                    colors[index + 4] = color;
                    colors[index + 5] = color;
                    index += stride;
                    colorindex += colorstride;
                }
            }
        }
    }

    glBindBuffer( GL_ARRAY_BUFFER, mVBO_ID[ iVBO_ID_index ] );

        glBufferData( GL_ARRAY_BUFFER, memsize + memcolorsize, 0, GL_STATIC_DRAW );
        glBufferSubData( GL_ARRAY_BUFFER, 0, memsize, &vertices[0] );
        glBufferSubData( GL_ARRAY_BUFFER, memsize, memcolorsize, &colors[0] );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    mVerticesMsize = memsize;
*/
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

