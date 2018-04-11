#pragma once


#include "Core.Volumetric.SparseOctree.Types.h"
#include "Core.Volumetric.SparseOctree.Data.h"
#include "Core.Volumetric.SparseOctree.DataConverterProtocol.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


// Forward Declaration of cROMSConfig
class  cROMSConfig;


template< eLod2N LOD, typename Atomic >
class  cROMSChunk :
    public cDataConverterProtocol
{

public:
    // Construction / Destruction
    virtual  ~cROMSChunk();
    cROMSChunk( const  cROMSConfig*  iROMSConfig, eType iDataStartType = eType::kEmpty, const  Atomic& iStartValue = Atomic( 0 ) );
    cROMSChunk( const  cROMSChunk& ) = delete;

public:
    // Data Accessors
    const  Atomic*  Get( tIndex iX, tIndex iY, tIndex iZ )  const;
    void  Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue );

    cData< LOD, Atomic >*  Data();

private:
    // Virtual Conversion Protocol Functions Overrides
    virtual  void  ConvertToEmpty(  const  cDataReportAnalysis&  iDataReportAnalysis )  override;
    virtual  void  ConvertToFull(   const  cDataReportAnalysis&  iDataReportAnalysis )  override;
    virtual  void  ConvertToSparse( const  cDataReportAnalysis&  iDataReportAnalysis )  override;
    virtual  void  ConvertToRaw(    const  cDataReportAnalysis&  iDataReportAnalysis )  override;
    virtual  void  ConvertToRLE(    const  cDataReportAnalysis&  iDataReportAnalysis )  override;

private:
    // VBO Related
    void  InitVBOCapable();
    void  InvalidVBO();
    void  ProcessInvalidStatus(  const  cDataReportAnalysis&  iDataReportAnalysis );

public:
    // Render
    void  RenderOctDebug();

private:
    // Private Member Data
    cData< LOD, Atomic >*  mData; // Owning
    const  cROMSConfig*  mROMSConfig; // Non-Owning
    const  bool  mVBO_Capable;
    bool  mVBO_Valid;

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Core.Volumetric.SparseOctree.ROMSChunk.tImp.hpp"

