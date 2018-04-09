#pragma once


#include "Core.Volumetric.SparseOctree.Data.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cFullData final :
    public  cData< LOD, Atomic >
{

public:
    // Construction / Destruction
    virtual  ~cFullData();
    cFullData( const  cROMSConfig*  iROMSConfig, const  Atomic& iValue );
    cFullData( const  cFullData& ) = delete;

public:
    // Virtual Runtime Information Overrides
    virtual  bool   Compressed()    const  override;
    virtual  eType  Type()          const  override;

public:
    // Data Accessors
    virtual  const  Atomic*  Get( tIndex iX, tIndex iY, tIndex iZ )  const          override;
    virtual  void  Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )   override;

public:
    // Data Transform Analysis
    virtual  cDataReportAnalysis  AnteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )  override;

public:
    virtual  glm::vec3  OctDebugColor()  override;

private:
    // Private Member Data
    Atomic  mValue;

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Core.Volumetric.SparseOctree.FullData.tImp.hpp"

