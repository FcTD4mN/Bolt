#pragma once


#include "Volumetric.SparseOctree.Data.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cOrderedData :
    public  cData< LOD, Atomic >
{

protected:
    // Construction / Destruction
    virtual  ~cOrderedData() = 0;
    cOrderedData( const  cOrderedData& ) = delete;

public:
    // Virtual Runtime Information Overrides
    virtual  bool       Compressed()    const;
    virtual  eType      Type()          const;
    virtual  eSubType   SubType()       const  = 0;

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Volumetric.SparseOctree.OrderedData.hpp"

