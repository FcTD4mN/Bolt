#include "Volumetric.SparseOctree.ROMSConfig.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


cROMSConfig::~cROMSConfig()
{
}


cROMSConfig::cROMSConfig()
{
}


cROMSConfig::cROMSConfig( const  eLod2N&  iMacroscopicLODGranularity,
                          const  eLod2N&  iMicroscopicLODGranularity,
                          const  tLargeByteSize&  iGPU_BUS_MAX ) :
    mMacroscopicLODGranularity( iMacroscopicLODGranularity ),
    mMicroscopicLODGranularity( iMicroscopicLODGranularity ),
    mGPU_BUS_MAX( iGPU_BUS_MAX )
{
}


const  eLod2N&
cROMSConfig::MacroscopicLODGranularity()  const
{
    return  mMacroscopicLODGranularity;
}

const  eLod2N&
cROMSConfig::MicroscopicLODGranularity()  const
{
    return  mMicroscopicLODGranularity;
}


const  tLargeByteSize&
cROMSConfig::GPU_BUS_MAX()  const
{
    return  mGPU_BUS_MAX;
}


void
cROMSConfig::MacroscopicLODGranularity(const eLod2N & iMacroscopicLODGranularity)
{
    mMacroscopicLODGranularity = iMacroscopicLODGranularity;
}


void
cROMSConfig::MicroscopicLODGranularity(const eLod2N & iMacroscopicLODGranularity)
{
    mMicroscopicLODGranularity = iMacroscopicLODGranularity;
}


void
cROMSConfig::GPU_BUS_MAX(const tLargeByteSize & iGPU_BUS_MAX)
{
    mGPU_BUS_MAX = iGPU_BUS_MAX;
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

