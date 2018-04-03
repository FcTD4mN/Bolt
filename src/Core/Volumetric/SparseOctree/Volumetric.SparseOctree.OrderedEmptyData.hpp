#include "Volumetric.SparseOctree.OrderedEmptyData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
inline  cOrderedEmptyData< LOD, Atomic >::~cOrderedEmptyData()
{
}


template< eLod2N LOD, typename Atomic >
inline  cOrderedEmptyData< LOD, Atomic >::cOrderedEmptyData()
{
}


template< eLod2N LOD, typename Atomic >
inline  eSubType  cOrderedEmptyData< LOD, Atomic >::SubType()  const
{
    return  eSubType::kEmpty;
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

