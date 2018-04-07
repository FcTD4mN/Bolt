#include "Volumetric.SparseOctree.USROCMap.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


template< eLod2N LOD, typename Atomic >
inline  cDataConverterProtocol< LOD, Atomic >::~cDataConverterProtocol()
{
}


template< eLod2N LOD, typename Atomic >
inline  cDataConverterProtocol< LOD, Atomic >::cDataConverterProtocol() :
    mTypeSelectMap(),
    mOrderedProcessMap(),
    mSparseProcessMap(),
    mEntropicProcessMap()
{
    mTypeSelectMap[ eType::kOrdered ]   = &mOrderedProcessMap;
    mTypeSelectMap[ eType::kSparse ]    = &mSparseProcessMap;
    mTypeSelectMap[ eType::kEntropic ]  = &mEntropicProcessMap;

    mOrderedProcessMap[ eSubType::kEmpty ] = void;
    mOrderedProcessMap[ eSubType::kFull ] = void;

    mSparseProcessMap[ eSubType::kNone ] = void;

    mEntropicProcessMap[ eSubType::kRaw ] = void;
    mEntropicProcessMap[ eSubType::kRLE ] = void;
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------- Conversion Protocol Functions


template< eLod2N LOD, typename Atomic >
inline  void  cDataConverterProtocol< LOD, Atomic >::ProcessDataReportAnalysis( const  cDataReportAnalysis< Atomic >&  iDataReportAnalysis, cData< LOD, Atomic >**  iData )
{
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

