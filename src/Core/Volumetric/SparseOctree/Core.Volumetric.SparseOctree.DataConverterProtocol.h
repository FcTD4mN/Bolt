#pragma once


#include "Core.Volumetric.SparseOctree.Data.h"


#include <map>


namespace  nVolumetric      {
namespace  nSparseOctree    {


class  cDataConverterProtocol
{

protected:
    // Construction / Destruction
    virtual  ~cDataConverterProtocol();
    cDataConverterProtocol();
    cDataConverterProtocol( const  cDataConverterProtocol& ) = delete;

private:
    // Conversion Protocol Functions
    void  ProcessDataReportAnalysis( const  cDataReportAnalysis&  iDataReportAnalysis );

    virtual  void  ConvertToEmpty(  const  cDataReportAnalysis&  iDataReportAnalysis )  = 0;
    virtual  void  ConvertToFull(   const  cDataReportAnalysis&  iDataReportAnalysis )  = 0;
    virtual  void  ConvertToSparse( const  cDataReportAnalysis&  iDataReportAnalysis )  = 0;
    virtual  void  ConvertToRaw(    const  cDataReportAnalysis&  iDataReportAnalysis )  = 0;
    virtual  void  ConvertToRLE(    const  cDataReportAnalysis&  iDataReportAnalysis )  = 0;

private:
    // Data Members
    typedef  void  ( cDataConverterProtocol::*tFctPtr )( const  cDataReportAnalysis& );
    typedef std::map< eType, tFctPtr >  tProcessMap;

    tProcessMap  mProcessMap;

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric

