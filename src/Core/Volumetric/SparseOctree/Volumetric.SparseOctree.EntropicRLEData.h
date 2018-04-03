#pragma once


#include "Volumetric.SparseOctree.EntropicData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cEntropicRLEData :
    public  cEntropicData< LOD, Atomic >
{

protected:
    // Construction / Destruction
    virtual  ~cEntropicRLEData();
    cEntropicRLEData();
    cEntropicRLEData( const  cEntropicRLEData& ) = delete;

public:
    // Virtual Runtime Information Overrides
    virtual  bool       Compressed()    const;
    virtual  eSubType   SubType()       const;

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Volumetric.SparseOctree.EntropicRLEData.hpp"

