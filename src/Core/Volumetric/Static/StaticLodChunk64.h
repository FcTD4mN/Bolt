#pragma once


#include "Volumetric/Static/Data.h"
#include "Volumetric/Static/Types.h"


#include <GL/glew.h>
#include <gl/GLU.h>
#include "SFML/OpenGL.hpp"
#include "SFML/Graphics.hpp"


namespace  nVolumetric
{


class  cStaticLodChunk64
{

public:
    // Construction / Destruction
    ~cStaticLodChunk64();
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
    void    Fill( tByte iVal );

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
    cData*              DataHandle( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ );
    void                UpdateDataNeighbours( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ );

    cData*              GetSafeExternDataHandle( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ );
    cStaticLodChunk64*  GetSafeExternChunkHandle( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ );

public:
    // Naive Rendering
    void  DrawVBOs( GLuint iShaderProgramID );
    void  SetDebugColor( const  sf::Vector3f& iDebugColor );

public:
    // VBO Interface
    void  UpdateVBOs();

private:
    // Private OpenGL Object Building
    void  InitVBOs();
    void  DestroyVBOs();
    void  UpdateVBO( eNF_Index  iVBO_ID_index );

private:
    // Private OpenGL Object Rendering
    void  DrawVBO( eNF_Index  iVBO_ID_index, GLuint iShaderProgramID  );
    void  SendUniformNormal( eNF_Index  iVBO_ID_index, GLuint iShaderProgramID  );
    void  SendUniformDebugColor( GLuint iShaderProgramID  );

private:
    // Private Data Members
    static  const  tByte            msSize = 64;
    static  const  unsigned  int    msCapacity = msSize * msSize * msSize; // size^3
    unsigned  int                   mOccupiedVolume;
    cStaticLodChunk64*              mNeighbour[6] = { 0, 0, 0, 0, 0, 0 };   // six neighbours
    cData                           mData[msSize][msSize][msSize];          // data
    GLuint                          mVBO_ID[6] = { 0, 0, 0, 0, 0, 0 };
    GLuint                          mNVerticesVBOElem;
    GLuint                          mNColorsVBOElem;
    static  const  int              msElementSize = sizeof( sf::Vector3f );
    GLuint                          mVerticesMsize;
    sf::Vector3f                    mDebugColor;
};


} // namespace  nVolumetric

