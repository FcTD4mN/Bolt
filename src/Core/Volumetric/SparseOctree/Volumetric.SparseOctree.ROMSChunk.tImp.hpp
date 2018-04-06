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
    PreCheckOnSet( iX, iY, iZ, iValue );
    mData->Set( iX, iY, iZ, iValue );
}


//----------------------------------------------------------------------------------------------
//----------------------------------------------------------- Internal Data Transform Operations


template< eLod2N LOD, typename Atomic >
cROMSChunkPreCheckAnalysis  cROMSChunk< LOD, Atomic >::PreCheckOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
{
    switch( mData->Type() )
    {
        case  eType::kOrdered:
            return  PreCheckOrderedOnSet( iX, iY, iZ, iValue );

        case  eType::kSparse:
        {
            break;
        }

        case  eType::kEntropic:
        {
            break;
        }

        default:
            assert( false ); // Crash
    }
}


template< eLod2N LOD, typename Atomic >
inline  void  cROMSChunk< LOD, Atomic >::PostCheckOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
{
}


//----------------------------------------------------------------------------------------------
//----------------------------------------- Internal Data Ordered Transform Scpecific Operations


template< eLod2N LOD, typename Atomic >
cROMSChunkPreCheckAnalysis  cROMSChunk< LOD, Atomic >::PreCheckOrderedOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
{
    // Shouldn't be called otherwise
    assert( mData->Type() == eType::kOrdered );

    switch( mData->SubType() )
    {
        case  eSubType::kEmpty:
            return  PreCheckOrderedEmptyOnSet( iX, iY, iZ, iValue );

        case  eSubType::kFull:
            return  PreCheckOrderedFullOnSet( iX, iY, iZ, iValue );

        default:
            assert( false ); // Crash
    }
}


template< eLod2N LOD, typename Atomic >
cROMSChunkPreCheckAnalysis  cROMSChunk< LOD, Atomic >::PreCheckOrderedEmptyOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )
{
    // Shouldn't be called otherwise
    assert( mData->Type() == eType::kOrdered );
    assert( mData->SubType() == eSubType::kEmpty );

    if( LOD > mROMSConfig->MicroscopicLODGranularity() )
        return  cPreCheckAnalysis( true, eType::kOrdered, eSubType::kEmpty, eType::kSparse, eSubType::kNone );
    else if( LOD == mROMSConfig->MicroscopicLODGranularity() )
        return  cPreCheckAnalysis( true, eType::kOrdered, eSubType::kEmpty, eType::kEntropic, eSubType::kRaw );
    else
        assert( false ); // Crash
}


template< eLod2N LOD, typename Atomic >
cROMSChunkPreCheckAnalysis  cROMSChunk< LOD, Atomic >::PreCheckOrderedFullOnSet( tIndex iX, tIndex iY, tIndex iZ, const Atomic&  iValue )
{
    assert( mData->Type() == eType::kOrdered );
    assert( mData->SubType() == eSubType::kFull );

    if( LOD > mROMSConfig->MicroscopicLODGranularity() )
        return  cPreCheckAnalysis( true, eType::kOrdered, eSubType::kFull, eType::kSparse, eSubType::kNone );
    else if( LOD == mROMSConfig->MicroscopicLODGranularity() )
        return  cPreCheckAnalysis( true, eType::kOrdered, eSubType::kFull, eType::kEntropic, eSubType::kRaw );
    else
        assert( false ); // Crash
}


//----------------------------------------------------------------------------------------------
//----------------------------------------------------------- Internal Data Transform Operations


template< eLod2N LOD, typename Atomic >
inline  void  cROMSChunk< LOD, Atomic >::SwitchData( eType iFromType, eSubType iFromSubType, eType iToType, eSubType iToSubType )
{
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

