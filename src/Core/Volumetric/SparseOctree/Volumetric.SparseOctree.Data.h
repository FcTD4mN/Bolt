#pragma once


#include "Volumetric.SparseOctree.Types.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cData
{

protected:
    // Construction / Destruction
    virtual  ~cData() = 0;
    cData( const  cData& ) = delete;

public:
    // Pure Virtual Runtime Information
    virtual  bool       Compressed()    const  = 0;
    virtual  eType      Type()          const  = 0;
    virtual  eSubType   SubType()       const  = 0;

public:
    // Template Accessors
    eLod2N  LOD()       const;
    tSize   Size()      const;
    tVolume Capacity()  const;

private:
    // Private Member Data
    const  tVolume  mCapacity  =  LOD * LOD * LOD;

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Volumetric.SparseOctree.Data.hpp"

