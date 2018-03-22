#pragma once

#include "Volumetric/Static64/Types.h"

namespace  nVolumetric
{

inline  static  eNF_Flag    NF_IndexToFlag( eNF_Index iNF_Index )   { return  static_cast< eNF_Flag >( int( pow( int( iNF_Index ), 2 ) ) ); }
inline  static  eNF_Index   NF_FlagToIndex( eNF_Flag iNF_Flag )     { return  static_cast< eNF_Index >( int( log2( long double( iNF_Flag ) ) ) ); }

void  GenFace( eNF_Index iFace, int factor, int factor2, float* iData, int iX, int iY, int iZ );
void  GenTopFace(   float* iData ,  int iIndex, float iX, float iY, float iZ );
void  GenBotFace(   float* iData ,  int iIndex, float iX, float iY, float iZ );
void  GenFrontFace( float* iData ,  int iIndex, float iX, float iY, float iZ );
void  GenBackFace(  float* iData ,  int iIndex, float iX, float iY, float iZ );
void  GenLeftFace(  float* iData ,  int iIndex, float iX, float iY, float iZ );
void  GenRightFace( float* iData ,  int iIndex, float iX, float iY, float iZ );

} // namespace  nVolumetric

