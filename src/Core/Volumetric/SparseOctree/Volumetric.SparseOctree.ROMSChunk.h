#pragma once


#include "Volumetric.SparseOctree.Types.h"
#include "Volumetric.SparseOctree.Data.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


// Forward Declaration of cROMSConfig
class  cROMSConfig;


template< eLod2N LOD, typename Atomic >
class  cROMSChunk
{

public:
    // Construction / Destruction
    ~cROMSChunk();
    cROMSChunk( const  cROMSConfig*  iROMSConfig );
    cROMSChunk( const  cROMSChunk& ) = delete;

public:
    // Data Accessors
    const  Atomic&  Get( tIndex iX, tIndex iY, tIndex iZ )  const;
    void  Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue );

public:
    // Data Sensitive Operation

    // Base
    void  ProcessAnteriorDataTransformFromReportFrom( const  cDataReportAnalysis&  iDataReportAnalysis );

    // Tier
    void  ProcessAnteriorDataTransformFromReportFromOrdered( const  cDataReportAnalysis&  iDataReportAnalysis );
    void  ProcessAnteriorDataTransformFromReportFromEntropic( const  cDataReportAnalysis&  iDataReportAnalysis );

    //Final
    void  ProcessAnteriorDataTransformFromReportFromOrderedEmpty( const  cDataReportAnalysis&  iDataReportAnalysis );
    void  ProcessAnteriorDataTransformFromReportFromOrderedFull( const  cDataReportAnalysis&  iDataReportAnalysis );
    void  ProcessAnteriorDataTransformFromReportFromEntropicSparse( const  cDataReportAnalysis&  iDataReportAnalysis );
    void  ProcessAnteriorDataTransformFromReportFromEntropicRaw( const  cDataReportAnalysis&  iDataReportAnalysis );
    void  ProcessAnteriorDataTransformFromReportFromEntropicRLE( const  cDataReportAnalysis&  iDataReportAnalysis );


private:
    // Private Member Data
    cData< LOD, Atomic >*  mData; // Owning
    const  cROMSConfig*  mROMSConfig;
};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Volumetric.SparseOctree.ROMSChunk.tImp.hpp"

