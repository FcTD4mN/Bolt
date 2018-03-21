#pragma once

#include "Volumetric/Static64/Types.h"
#include "Volumetric/Static64/Data.h"


#include <GL/glew.h>
#include <gl/GLU.h>
#include "SFML/OpenGL.hpp"


namespace  nVolumetric
{


class  cStaticLodChunk64
{

public:
enum  eFaceIndex : tByte
{
    kTop    = 0,
    kBot    = 1,
    kFront  = 2,
    kBack   = 3,
    kLeft   = 4,
    kRight  = 5,
};

public:
    // Construction / Destruction
    cStaticLodChunk64();
    cStaticLodChunk64( tByte iVal );
    cStaticLodChunk64( const  cStaticLodChunk64& ) = delete;

public:
    // Volume Information
    tByte           Size()              const;
    unsigned  int   Capacity()          const;
    unsigned  int   OccupiedVolume()    const;
    bool            IsFull()            const;
    bool            IsEmpty()           const;

public:
    // Volume Manipulation
    void  Fill( tByte iVal );

public:
    // Material Accessors
    bool    IsSolid( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )       const;
    tByte   GetMaterial( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )   const;
    void    SetMaterial( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ, tByte iValue );

public:
    // Neighbour Accessors
    cStaticLodChunk64*  GetNeighbour( eFaceIndex  iNeighbourIndex )  const;
    void                SetNeighbour( eFaceIndex  iNeighbourIndex, cStaticLodChunk64* iAdress );

private:
    // Data Manipulation
    cData*          DataHandle( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ );
    void            UpdateDataNeighbours( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ );

    cData*  GetSafeExternDataHandle( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ );
    cStaticLodChunk64*  GetSafeExternChunkHandle( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ );

public:
    // Naive Rendering
    void  DirectDraw();
    void  DirectDrawCube( tByte iMaterial );

private:
    // Private OpenGL Object Building
    void  InitVBOs();
    void  DestroyVBOs();
    void  UpdateVBOs();
    void  UpdateVBO( eFaceIndex  iVBO_ID_index );
    void  GenFace( eFaceIndex iFace, float* iData , int iX, int iY, int iZ );
    void  GenTopFace(   float* iData ,  int iIndex, float iX, float iY, float iZ );
    void  GenBotFace(   float* iData ,  int iIndex, float iX, float iY, float iZ );
    void  GenFrontFace( float* iData ,  int iIndex, float iX, float iY, float iZ );
    void  GenBackFace(  float* iData ,  int iIndex, float iX, float iY, float iZ );
    void  GenLeftFace(  float* iData ,  int iIndex, float iX, float iY, float iZ );
    void  GenRightFace( float* iData ,  int iIndex, float iX, float iY, float iZ );

private:
    // Private OpenGL Object Rendering
    void  DrawVBOs();
    void  DrawVBO( eFaceIndex  iVBO_ID_index );

private:
    // Private Data Members
    static  const  tByte            msSize = 64;
    static  const  unsigned  int    msCapacity = msSize * msSize * msSize; // size^3
    unsigned  int                   mOccupiedVolume;
    cStaticLodChunk64*              mNeighbour[6] = { 0, 0, 0, 0, 0, 0 };   // six neighbours
    cData                           mData[msSize][msSize][msSize];          // data
    GLuint                          mVBO_ID[6] = { 0, 0, 0, 0, 0, 0 };      // six VBO faces

};


} // namespace  nVolumetric

