#include "Core.Volumetric.SparseOctree.NodeROMSChunk.h"
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
inline  cSparseData< LOD, Atomic >::cSparseData( cROMSChunk< LOD, Atomic >*  iParent, const  cROMSConfig*  iROMSConfig, eType iDataStartType, const  Atomic& iStartValue ) :
    cData< LOD, Atomic >( iParent, iROMSConfig )
{
    mOct[0] = new  cNodeROMSChunk< LOD, HALVED( LOD ), Atomic >( this, iROMSConfig, iDataStartType, iStartValue );
    mOct[1] = new  cNodeROMSChunk< LOD, HALVED( LOD ), Atomic >( this, iROMSConfig, iDataStartType, iStartValue );
    mOct[2] = new  cNodeROMSChunk< LOD, HALVED( LOD ), Atomic >( this, iROMSConfig, iDataStartType, iStartValue );
    mOct[3] = new  cNodeROMSChunk< LOD, HALVED( LOD ), Atomic >( this, iROMSConfig, iDataStartType, iStartValue );
    mOct[4] = new  cNodeROMSChunk< LOD, HALVED( LOD ), Atomic >( this, iROMSConfig, iDataStartType, iStartValue );
    mOct[5] = new  cNodeROMSChunk< LOD, HALVED( LOD ), Atomic >( this, iROMSConfig, iDataStartType, iStartValue );
    mOct[6] = new  cNodeROMSChunk< LOD, HALVED( LOD ), Atomic >( this, iROMSConfig, iDataStartType, iStartValue );
    mOct[7] = new  cNodeROMSChunk< LOD, HALVED( LOD ), Atomic >( this, iROMSConfig, iDataStartType, iStartValue );
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
inline  const  Atomic*  cSparseData< LOD, Atomic >::Get( tIndex iX, tIndex iY, tIndex iZ )  const
{
    // TEMPORARY:
    return  mOct[0]->Get( iX, iY, iZ );
}


template< eLod2N LOD, typename Atomic >
inline  void  cSparseData< LOD, Atomic >::Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic& iValue )
{
    glm::vec3 key = OctKeyForCoord( iX, iY, iZ );
    glm::vec3 vec = glm::vec3( float( iX ), float( iY ), float( iZ ) );
    glm::vec3 res = vec - ( key * ( cData< LOD, Atomic >::Sizef() / 2.f ) );
    tByte ind = OctIndexForKey( key );
    return  mOct[ind]->Set( tIndex( res.x ), tIndex( res.y ), tIndex( res.z ), iValue );
}


template< eLod2N LOD, typename Atomic >
inline  cDataReportAnalysis  cSparseData< LOD, Atomic >::AnteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
{
    return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                 cDataReportAnalysis::eProcessOperationStatus::kProcess );
}


template< eLod2N LOD, typename Atomic >
inline  cDataReportAnalysis  cSparseData< LOD, Atomic >::PosteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
{
    auto baseType = mOct[0]->Data()->Type();
    bool uniqueType = true;

    for( int i = 0; i < 8; ++i )
    {
        auto type = mOct[i]->Data()->Type();
        if( type != baseType )
        {
            uniqueType = false;
            break;
        }
    }

    if( !uniqueType )
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                        cDataReportAnalysis::eProcessOperationStatus::kProcess );

    if( baseType == eType::kEmpty )
    {
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kRequired,
                                        cDataReportAnalysis::eProcessOperationStatus::kProcess,
                                        eType::kSparse, eType::kEmpty );
    }
    else if( baseType == eType::kFull )
    {
        const  Atomic*  baseVal = mOct[0]->Get( 0, 0, 0 );
        bool uniqueVal = true;

        for( int i = 0; i < 8; ++i )
        {
            const  Atomic*  val = mOct[i]->Get( 0, 0, 0 );
            if( *val != *baseVal )
            {
                uniqueVal = false;
                break;
            }
        }

        if( !uniqueVal )
            return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                        cDataReportAnalysis::eProcessOperationStatus::kProcess );

        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kRequired,
                                        cDataReportAnalysis::eProcessOperationStatus::kProcess,
                                        eType::kSparse, eType::kFull );
    }

    return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                 cDataReportAnalysis::eProcessOperationStatus::kProcess );
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------- VBO Related


template< eLod2N LOD, typename Atomic >
inline  void  cSparseData< LOD, Atomic >::BuildVBODebug()
{
    for( int i=0; i<8; ++i )
        mOct[i]->BuildVBODebug();
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------- Render


template< eLod2N LOD, typename Atomic >
inline  glm::vec3  cSparseData< LOD, Atomic >::OctDebugColor()
{
    return glm::vec3( 0.0f, 0.5f, 1.0f );
}


template< eLod2N LOD, typename Atomic >
inline  void  cSparseData< LOD, Atomic >::RenderOctDebug()
{
    cData< LOD, Atomic >::RenderOctDebug();
    float  hsizef = float( HALVED( LOD ) );

    auto f = [&]( tByte iIndex  ) {
        glPushMatrix();
            auto  pos = OctKeyForIndex( iIndex ) * hsizef;
            glTranslatef( pos.x, pos.y, pos.z );
            mOct[iIndex]->RenderOctDebug();
        glPopMatrix();
    };

    for( int i=0; i<8; ++i )
        f(i);

}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------- Internal Oct Operations


template< eLod2N LOD, typename Atomic >
inline  glm::vec3  cSparseData< LOD, Atomic >::OctKeyForIndex( tByte iIndex )
{
    assert( iIndex >= 0 );
    assert( iIndex < 8 );
    float x = float( iIndex & 0b0001 );
    float y = float( ( iIndex & 0b0010 ) >> 1 );
    float z = float( ( iIndex & 0b0100 ) >> 2 );
    return  glm::vec3( x, y, z );
}


template< eLod2N LOD, typename Atomic >
inline  tByte  cSparseData< LOD, Atomic >::OctIndexForKey( const  glm::vec3&  iKey )
{
    assert( iKey.x == 0.f || iKey.x == 1.f );
    assert( iKey.y == 0.f || iKey.y == 1.f );
    assert( iKey.z == 0.f || iKey.z == 1.f );
    return  tByte( iKey.x ) | ( tByte( iKey.y ) << 1 ) | ( tByte( iKey.z ) << 2 );
}


template< eLod2N LOD, typename Atomic >
inline  glm::vec3  cSparseData< LOD, Atomic >::OctKeyForCoord( tIndex iX, tIndex iY, tIndex iZ )
{
    auto sizef = cData< LOD, Atomic >::Sizef();
    assert( iX >= 0.f && iX < sizef );
    assert( iY >= 0.f && iY < sizef );
    assert( iZ >= 0.f && iZ < sizef );

    //#pragma warning( push )
    //#pragma warning( default : 4723)

    float x = roundf( iX / sizef );
    float y = roundf( iY / sizef );
    float z = roundf( iZ / sizef );

    //#pragma warning( pop )

    assert( x == 0.f || x == 1.f );
    assert( y == 0.f || y == 1.f );
    assert( z == 0.f || z == 1.f );

    return  glm::vec3( x, y, z );
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

