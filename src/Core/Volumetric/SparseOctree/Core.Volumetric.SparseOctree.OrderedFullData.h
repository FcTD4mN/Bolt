#pragma once


#include "Core.Volumetric.SparseOctree.OrderedData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cOrderedFullData final :
    public  cOrderedData< LOD, Atomic >
{

public:
    // Construction / Destruction
    virtual  ~cOrderedFullData();
    cOrderedFullData( const  cROMSConfig*  iROMSConfig );
    cOrderedFullData( const  cOrderedFullData& ) = delete;

public:
    // Virtual Runtime Information Overrides
    virtual  eSubType  SubType()  const  override;

public:
    // Data Accessors
    virtual  const  Atomic&  Get( tIndex iX, tIndex iY, tIndex iZ )  const          override;
    virtual  void  Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )   override;

private:
    // Data Transform Analysis
    virtual  cDataReportAnalysis< Atomic >  AnteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )  override;

private:
    // Private Member Data
    Atomic  mValue;

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Core.Volumetric.SparseOctree.OrderedFullData.tImp.hpp"

