#pragma once


#include "Volumetric.SparseOctree.OrderedData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cOrderedEmptyData :
    public  cOrderedData< LOD, Atomic >
{

public:
    // Construction / Destruction
    virtual  ~cOrderedEmptyData();
    cOrderedEmptyData();
    cOrderedEmptyData( const  cOrderedEmptyData& ) = delete;

public:
    // Virtual Runtime Information Overrides
    virtual  eSubType  SubType()  const;

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Volumetric.SparseOctree.OrderedEmptyData.hpp"

