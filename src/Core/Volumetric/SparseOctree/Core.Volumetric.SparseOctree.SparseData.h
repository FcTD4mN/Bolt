#pragma once


#include "Core.Volumetric.SparseOctree.Data.h"


#include <glm/vec3.hpp>


#define  HALVED( i )  static_cast< eLod2N >( tSize( i ) / 2 )


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N ParentLOD, eLod2N LOD, typename Atomic >
class  cNodeROMSChunk;


template< eLod2N LOD, typename Atomic >
class  cSparseData final :
    public  cData< LOD, Atomic >
{

public:
    // Construction / Destruction
    virtual  ~cSparseData();
    cSparseData( cROMSChunk< LOD, Atomic >*  iParent, const  cROMSConfig*  iROMSConfig, eType iDataStartType = eType::kEmpty, const  Atomic& iStartValue = Atomic( 0 ) );
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
    virtual  cDataReportAnalysis  PosteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )  override;

public:
    // VBO Related
    void  BuildVBODebug();

public:
    virtual  glm::vec3  OctDebugColor()  override;
    virtual  void  RenderOctDebug()  override;

private:
    // Internal Oct Operations
    // 000 0
    // 001 1
    // 010 2
    // 011 3
    // 100 4
    // 101 5
    // 110 6
    // 111 7
    glm::vec3  OctKeyForIndex( tByte  iIndex );
    tByte OctIndexForKey( const  glm::vec3&  iKey );
    glm::vec3  OctKeyForCoord( tIndex iX, tIndex iY, tIndex iZ );



private:
    // Private Member Data
    cNodeROMSChunk< LOD, HALVED( LOD ), Atomic >*  mOct[8];

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#undef  HALVED


#include "Core.Volumetric.SparseOctree.SparseData.tImp.hpp"

