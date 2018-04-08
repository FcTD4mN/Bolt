#pragma once


#include "Core.Volumetric.SparseOctree.Data.h"


#include <map>


namespace  nVolumetric      {
namespace  nSparseOctree    {


template< eLod2N LOD, typename Atomic >
class  cDataConverterProtocol
{

protected:
    // Construction / Destruction
    virtual  ~cDataConverterProtocol();
    cDataConverterProtocol();
    cDataConverterProtocol( const  cDataConverterProtocol& ) = delete;

protected:
    // Conversion Protocol Functions
    void  ProcessDataReportAnalysis( const  cDataReportAnalysis< Atomic >&  iDataReportAnalysis, cData< LOD, Atomic >** iData );

    void  ConvertToEmpty( const  cDataReportAnalysis< Atomic >&  iDataReportAnalysis, cData< LOD, Atomic >** iData );
    void  ConvertToFull( const  cDataReportAnalysis< Atomic >&  iDataReportAnalysis, cData< LOD, Atomic >** iData );
    void  ConvertToSparse( const  cDataReportAnalysis< Atomic >&  iDataReportAnalysis, cData< LOD, Atomic >** iData );
    void  ConvertToRaw( const  cDataReportAnalysis< Atomic >&  iDataReportAnalysis, cData< LOD, Atomic >** iData );
    void  ConvertToRLE( const  cDataReportAnalysis< Atomic >&  iDataReportAnalysis, cData< LOD, Atomic >** iData );

private:
    // Data Members
    typedef  void  ( cDataConverterProtocol::*tVoidMemberFunctionPointer )();
    typedef std::map< eSubType, tVoidMemberFunctionPointer >  tProcessMap;

    std::map< eType, tProcessMap* >  mTypeSelectMap;
    tProcessMap  mOrderedProcessMap;
    tProcessMap  mSparseProcessMap;
    tProcessMap  mEntropicProcessMap;
};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Core.Volumetric.SparseOctree.DataConverterProtocol.tImp.hpp"

