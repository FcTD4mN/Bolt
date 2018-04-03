#pragma once


#include "Volumetric.SparseOctree.OrderedData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cOrderedFullData :
    public  cOrderedData< LOD, Atomic >
{

public:
    // Construction / Destruction
    virtual  ~cOrderedFullData();
    cOrderedFullData();
    cOrderedFullData( const  cOrderedFullData& ) = delete;

public:
    // Virtual Runtime Information Overrides
    virtual  eSubType  SubType()  const;

private:
    // Private Member Data
    Atomic  mValue;
};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Volumetric.SparseOctree.OrderedFullData.hpp"

