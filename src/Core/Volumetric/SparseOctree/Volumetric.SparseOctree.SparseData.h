#pragma once


#include "Volumetric.SparseOctree.Data.h"


#define  HALVED( i )  static_cast< eLod2N >( tSize( i ) / 2 )


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cROMSChunk;


template< eLod2N LOD, typename Atomic >
class  cSparseData final :
    public  cData< LOD, Atomic >
{

public:
    // Construction / Destruction
    virtual  ~cSparseData();
    cSparseData( const  cROMSConfig*  iROMSConfig );
    cSparseData( const  cSparseData& ) = delete;

public:
    // Virtual Runtime Information Overrides
    virtual  bool       Compressed()    const  override;
    virtual  eType      Type()          const  override;
    virtual  eSubType   SubType()       const  override;

public:
    // Data Accessors
    virtual  const  Atomic&  Get( tIndex iX, tIndex iY, tIndex iZ )  const          override;
    virtual  void  Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )   override;

private:
    // Private Member Data
    cROMSChunk< HALVED( LOD ), Atomic >*  mOct[8];

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#undef  HALVED


#include "Volumetric.SparseOctree.SparseData.hpp"

