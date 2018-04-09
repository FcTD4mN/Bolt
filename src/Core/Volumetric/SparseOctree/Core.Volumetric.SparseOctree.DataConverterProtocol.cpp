#include "Core.Volumetric.SparseOctree.DataConverterProtocol.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


#define KEY_EXISTS( iMap, iKey )            ( ! ( iMap.find( iKey ) == iMap.end() ) )


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


cDataConverterProtocol::~cDataConverterProtocol()
{
}


cDataConverterProtocol::cDataConverterProtocol() :
    mProcessMap()
{
    mProcessMap[ eType::kEmpty ]    = &cDataConverterProtocol::ConvertToEmpty;
    mProcessMap[ eType::kFull ]     = &cDataConverterProtocol::ConvertToFull;
    mProcessMap[ eType::kSparse ]   = &cDataConverterProtocol::ConvertToSparse;
    mProcessMap[ eType::kRaw ]      = &cDataConverterProtocol::ConvertToRaw;
    mProcessMap[ eType::kRLE ]      = &cDataConverterProtocol::ConvertToRLE;
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------- Conversion Protocol Selection


void  cDataConverterProtocol::ProcessDataReportAnalysis( const  cDataReportAnalysis&  iDataReportAnalysis )
{
    if( iDataReportAnalysis.mConversionOperationStatus == cDataReportAnalysis::eConversionOperationStatus::kNotRequired )
        return;

    auto type = iDataReportAnalysis.mToType;
    if( KEY_EXISTS( mProcessMap, type ) )
            ( this->*( mProcessMap[ type ] ) )( iDataReportAnalysis );
    else
        assert( false );
}


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

