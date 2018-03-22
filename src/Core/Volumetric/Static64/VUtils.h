#pragma once

#include "SFML/Graphics.hpp"
#include "Volumetric/Static64/Types.h"

namespace  nVolumetric
{

inline  static  eNF_Flag    NF_IndexToFlag( eNF_Index iNF_Index )   { return  static_cast< eNF_Flag >( int( pow( int( iNF_Index ), 2 ) ) ); }
inline  static  eNF_Index   NF_FlagToIndex( eNF_Flag iNF_Flag )     { return  static_cast< eNF_Index >( int( log2( long double( iNF_Flag ) ) ) ); }

void  GenFace( eNF_Index iFace, int iIndex, std::vector< sf::Vector3f >& iData, int iX, int iY, int iZ );
void  GenTopFace(   std::vector< sf::Vector3f >& iData ,  int iIndex, float iX, float iY, float iZ );
void  GenBotFace(   std::vector< sf::Vector3f >& iData ,  int iIndex, float iX, float iY, float iZ );
void  GenFrontFace( std::vector< sf::Vector3f >& iData ,  int iIndex, float iX, float iY, float iZ );
void  GenBackFace(  std::vector< sf::Vector3f >& iData ,  int iIndex, float iX, float iY, float iZ );
void  GenLeftFace(  std::vector< sf::Vector3f >& iData ,  int iIndex, float iX, float iY, float iZ );
void  GenRightFace( std::vector< sf::Vector3f >& iData ,  int iIndex, float iX, float iY, float iZ );

} // namespace  nVolumetric

