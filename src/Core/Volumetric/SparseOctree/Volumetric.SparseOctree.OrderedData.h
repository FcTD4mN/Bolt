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
    virtual  bool       Compressed()    const  override;
    virtual  eType      Type()          const  override;
    virtual  eSubType   SubType()       const  = 0;

public:
    // Data Accessors
    virtual  const  Atomic&  Get( tIndex iX, tIndex iY, tIndex iZ )  const          = 0;
    virtual  void  Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )   = 0;

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Volumetric.SparseOctree.OrderedData.hpp"

