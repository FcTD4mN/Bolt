#pragma once


#include "Volumetric.SparseOctree.OrderedData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cOrderedFullData final :
    public  cOrderedData< LOD, Atomic >
{

public:
    // Construction / Destruction
    virtual  ~cOrderedFullData();
    cOrderedFullData();
    cOrderedFullData( const  cOrderedFullData& ) = delete;

public:
    // Virtual Runtime Information Overrides
    virtual  eSubType  SubType()  const  override;

public:
    // Data Accessors
    virtual  const  Atomic&  Get( tIndex iX, tIndex iY, tIndex iZ )  const          override;
    virtual  void  Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )   override;

private:
    // Private Member Data
    Atomic  mValue;
};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Volumetric.SparseOctree.OrderedFullData.hpp"

