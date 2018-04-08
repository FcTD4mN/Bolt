#pragma once


#include "Core.Volumetric.SparseOctree.Data.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cEmptyData final :
    public  cData< LOD, Atomic >
{

public:
    // Construction / Destruction
    virtual  ~cEmptyData();
    cEmptyData( const  cROMSConfig*  iROMSConfig );
    cEmptyData( const  cEmptyData& ) = delete;

public:
    // Virtual Runtime Information Overrides
    virtual  bool   Compressed()    const  override;
    virtual  eType  Type()          const  override;

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


#include "Core.Volumetric.SparseOctree.EmptyData.tImp.hpp"

