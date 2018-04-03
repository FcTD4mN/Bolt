#include "Volumetric.SparseOctree.OrderedData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
inline  bool  cOrderedData< LOD, Atomic >::Compressed()  const
{
    return  true;
}


template< eLod2N LOD, typename Atomic >
inline  eType  cOrderedData< LOD, Atomic >::Type()  const
{
    return  eType::kOrdered;
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

