#include "Volumetric.SparseOctree.OrderedFullData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
inline  cOrderedFullData< LOD, Atomic >::~cOrderedFullData()
{
}


template< eLod2N LOD, typename Atomic >
inline  cOrderedFullData< LOD, Atomic >::cOrderedFullData()
{
}


template< eLod2N LOD, typename Atomic >
inline  eSubType  cOrderedFullData< LOD, Atomic >::SubType()  const
{
    return  eSubType::kFull;
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

