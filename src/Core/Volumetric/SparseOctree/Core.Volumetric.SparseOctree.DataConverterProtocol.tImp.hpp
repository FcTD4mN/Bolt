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
    mTypeSelectMap[ eType::kOrdered ]   = &mOrderedProcessMap;
    mTypeSelectMap[ eType::kSparse ]    = &mSparseProcessMap;
    mTypeSelectMap[ eType::kEntropic ]  = &mEntropicProcessMap;

    mOrderedProcessMap[ eSubType::kEmpty ]  = &cDataConverterProtocol< LOD, Atomic >::ConvertToEmpty;
    mOrderedProcessMap[ eSubType::kFull ]   = &cDataConverterProtocol< LOD, Atomic >::ConvertToFull;
    mSparseProcessMap[ eSubType::kNone ]    = &cDataConverterProtocol< LOD, Atomic >::ConvertToSparse;
    mEntropicProcessMap[ eSubType::kRaw ]   = &cDataConverterProtocol< LOD, Atomic >::ConvertToRaw;
    mEntropicProcessMap[ eSubType::kRLE ]   = &cDataConverterProtocol< LOD, Atomic >::ConvertToRLE;
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------- Conversion Protocol Functions


template< eLod2N LOD, typename Atomic >
inline  void  cDataConverterProtocol< LOD, Atomic >::ProcessDataReportAnalysis( const  cDataReportAnalysis< Atomic >&  iDataReportAnalysis, cData< LOD, Atomic >**  iData )
{
    auto type = iDataReportAnalysis.mToType;
    auto subtype = iDataReportAnalysis.mToSubType;
    if( KEY_EXISTS( mTypeSelectMap, type ) )
    {
        if( KEY_EXISTS( ( *mTypeSelectMap[ type ] ), subtype ) )
        {
            (this->*( *mTypeSelectMap[ type ] )[ subtype ])();
        }
        else
        {
            assert( false );
        }
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

