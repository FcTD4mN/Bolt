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
    switch( mData->Type() )
    {
        case  eType::kOrdered:
        {
            if( mData->SubType() == eSubType::kEmpty )
            {
                if( LOD == mROMSConfig->MicroscopicLODGranularity() )
                {
                    delete  mData;
                    mData = new  cEntropicRawData< LOD, Atomic >( mROMSConfig );
                    mData->Set( iX, iY, iZ, iValue );
                    break;
                }
                else if( LOD > mROMSConfig->MicroscopicLODGranularity() )
                {
                    delete  mData;
                    mData = new  cSparseData< LOD, Atomic >( mROMSConfig );
                    mData->Set( iX, iY, iZ, iValue );
                    break;
                }
                else
                {
                    // Shouldn't be possible
                    xassert( 0 );
                }
            }

            if( mData->SubType() == eSubType::kFull )
            {
                break;
            }
        }

        case  eType::kSparse:
        {
            break;
        }

        case  eType::kEntropic:
        {
            if( mData->SubType() == eSubType::kRaw )
            {
                break;
            }

            if( mData->SubType() == eSubType::kRLE )
            {
                break;
            }
        }

    }
    mData->Set( iX, iY, iZ, iValue );
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

