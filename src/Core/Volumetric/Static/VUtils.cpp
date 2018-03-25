#pragma once

#include "Volumetric/Static/VUtils.h"

namespace  nVolumetric
{

void
GenFace( eNF_Index iFace, int iIndex, std::vector< sf::Vector3f >& iData, int iX, int iY, int iZ )
{
    float x = float( iX );
    float y = float( iY );
    float z = float( iZ );

    switch( iFace )
    {
    case kIndexTop:
        GenTopFace( iData, iIndex, x, y, z );
        break;
    case kIndexBot:
        GenBotFace( iData, iIndex, x, y, z );
        break;
    case kIndexFront:
        GenFrontFace( iData, iIndex, x, y, z );
        break;
    case kIndexBack:
        GenBackFace( iData, iIndex, x, y, z );
        break;
    case kIndexLeft:
        GenLeftFace( iData, iIndex, x, y, z );
        break;
    case kIndexRight:
        GenRightFace( iData, iIndex, x, y, z );
        break;
    }
}


void
GenTopFace( std::vector< sf::Vector3f >& iData,int iIndex,float iX,float iY,float iZ)
{
    iData[ iIndex++ ]   = sf::Vector3f( iX,         iY,         iZ          );
    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f,   iY,         iZ          );
    iData[ iIndex++ ]   = sf::Vector3f( iX,         iY,         iZ - 1.f    );

    iData[ iIndex++ ]   = sf::Vector3f( iX,         iY,         iZ - 1.f    );
    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f,   iY,         iZ          );
    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f,   iY,         iZ - 1.f    );
}


void
GenBotFace( std::vector< sf::Vector3f >& iData,int iIndex,float iX,float iY,float iZ)
{
    iData[ iIndex++ ]   = sf::Vector3f( iX,         iY - 1.f,   iZ          );
    iData[ iIndex++ ]   = sf::Vector3f( iX,         iY - 1.f,   iZ - 1.f    );
    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f,   iY - 1.f,   iZ          );

    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f,   iY - 1.f,   iZ          );
    iData[ iIndex++ ]   = sf::Vector3f( iX,         iY - 1.f,   iZ - 1.f    );
    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f,   iY - 1.f,   iZ - 1.f    );
}


void
GenFrontFace( std::vector< sf::Vector3f >& iData,int iIndex,float iX,float iY,float iZ)
{
    iData[ iIndex++ ]   = sf::Vector3f( iX,         iY,         iZ          );
    iData[ iIndex++ ]   = sf::Vector3f( iX,         iY - 1.f,   iZ          );
    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f,   iY,         iZ          );

    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f,   iY,         iZ          );
    iData[ iIndex++ ]   = sf::Vector3f( iX,         iY - 1.f,   iZ          );
    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f,   iY - 1.f,   iZ          );
}


void
GenBackFace( std::vector< sf::Vector3f >& iData,int iIndex,float iX,float iY,float iZ)
{
    iData[ iIndex++ ]   = sf::Vector3f( iX,         iY,         iZ - 1.f    );
    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f,   iY,         iZ - 1.f    );
    iData[ iIndex++ ]   = sf::Vector3f( iX,         iY - 1.f,   iZ - 1.f    );

    iData[ iIndex++ ]   = sf::Vector3f( iX,         iY - 1.f,   iZ - 1.f    );
    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f,   iY,         iZ - 1.f    );
    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f,   iY - 1.f,   iZ - 1.f    );
}


void
GenLeftFace( std::vector< sf::Vector3f >& iData,int iIndex,float iX,float iY,float iZ)
{
    iData[ iIndex++ ]   = sf::Vector3f( iX,         iY,         iZ          );
    iData[ iIndex++ ]   = sf::Vector3f( iX,         iY,         iZ - 1.f    );
    iData[ iIndex++ ]   = sf::Vector3f( iX,         iY - 1.f,   iZ          );

    iData[ iIndex++ ]   = sf::Vector3f( iX,         iY - 1.f,   iZ          );
    iData[ iIndex++ ]   = sf::Vector3f( iX,         iY,         iZ - 1.f    );
    iData[ iIndex++ ]   = sf::Vector3f( iX,         iY - 1.f,   iZ - 1.f    );
}


void
GenRightFace( std::vector< sf::Vector3f >& iData,int iIndex,float iX,float iY,float iZ)
{
    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f,   iY,         iZ          );
    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f,   iY - 1.f,   iZ          );
    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f,   iY,         iZ - 1.f    );

    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f,   iY,         iZ - 1.f    );
    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f,   iY - 1.f,   iZ          );
    iData[ iIndex++ ]   = sf::Vector3f( iX + 1.f,   iY - 1.f,   iZ - 1.f    );
}


sf::Vector3f
ColorFromVGAMaterial( tByte iMaterial )
{
    float r = float( ( iMaterial & 0b11100000 ) >> 5 ) / 3.f;
    float g = float( ( iMaterial & 0b00011100 ) >> 2 ) / 7.f;
    float b = float( ( iMaterial & 0b00000011 ) ) / 7.f;
    return  sf::Vector3f( r, g, b );
}


} // namespace  nVolumetric

