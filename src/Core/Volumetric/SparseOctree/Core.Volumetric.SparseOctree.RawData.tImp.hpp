#include "Core.Volumetric.SparseOctree.RawData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N LOD, typename Atomic >
inline  cRawData< LOD, Atomic >::~cRawData()
{
    for( int i = 0; i < LOD; ++i )
    {
        for( int j = 0; j < LOD; ++j )
        {
            delete  mCore[i][j];
        }
        delete  mCore[i];
    }
    delete  mCore;
}


template< eLod2N LOD, typename Atomic >
inline  cRawData< LOD, Atomic >::cRawData( const  cROMSConfig*  iROMSConfig, const  Atomic& iFillValue ) :
    cData< LOD, Atomic >( iROMSConfig ),
    mOccupiedVolume( 0 )
{
    mCore = new  Atomic**[ LOD ];
    for( int i = 0; i < LOD; ++i )
    {
        mCore[i] = new Atomic*[ LOD ];
        for( int j = 0; j < LOD; ++j )
        {
            mCore[i][j] = new Atomic[ LOD ];
            for( int k = 0; k < LOD; ++k )
            {
                mCore[i][j][k] = iFillValue;
            }
        }
    }

    if( iFillValue > Atomic( 0 ) )
        mOccupiedVolume = cData< LOD, Atomic >::Capacity();
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
inline  const  Atomic*  cRawData< LOD, Atomic >::Get( tIndex iX, tIndex iY, tIndex iZ )  const
{
    auto size = tSize( LOD );
    assert( iX >= 0 && iX < size );
    assert( iY >= 0 && iY < size );
    assert( iZ >= 0 && iZ < size );
    return  &mCore[ iX ][ iY ][ iZ ];
}


template< eLod2N LOD, typename Atomic >
inline  void  cRawData< LOD, Atomic >::Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic& iValue )
{
    auto size = tSize( LOD );
    assert( iX >= 0 && iX < size );
    assert( iY >= 0 && iY < size );
    assert( iZ >= 0 && iZ < size );
    mCore[ iX ][ iY ][ iZ ] = iValue;
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------- Data Transform Analysis


template< eLod2N LOD, typename Atomic >
inline  cDataReportAnalysis  cRawData< LOD, Atomic >::AnteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
{
    if( iValue == *Get( iX, iY ,iZ ) )
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kDiscard );
    else
        return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                     cDataReportAnalysis::eProcessOperationStatus::kProcess );
}


template< eLod2N LOD, typename Atomic >
inline  cDataReportAnalysis  cRawData< LOD, Atomic >::PosteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
{
    if( mOccupiedVolume == cData< LOD, Atomic >::Capacity() )
    {
        const  Atomic* baseVal = Get( 0, 0, 0 );
        bool uniqueVal = true;
        for( int i = 0; i < LOD; ++i )
        {
            for( int j = 0; j < LOD; ++j )
            {
                for( int k = 0; k < LOD; ++k )
                {
                    const  Atomic* val = Get( i, j , k );
                    if( *val != *baseVal )
                    {
                        uniqueVal = false;
                        break;
                    }
                }
            }
        }

        if( !uniqueVal )
            return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                         cDataReportAnalysis::eProcessOperationStatus::kProcess );

        if( *baseVal == Atomic( 0 ) )
            return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kRequired,
                                         cDataReportAnalysis::eProcessOperationStatus::kProcess,
                                         eType::kRaw, eType::kEmpty );
        else
            return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kRequired,
                                         cDataReportAnalysis::eProcessOperationStatus::kProcess,
                                         eType::kRaw, eType::kFull );
    }

    return  cDataReportAnalysis( cDataReportAnalysis::eConversionOperationStatus::kNotRequired,
                                 cDataReportAnalysis::eProcessOperationStatus::kDiscard );
}


template< eLod2N LOD, typename Atomic >
inline  glm::vec3  cRawData< LOD, Atomic >::OctDebugColor()
{
    return glm::vec3( 1.0f, 0.0f, 0.0f );
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

