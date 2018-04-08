#pragma once


#include "Core.Volumetric.SparseOctree.EntropicData.h"
#include "Core.Volumetric.SparseOctree.RawStorage.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cEntropicRawData final :
    public  cEntropicData< LOD, Atomic >
{

public:
    // Construction / Destruction
    virtual  ~cEntropicRawData();
    cEntropicRawData( const  cROMSConfig*  iROMSConfig );
    cEntropicRawData( const  cEntropicRawData& ) = delete;

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

private:
    // Private Member Data
    cRawStorage< LOD, Atomic >  mStorage;
};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Core.Volumetric.SparseOctree.EntropicRawData.tImp.hpp"

