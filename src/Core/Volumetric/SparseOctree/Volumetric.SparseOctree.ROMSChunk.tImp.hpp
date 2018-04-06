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
    mData = new  cOrderedEmptyData< LOD, Atomic >( mROMSConfig ); // Owning
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
    ProcessAnteriorDataTransformFromReportFrom( analysis );
    mData->Set( iX, iY, iZ, iValue );
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------- Data Sensitive Operation


// Base
template< eLod2N LOD, typename Atomic >
inline  void  cROMSChunk< LOD, Atomic >::ProcessAnteriorDataTransformFromReportFrom( const  cDataReportAnalysis&  iDataReportAnalysis )
{
    if( iDataReportAnalysis.mTransformOperationStatus == cDataReportAnalysis::eTransformOperationStatus::kNotRequired )
        return;

    switch( iDataReportAnalysis.mFromType )
    {
        case  eType::kOrdered:
        {
            ProcessAnteriorDataTransformFromReportFromOrdered();
            break;
        }

        case  eType::kSparse:
        {
            ProcessAnteriorDataTransformFromReportFromSparse();
            break;
        }

        case  eType::kEntropic:
        {
            ProcessAnteriorDataTransformFromReportFromEntropic();
            break;
        }

        default:
        {
            assert( false ); // Crash;
        }
    }
}


// Tier
template< eLod2N LOD, typename Atomic >
inline  void  cROMSChunk< LOD, Atomic >::ProcessAnteriorDataTransformFromReportFromOrdered( const  cDataReportAnalysis&  iDataReportAnalysis )
{
    switch( iDataReportAnalysis.mFromSubType )
    {
        case  eSubType::kEmpty:
        {
            ProcessAnteriorDataTransformFromReportFromOrderedEmpty();
            break;
        }

        case  eSubType::kFull:
        {
            ProcessAnteriorDataTransformFromReportFromOrderedFull();
            break;
        }
        default:
        {
            assert( false ); // Crash;
        }
    }
}


template< eLod2N LOD, typename Atomic >
inline  void  cROMSChunk< LOD, Atomic >::ProcessAnteriorDataTransformFromReportFromEntropic( const  cDataReportAnalysis&  iDataReportAnalysis )
{
    switch( iDataReportAnalysis.mFromSubType )
    {
        case  eSubType::kRaw:
        {
            ProcessAnteriorDataTransformFromReportFromEntropicRaw();
            break;
        }

        case  eSubType::kRLE:
        {
            ProcessAnteriorDataTransformFromReportFromEntropicRLE();
            break;
        }
        default:
        {
            assert( false ); // Crash;
        }
    }
}


// Final
template< eLod2N LOD, typename Atomic >
inline  void  cROMSChunk< LOD, Atomic >::ProcessAnteriorDataTransformFromReportFromOrderedEmpty( const  cDataReportAnalysis&  iDataReportAnalysis )
{
    switch( iDataReportAnalysis.mToType )
    {
        case  eType::kOrdered:
        {
            break;
        }

        case  eType::kSparse:
        {
            break;
        }

        case  eType::kEntropic:
        {
            break;
        }

        default:
        {
            assert( false ); // Crash;
        }
    }
}


template< eLod2N LOD, typename Atomic >
inline  void  cROMSChunk< LOD, Atomic >::ProcessAnteriorDataTransformFromReportFromOrderedFull( const  cDataReportAnalysis&  iDataReportAnalysis )
{
    switch( iDataReportAnalysis.mToType )
    {
        case  eType::kOrdered:
        {
            break;
        }

        case  eType::kSparse:
        {
            break;
        }

        case  eType::kEntropic:
        {
            break;
        }

        default:
        {
            assert( false ); // Crash;
        }
    }
}


template< eLod2N LOD, typename  Atomic >
inline  void  cROMSChunk< LOD, Atomic >::ProcessAnteriorDataTransformFromReportFromEntropicSparse( const  cDataReportAnalysis&  iDataReportAnalysis )
{
    switch( iDataReportAnalysis.mToType )
    {
        case  eType::kOrdered:
        {
            break;
        }

        case  eType::kSparse:
        {
            break;
        }

        case  eType::kEntropic:
        {
            break;
        }

        default:
        {
            assert( false ); // Crash;
        }
    }
}


template< eLod2N LOD, typename Atomic >
inline  void  cROMSChunk< LOD, Atomic >::ProcessAnteriorDataTransformFromReportFromEntropicRaw( const  cDataReportAnalysis&  iDataReportAnalysis )
{
    switch( iDataReportAnalysis.mToType )
    {
        case  eType::kOrdered:
        {
            break;
        }

        case  eType::kSparse:
        {
            break;
        }

        case  eType::kEntropic:
        {
            break;
        }

        default:
        {
            assert( false ); // Crash;
        }
    }
}


template< eLod2N LOD, typename Atomic >
inline  void  cROMSChunk< LOD, Atomic >::ProcessAnteriorDataTransformFromReportFromEntropicRLE( const  cDataReportAnalysis&  iDataReportAnalysis )
{
    switch( iDataReportAnalysis.mToType )
    {
        case  eType::kOrdered:
        {
            break;
        }

        case  eType::kSparse:
        {
            break;
        }

        case  eType::kEntropic:
        {
            break;
        }

        default:
        {
            assert( false ); // Crash;
        }
    }
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

