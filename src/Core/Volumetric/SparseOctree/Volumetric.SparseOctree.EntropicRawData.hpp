#include "Volumetric.SparseOctree.EntropicRawData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
inline  cEntropicRawData< LOD, Atomic >::~cEntropicRawData()
{
}


template< eLod2N LOD, typename Atomic >
inline  cEntropicRawData< LOD, Atomic >::cEntropicRawData()
{
}

template< eLod2N LOD, typename Atomic >
inline  bool  cEntropicRawData< LOD, Atomic >::Compressed()  const
{
    return  false;
}


template< eLod2N LOD, typename Atomic >
inline  eSubType  cEntropicRawData< LOD, Atomic >::SubType()  const
{
    return  eSubType::kRaw;
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

