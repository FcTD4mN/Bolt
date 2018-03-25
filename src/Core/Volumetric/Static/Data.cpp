#include "Volumetric/Static/Data.h"


namespace  nVolumetric
{

//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


cData::cData() :
    mDataField()
{
}


cData::cData( t2Byte iData ) :
    mDataField( iData )
{
}


cData::cData( tByte iMaterial ) :
    mDataField( iMaterial )
{
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------ Data Manipulation Interface


tByte
cData::GetMaterialField()  const
{
    return  mDataField.mField[0];
}


bool
cData::HasNeighbour( eNF_Flag  iDataNeighbourFlag)  const
{
    return  bool( GetNeighbourField() & tByte( iDataNeighbourFlag ) );
}


bool
cData::IsSolid()  const
{
    return  GetMaterialField() != sgEmptyMaterial;
}


void
cData::SetMaterialField( tByte  iMaterialField )
{
    mDataField.mField[0] = iMaterialField;
}


void
cData::SetNeighbour( eNF_Flag  iDataNeighbourFlag, bool iValue )
{
    if( iValue )
        SetNeighbourField( GetNeighbourField() | iDataNeighbourFlag );
    else
        SetNeighbourField( GetNeighbourField() & ~iDataNeighbourFlag );
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Private Manipulation tools


void
cData::SetNeighbourField( tByte  iNeighbourField )
{
    mDataField.mField[1] = iNeighbourField;
}


tByte
cData::GetNeighbourField()  const
{
    return  mDataField.mField[1];
}


} // namespace  nVolumetric

