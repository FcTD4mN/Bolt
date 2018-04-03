#include "Volumetric.SparseOctree.SparseData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
inline  cSparseData< LOD, Atomic >::~cSparseData()
{
}


template< eLod2N LOD, typename Atomic >
inline  cSparseData< LOD, Atomic >::cSparseData()
{
}


template< eLod2N LOD, typename Atomic >
inline  bool  cSparseData< LOD, Atomic >::Compressed()  const
{
    return  false;
}


template< eLod2N LOD, typename Atomic >
inline  eType  cSparseData< LOD, Atomic >::Type()  const
{
    return  eType::kSparse;
}


template< eLod2N LOD, typename Atomic >
inline  eSubType  cSparseData< LOD, Atomic >::SubType()  const
{
    return  eSubType::kNone;
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

