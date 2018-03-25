#pragma once


#include "Volumetric/Static/Types.h"


namespace  nVolumetric
{


class  cData
{
public:
    // Construction / Destruction
    cData();
    cData( t2Byte iData );
    cData( tByte iMaterial );

public:
    // Data Manipulation Interface
    tByte   GetMaterialField()                              const;
    bool    HasNeighbour( eNF_Flag  iDataNeighbourFlag)     const;
    bool    IsSolid()                                       const;

    void    SetMaterialField( tByte  iMaterialField );
    void    SetNeighbour( eNF_Flag  iDataNeighbourFlag, bool iValue );

private:
    // Private Manipulation tools
    void            SetNeighbourField( tByte  iNeighbourField );
    tByte           GetNeighbourField()                             const;

private:
    // Private Data Members
    union  uDataField
    {
        uDataField()                    : mData( t2Byte( 0 ) )          {}
        uDataField( t2Byte iData )      : mData( iData )                {}
        uDataField( tByte iMaterial )   : mData( t2Byte( iMaterial ) )  {}

        t2Byte  mData;      // Occupies 2 Bytes
        tByte   mField[2];  // Occupies 2 Bytes
    };                      // The whole union occupies 2 Bytes: First Byte is Material Field, Second Byte is Neighbour Field

    uDataField  mDataField;
};


} // namespace  nVolumetric

