#pragma once


#include "Volumetric.SparseOctree.Data.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cEntropicData :
    public  cData< LOD, Atomic >
{

protected:
    // Construction / Destruction
    virtual  ~cEntropicData() = 0;
    cEntropicData( const  cEntropicData& ) = delete;

public:
    // Virtual Runtime Information Overrides
    virtual  bool       Compressed()    const  = 0;
    virtual  eType      Type()          const;
    virtual  eSubType   SubType()       const  = 0;

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Volumetric.SparseOctree.EntropicData.hpp"

