#pragma once


#include "Volumetric.SparseOctree.EntropicData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cEntropicRLEData :
    public  cEntropicData< LOD, Atomic >
{

public:
    // Construction / Destruction
    virtual  ~cEntropicRLEData() = 0; // TODO: Remove pure virtual when implemented
    cEntropicRLEData();
    cEntropicRLEData( const  cEntropicRLEData& ) = delete;

public:
    // Virtual Runtime Information Overrides
    virtual  bool       Compressed()    const;
    virtual  eSubType   SubType()       const;

private:
    // Private Member Data
    // Not Implemented yet

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Volumetric.SparseOctree.EntropicRLEData.hpp"

