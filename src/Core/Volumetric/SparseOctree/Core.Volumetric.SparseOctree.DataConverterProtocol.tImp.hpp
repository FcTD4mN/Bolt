#include "Core.Volumetric.SparseOctree.USROCMap.h"
#include "Core.Volumetric.SparseOctree.DataConverterProtocol.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


#define KEY_EXISTS( iMap, iKey )            ( ! ( iMap.find( iKey ) == iMap.end() ) )


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

    mProcessMap[ eType::kEmpty ]    = &cDataConverterProtocol< LOD, Atomic >::ConvertToEmpty;
    mProcessMap[ eType::kFull ]     = &cDataConverterProtocol< LOD, Atomic >::ConvertToFull;
    mProcessMap[ eType::kSparse ]   = &cDataConverterProtocol< LOD, Atomic >::ConvertToSparse;
    mProcessMap[ eType::kRaw ]      = &cDataConverterProtocol< LOD, Atomic >::ConvertToRaw;
    mProcessMap[ eType::kRLE ]      = &cDataConverterProtocol< LOD, Atomic >::ConvertToRLE;
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------- Conversion Protocol Functions


template< eLod2N LOD, typename Atomic >
inline  void  cDataConverterProtocol< LOD, Atomic >::ProcessDataReportAnalysis( const  cDataReportAnalysis< Atomic >&  iDataReportAnalysis, cData< LOD, Atomic >**  iData )
{
    auto type = iDataReportAnalysis.mToType;
    if( KEY_EXISTS( mTypeSelectMap, type ) )
    {
            (this->*( *mTypeSelectMap[ type ] ))();
    }
    else
    {
        assert( false );
    }
}


template< eLod2N LOD, typename Atomic >
inline  void  cDataConverterProtocol< LOD, Atomic >::ConvertToEmpty( const  cDataReportAnalysis<Atomic>&  iDataReportAnalysis, cData< LOD, Atomic >**  iData )
{
    cData< LOD, Atomic >*  data = *iData;
    delete  data;
}


template<eLod2N LOD,typename Atomic>
inline void cDataConverterProtocol<LOD,Atomic>::ConvertToFull(const cDataReportAnalysis<Atomic>& iDataReportAnalysis,cData<LOD,Atomic>** iData)
{
}


template<eLod2N LOD,typename Atomic>
inline void cDataConverterProtocol<LOD,Atomic>::ConvertToSparse(const cDataReportAnalysis<Atomic>& iDataReportAnalysis,cData<LOD,Atomic>** iData)
{
}


template<eLod2N LOD,typename Atomic>
inline void cDataConverterProtocol<LOD,Atomic>::ConvertToRaw(const cDataReportAnalysis<Atomic>& iDataReportAnalysis,cData<LOD,Atomic>** iData)
{
}


template<eLod2N LOD,typename Atomic>
inline void cDataConverterProtocol<LOD,Atomic>::ConvertToRLE(const cDataReportAnalysis<Atomic>& iDataReportAnalysis,cData<LOD,Atomic>** iData)
{
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

