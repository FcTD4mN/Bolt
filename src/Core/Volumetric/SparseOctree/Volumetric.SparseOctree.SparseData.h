#pragma once


#include "Volumetric.SparseOctree.Data.h"


#define  HALVED( i )  static_cast< eLod2N >( tSize( i ) / 2 )


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cROMSChunk;


template< eLod2N LOD, typename Atomic >
class  cSparseData :
    public  cData< LOD, Atomic >
{

protected:
    // Construction / Destruction
    virtual  ~cSparseData();
    cSparseData();
    cSparseData( const  cSparseData& ) = delete;

public:
    // Virtual Runtime Information Overrides
    virtual  bool       Compressed()    const;
    virtual  eType      Type()          const;
    virtual  eSubType   SubType()       const;

private:
    // Private Member Data
    cROMSChunk< HALVED( LOD ), Atomic >*  mOct[8];

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#undef  HALVED


#include "Volumetric.SparseOctree.SparseData.hpp"

