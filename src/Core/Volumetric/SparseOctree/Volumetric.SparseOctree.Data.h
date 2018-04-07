#pragma once


#include "Volumetric.SparseOctree.Types.h"


namespace  nVolumetric      {
namespace  nSparseOctree    {


// Forward Declaration of cROMSConfig
class  cROMSConfig;


// Runtime Information Enums
enum  eType
{
    kOrdered,
    kSparse,
    kEntropic
};


enum  eSubType
{
    kEmpty,
    kFull,

    kNone,

    kRaw,
    kRLE
};


// PreCheckAnalysis Spider Struct
template< typename Atomic >
struct  cDataReportAnalysis
{
    enum  eConversionOperationStatus
    {
        kRequired,
        kNotRequired,
    };

    enum  eProcessOperationStatus
    {
        kProcess,
        kDiscard,
    };

    cDataReportAnalysis( eConversionOperationStatus iConversionOperationStatus,
                         eProcessOperationStatus    iProcessOperationStatus,
                         eType       iFromType,
                         eSubType    iFromSubType,
                         eType       iToType,
                         eSubType    iToSubType,
                         Atomic      iValue ) :
    mConversionOperationStatus( iConversionOperationStatus ),
    mProcessOperationStatus( iProcessOperationStatus ),
    mFromType( iFromType ),
    mFromSubType( iFromSubType ),
    mToType( iToType ),
    mToSubType( iToSubType ),
    mValue( iValue )
    {
    }

    cDataReportAnalysis( eConversionOperationStatus iConversionOperationStatus,
                         eProcessOperationStatus    iProcessOperationStatus ) :
    mConversionOperationStatus( iConversionOperationStatus ),
    mProcessOperationStatus( iProcessOperationStatus ),
    mFromType( eType() ),
    mFromSubType( eSubType() ),
    mToType( eType() ),
    mToSubType( eSubType() ),
    mValue( Atomic( 0 ) )
    {
    }

    eConversionOperationStatus  mConversionOperationStatus;
    eProcessOperationStatus     mProcessOperationStatus;
    eType       mFromType;
    eSubType    mFromSubType;

    eType       mToType;
    eSubType    mToSubType;

    Atomic      mValue;
};


template< eLod2N LOD, typename Atomic >
class  cData
{

public:
    // Construction / Destruction
    virtual  ~cData();
    cData( const  cROMSConfig*  iROMSConfig );
    cData( const  cData& ) = delete;

public:
    // Pure Virtual Runtime Information
    virtual  bool       Compressed()    const  = 0;
    virtual  eType      Type()          const  = 0;
    virtual  eSubType   SubType()       const  = 0;

public:
    // Template Data Container Accessors
    eLod2N  LOD()       const;
    tSize   Size()      const;
    tVolume Capacity()  const;

    const  cROMSConfig&  ROMSConfig()  const;

public:
    // Data Accessors
    virtual  const  Atomic&  Get( tIndex iX, tIndex iY, tIndex iZ )  const          = 0;
    virtual  void  Set( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )   = 0;

private:
    // Data Transform Analysis
    virtual  cDataReportAnalysis< Atomic >  AnteriorReportAnalysisOnSet( tIndex iX, tIndex iY, tIndex iZ, const  Atomic&  iValue )  = 0;

private:
    // Private Member Data
    const  tVolume  mCapacity  =  LOD * LOD * LOD;
    const  cROMSConfig*  mROMSConfig; // Non-Owning

};


}  // namespace  nSparseOctree
}  // namespace  nVolumetric


#include "Volumetric.SparseOctree.Data.tImp.hpp"

