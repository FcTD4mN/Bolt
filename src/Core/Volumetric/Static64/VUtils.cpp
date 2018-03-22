#pragma once

#include "Volumetric/Static64/VUtils.h"

namespace  nVolumetric
{

void
GenFace( eNF_Index iFace, int factor, int factor2, float* iData, int iX, int iY, int iZ )
{
    int index = iX + iY * factor + iZ * factor2;
    float x = float( iX );
    float y = float( iY );
    float z = float( iZ );

    switch( iFace )
    {
    case kIndexTop:
        GenTopFace( iData, index, x, y, z );
        break;
    case kIndexBot:
        GenBotFace( iData, index, x, y, z );
        break;
    case kIndexFront:
        GenFrontFace( iData, index, x, y, z );
        break;
    case kIndexBack:
        GenBackFace( iData, index, x, y, z );
        break;
    case kIndexLeft:
        GenLeftFace( iData, index, x, y, z );
        break;
    case kIndexRight:
        GenRightFace( iData, index, x, y, z );
        break;
    }
}


void
GenTopFace(float* iData,int iIndex,float iX,float iY,float iZ)
{
    iData[ ++iIndex ]       = iX;
    iData[ ++iIndex ]       = iY;
    iData[ ++iIndex ]       = iZ;

    iData[ ++iIndex ]       = iX;
    iData[ ++iIndex ]       = iY;
    iData[ ++iIndex ]       = iZ;

    iData[ ++iIndex ]       = iX;
    iData[ ++iIndex ]       = iY;
    iData[ ++iIndex ]       = iZ;

    iData[ ++iIndex ]       = iX;
    iData[ ++iIndex ]       = iY;
    iData[ ++iIndex ]       = iZ;

    iData[ ++iIndex ]       = iX;
    iData[ ++iIndex ]       = iY;
    iData[ ++iIndex ]       = iZ;

    iData[ ++iIndex ]       = iX;
    iData[ ++iIndex ]       = iY;
    iData[ ++iIndex ]       = iZ;
}


void
GenBotFace(float* iData,int iIndex,float iX,float iY,float iZ)
{
}


void
GenFrontFace(float* iData,int iIndex,float iX,float iY,float iZ)
{
}


void
GenBackFace(float* iData,int iIndex,float iX,float iY,float iZ)
{
}


void
GenLeftFace(float* iData,int iIndex,float iX,float iY,float iZ)
{
}


void
GenRightFace(float* iData,int iIndex,float iX,float iY,float iZ)
{
}


} // namespace  nVolumetric

