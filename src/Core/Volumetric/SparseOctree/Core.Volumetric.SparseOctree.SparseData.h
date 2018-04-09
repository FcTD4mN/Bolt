#pragma once


#include "Core.Volumetric.SparseOctree.Data.h"


#define  HALVED( i )  static_cast< eLod2N >( tSize( i ) / 2 )


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cROMSChunk;


template< eLod2N LOD, typename Atomic >
class  cSparseData final :
    public  cData< LOD, Atomic >
{

public:
    // Construction / Destruction
    virtual  ~cSparseData();
    cSparseData( const  cROMSConfig*  iROMSConfig, eType iDataStartType = eType::kEmpty, const  Atomic& iStartValue = Atomic( 0 ) );
    cSparseData( const  cSparseData& ) = delete;

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
    virtual  void  RenderOctDebug()  override;

private:
    // Private Member Data
    cROMSChunk< HALVED( LOD ), Atomic >*  mOct[8];

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#undef  HALVED


#include "Core.Volumetric.SparseOctree.SparseData.tImp.hpp"

