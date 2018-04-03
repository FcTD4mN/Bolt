#include "Volumetric.SparseOctree.EntropicRLEData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
inline  cEntropicRLEData< LOD, Atomic >::~cEntropicRLEData()
{
}


template< eLod2N LOD, typename Atomic >
inline  cEntropicRLEData< LOD, Atomic >::cEntropicRLEData()
{
}


template< eLod2N LOD, typename Atomic >
inline  bool  cEntropicRLEData< LOD, Atomic >::Compressed()  const
{
    return  true;
}

template< eLod2N LOD, typename Atomic >
inline  eSubType  cEntropicRLEData< LOD, Atomic >::SubType()  const
{
    return  eSubType::kRLE;
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

