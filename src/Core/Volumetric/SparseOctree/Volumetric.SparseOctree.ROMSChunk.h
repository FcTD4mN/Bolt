#pragma once


#include "Volumetric.SparseOctree.Types.h"
#include "Volumetric.SparseOctree.Data.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


// Forward Declaration of cROMSConfig
class  cROMSConfig;


// PreCheckAnalysis Spider Struct
struct  cROMSChunkPreCheckAnalysis
{
    cROMSChunkPreCheckAnalysis( bool         iTransformOperationRequired,
                        eType        iFromType,
                        eSubType     iFromSubType,
                        eType        iToType,
                        eSubType     iToSubType ) :
    mTransformOperationRequired( iTransformOperationRequired ),
    mFromType( iFromType ),
    mFromSubType( iFromSubType ),
    mToType( iToType ),
    mToSubType( iToSubType )
    {
    }

    bool        mTransformOperationRequired;
    eType       mFromType;
    eSubType    mFromSubType;

    eType       mToType;
    eSubType    mToSubType;
};


template< eLod2N LOD, typename Atomic >
class  cROMSChunk
{

public:
    // Construction / Destruction
    ~cROMSChunk();
    cROMSChunk( const  cROMSConfig*  iROMSConfig );
    cROMSChunk( const  cROMSChunk& ) = delete;

public:
    // Data Accessors
    const  Atomic&  Get( tIndex iX, tIndex iY, tIndex iZ )  const;
    void  Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue );

private:
    // Internal Data Transform Operations
    cROMSChunkPreCheckAnalysis  PreCheckOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue );
    void  PostCheckOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue );

private:
    // Internal Data Ordered Transform Scpecific Operations
    cROMSChunkPreCheckAnalysis  PreCheckOrderedOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue );
    cROMSChunkPreCheckAnalysis  PreCheckOrderedEmptyOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue );
    cROMSChunkPreCheckAnalysis  PreCheckOrderedFullOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue );

private:
    // Internal Data Transform Operations
    void  SwitchData( eType  iFromType, eSubType  iFromSubType, eType  iToType, eSubType  iToSubType );

private:
    // Private Member Data
    cData< LOD, Atomic >*  mData; // Owning
    const  cROMSConfig*  mROMSConfig;
};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Volumetric.SparseOctree.ROMSChunk.tImp.hpp"

