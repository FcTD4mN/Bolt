#pragma once


#include "Core.Volumetric.SparseOctree.Types.h"
#include "Core.Volumetric.SparseOctree.Data.h"
#include "Core.Volumetric.SparseOctree.DataConverterProtocol.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


// Forward Declaration of cROMSConfig
class  cROMSConfig;


template< eLod2N LOD, typename Atomic >
class  cROMSChunk final :
    private cDataConverterProtocol< LOD, Atomic >
{

public:
    // Construction / Destruction
    virtual  ~cROMSChunk();
    cROMSChunk( const  cROMSConfig*  iROMSConfig );
    cROMSChunk( const  cROMSChunk& ) = delete;

public:
    // Data Accessors
    const  Atomic&  Get( tIndex iX, tIndex iY, tIndex iZ )  const;
    void  Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue );

private:
    // Private Member Data
    cData< LOD, Atomic >*  mData; // Owning
    const  cROMSConfig*  mROMSConfig; // Non-Owning

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Core.Volumetric.SparseOctree.ROMSChunk.tImp.hpp"

