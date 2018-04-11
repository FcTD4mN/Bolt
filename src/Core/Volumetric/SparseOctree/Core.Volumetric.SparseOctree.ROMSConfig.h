#pragma once


#include "Core.Volumetric.SparseOctree.Types.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


class  cROMSConfig final
{

public:
    // Construction / Destruction
    virtual  ~cROMSConfig();
    cROMSConfig(  const  eLod2N&  iMacroscopicLODGranularity,
                  const  eLod2N&  iVBO_LODGranularity,
                  const  eLod2N&  iMicroscopicLODGranularity,
                  const  tLargeByteSize&  iGPU_BUS_MAX );

public:
    // Accessors
    const  eLod2N&  MacroscopicLODGranularity()  const;
    const  eLod2N&  VBOLODGranularity()  const;
    const  eLod2N&  MicroscopicLODGranularity()  const;
    const  tLargeByteSize&  GPU_BUS_MAX()  const;

    void  MacroscopicLODGranularity( const  eLod2N&  iMacroscopicLODGranularity );
    void  MicroscopicLODGranularity( const  eLod2N&  iMacroscopicLODGranularity );
    void  GPU_BUS_MAX( const  tLargeByteSize&  iGPU_BUS_MAX );

private:
    // Private Member Data
    eLod2N  mMacroscopicLODGranularity;
    eLod2N  mVBO_LODGranularity;
    eLod2N  mMicroscopicLODGranularity;
    tLargeByteSize  mGPU_BUS_MAX;

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

