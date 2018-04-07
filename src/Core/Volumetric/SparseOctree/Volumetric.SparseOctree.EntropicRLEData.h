#pragma once


#include "Volumetric.SparseOctree.EntropicData.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cEntropicRLEData final :
    public  cEntropicData< LOD, Atomic >
{

public:
    // Construction / Destruction
    virtual  ~cEntropicRLEData();
    cEntropicRLEData( const  cROMSConfig*  iROMSConfig );
    cEntropicRLEData( const  cEntropicRLEData& ) = delete;

public:
    // Virtual Runtime Information Overrides
    virtual  bool       Compressed()    const  override;
    virtual  eSubType   SubType()       const  override;

public:
    // Data Accessors
    virtual  const  Atomic&  Get( tIndex iX, tIndex iY, tIndex iZ )  const          override;
    virtual  void  Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )   override;

private:
    // Data Transform Analysis
    virtual  cDataReportAnalysis< Atomic >  AnteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )  override;

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Volumetric.SparseOctree.EntropicRLEData.tImp.hpp"

