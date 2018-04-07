#pragma once


#include <map>


#include "Volumetric.SparseOctree.Data.h"


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


#include "Volumetric.SparseOctree.DataConverterProtocol.tImp.hpp"

