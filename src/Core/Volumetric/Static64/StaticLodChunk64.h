#pragma once


#include "Volumetric/Static64/Data.h"
#include "Volumetric/Static64/Types.h"


#include <GL/glew.h>
#include <gl/GLU.h>
#include "SFML/OpenGL.hpp"


namespace  nVolumetric
{


class  cStaticLodChunk64
{

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
    cStaticLodChunk64*  GetNeighbour( eNF_Index  iNeighbourIndex )  const;
    void                SetNeighbour( eNF_Index  iNeighbourIndex, cStaticLodChunk64* iAdress );

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
    void  DestroyVBOs();
    void  UpdateVBOs();
    void  UpdateVBO( eNF_Index  iVBO_ID_index );

private:
    // Private OpenGL Object Rendering
    void  DrawVBOs();
    void  DrawVBO( eNF_Index  iVBO_ID_index );

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

