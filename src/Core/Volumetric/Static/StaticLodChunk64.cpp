#include "Volumetric/Static/StaticLodChunk64.h"
#include "Volumetric/Static/VUtils.h"


namespace  nVolumetric
{


static  const  sf::Vector3f  sgUniformFaceNormals[6] = { sf::Vector3f(  0.f,    +1.f,   0.f     ),      // Top
                                                         sf::Vector3f(  0.f,    -1.f,   0.f     ),      // Bot
                                                         sf::Vector3f(  0.f,    0.f,    +1.f    ),      // Front
                                                         sf::Vector3f(  0.f,    0.f,    -1.f    ),      // Back
                                                         sf::Vector3f(  -1.f,   0.f,    0.f     ),      // Left
                                                         sf::Vector3f(  +1.f,   0.f,    0.f     ) };    // Right

//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


cStaticLodChunk64::~cStaticLodChunk64()
{
    DestroyVBOs();
}


cStaticLodChunk64::cStaticLodChunk64() :
    mOccupiedVolume( 0 ),
    mNVerticesVBOElem( 0 ),
    mDebugColor( sf::Vector3f() )
{
    InitVBOs();
}


 cStaticLodChunk64::cStaticLodChunk64( tByte iVal ) :
    mOccupiedVolume( 0 ),
    mNVerticesVBOElem( 0 ),
    mDebugColor( sf::Vector3f() )
{
    Fill( iVal );
    InitVBOs();
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Volume Information


tByte cStaticLodChunk64::Size()  const
{
    return  msSize;
}


unsigned  int 
cStaticLodChunk64::Capacity()  const
{
    return  msCapacity;
}


unsigned  int
cStaticLodChunk64::OccupiedVolume()  const
{
    return  mOccupiedVolume;
}


bool
cStaticLodChunk64::IsFull()  const
{
    return  mOccupiedVolume == msCapacity;
}


bool
cStaticLodChunk64::IsEmpty()  const
{
    return  mOccupiedVolume == 0;
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- Volume Manipulation


void
cStaticLodChunk64::Fill(tByte iVal)
{
    for( tLocalDataIndex  i = 0; i < msSize; ++i )
    {
        for( tLocalDataIndex  j = 0; j < msSize; ++j )
        {
            for( tLocalDataIndex  k = 0; k < msSize; ++k )
            {
                mData[i][j][k] = iVal;
            }
        }
    }

    if( iVal == sgEmptyMaterial )
        mOccupiedVolume = 0;
    else
        mOccupiedVolume = msCapacity;
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------- Material Accessors


bool
cStaticLodChunk64::IsSolid( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )  const
{
    return  mData[iX][iY][iZ].IsSolid();
}


tByte
cStaticLodChunk64::GetMaterial( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )  const
{
    return  mData[iX][iY][iZ].GetMaterialField();
}


void
cStaticLodChunk64::SetMaterial( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ, tByte iValue )
{
    tByte oldMat = GetMaterial( iX, iY, iZ );
    mData[iX][iY][iZ].SetMaterialField( iValue );

    tByte flag = tByte( bool( oldMat ) ) << 1 | tByte( bool( iValue ) );
    // Bitfield manipulation:
    // 11   old solid - new solid   - 3 - no change
    // 10   old solid - new empty   - 2 - decrease occupied volume
    // 01   old empty - new solid   - 1 - increase occupied volume
    // 00   old empty - new empty   - 0 - no change
    if( flag == 2 ) --mOccupiedVolume;
    if( flag == 1 ) ++mOccupiedVolume;

    if( flag == 1 || flag == 2 )    // Update neighbours in case of change
    {
        UpdateDataNeighbours( iX, iY, iZ );
    }
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- Neighbour Accessors


cStaticLodChunk64*
cStaticLodChunk64::GetNeighbour( eNF_Index  iNeighbour )  const
{
    return  mNeighbour[ iNeighbour ];
}


void cStaticLodChunk64::SetNeighbour( eNF_Index iNeighbour, cStaticLodChunk64* iAdress )
{
    mNeighbour[ iNeighbour ] = iAdress;
}


//----------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------- Data Manipulation


cData*
cStaticLodChunk64::DataHandle( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )
{
    return  &mData[iX][iY][iZ];
}


void
cStaticLodChunk64::UpdateDataNeighbours( tLocalDataIndex iX, tLocalDataIndex iY, tLocalDataIndex iZ )
{
    cData* currentHandle    = DataHandle( iX, iY, iZ );
    bool  currentIsSolid    = currentHandle->IsSolid();
    cData* topDataHandle    = GetSafeExternDataHandle( iX,     iY+1,   iZ      );
    cData* botDataHandle    = GetSafeExternDataHandle( iX,     iY-1,   iZ      );
    cData* frontDataHandle  = GetSafeExternDataHandle( iX,     iY,     iZ+1    );
    cData* backDataHandle   = GetSafeExternDataHandle( iX,     iY,     iZ-1    );
    cData* leftDataHandle   = GetSafeExternDataHandle( iX-1,   iY,     iZ      );
    cData* rightDataHandle  = GetSafeExternDataHandle( iX+1,   iY,     iZ      );

    if( topDataHandle )
    {
        currentHandle->SetNeighbour( eNF_Flag::kFlagTop, topDataHandle->IsSolid() );
        topDataHandle->SetNeighbour( eNF_Flag::kFlagBot, currentIsSolid );
    }

    if( botDataHandle )
    {
        currentHandle->SetNeighbour( eNF_Flag::kFlagBot, botDataHandle->IsSolid() );
        botDataHandle->SetNeighbour( eNF_Flag::kFlagTop, currentIsSolid );
    }

    if( frontDataHandle )
    {
        currentHandle->SetNeighbour( eNF_Flag::kFlagFront, frontDataHandle->IsSolid() );
        frontDataHandle->SetNeighbour( eNF_Flag::kFlagBack, currentIsSolid );
    }

    if( backDataHandle )
    {
        currentHandle->SetNeighbour( eNF_Flag::kFlagBack, backDataHandle->IsSolid() );
        backDataHandle->SetNeighbour( eNF_Flag::kFlagFront, currentIsSolid );
    }

    if( leftDataHandle )
    {
        currentHandle->SetNeighbour( eNF_Flag::kFlagLeft, leftDataHandle->IsSolid() );
        leftDataHandle->SetNeighbour( eNF_Flag::kFlagRight, currentIsSolid );
    }

    if( rightDataHandle )
    {
        currentHandle->SetNeighbour( eNF_Flag::kFlagRight, rightDataHandle->IsSolid() );
        rightDataHandle->SetNeighbour( eNF_Flag::kFlagLeft, currentIsSolid );
    }
}


cData*
cStaticLodChunk64::GetSafeExternDataHandle( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )
{
    auto chunk = GetSafeExternChunkHandle( iX, iY, iZ );
    if( !chunk )
        return  NULL;

    int w = int( msSize );
    tLocalDataIndex safeX = tLocalDataIndex( iX % w + ( iX % w < 0 ? w : 0) );
    tLocalDataIndex safeY = tLocalDataIndex( iY % w + ( iY % w < 0 ? w : 0) );
    tLocalDataIndex safeZ = tLocalDataIndex( iZ % w + ( iZ % w < 0 ? w : 0) );
    return  chunk->DataHandle( safeX, safeY, safeZ );
}


 cStaticLodChunk64*
cStaticLodChunk64::GetSafeExternChunkHandle( tGlobalDataIndex iX, tGlobalDataIndex iY, tGlobalDataIndex iZ )
{
    if( ( iX >= 0 && iX < msSize ) &&
        ( iY >= 0 && iY < msSize ) &&
        ( iZ >= 0 && iZ < msSize ) )
    {
        return  this;
    }
    else
    {
        if( iY == -1 )      return  mNeighbour[ eNF_Index::kIndexTop ];
        if( iY == msSize )  return  mNeighbour[ eNF_Index::kIndexBot ];
        if( iZ == -1 )      return  mNeighbour[ eNF_Index::kIndexFront ];
        if( iZ == msSize )  return  mNeighbour[ eNF_Index::kIndexBack ];
        if( iX == -1 )      return  mNeighbour[ eNF_Index::kIndexLeft ];
        if( iX == msSize )  return  mNeighbour[ eNF_Index::kIndexRight ];
    }

    return  NULL;
}


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Naive Rendering


void
cStaticLodChunk64::DrawVBOs( GLuint iShaderProgramID )
{
    SendUniformDebugColor( iShaderProgramID );
    DrawVBO( eNF_Index::kIndexTop   , iShaderProgramID );
    DrawVBO( eNF_Index::kIndexBot   , iShaderProgramID );
    DrawVBO( eNF_Index::kIndexFront , iShaderProgramID );
    DrawVBO( eNF_Index::kIndexBack  , iShaderProgramID );
    DrawVBO( eNF_Index::kIndexLeft  , iShaderProgramID );
    DrawVBO( eNF_Index::kIndexRight , iShaderProgramID );
}


void
cStaticLodChunk64::SetDebugColor( const  sf::Vector3f& iDebugColor )
{
    mDebugColor = iDebugColor;
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- VBO Interface


void
cStaticLodChunk64::UpdateVBOs()
{
    UpdateVBO( eNF_Index::kIndexTop );
    UpdateVBO( eNF_Index::kIndexBot );
    UpdateVBO( eNF_Index::kIndexFront );
    UpdateVBO( eNF_Index::kIndexBack );
    UpdateVBO( eNF_Index::kIndexLeft );
    UpdateVBO( eNF_Index::kIndexRight );
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------- Private OpenGL Object Building


void
cStaticLodChunk64::InitVBOs()
{
    glGenBuffers( 6, mVBO_ID );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO_ID[ eNF_Index::kIndexTop ] );
        glBufferData( GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO_ID[ eNF_Index::kIndexBot ] );
        glBufferData( GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO_ID[ eNF_Index::kIndexFront ] );
        glBufferData( GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO_ID[ eNF_Index::kIndexBot ] );
        glBufferData( GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO_ID[ eNF_Index::kIndexLeft ] );
        glBufferData( GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, mVBO_ID[ eNF_Index::kIndexRight ] );
        glBufferData( GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}


void
cStaticLodChunk64::DestroyVBOs()
{
    glDeleteBuffers( 6, mVBO_ID );
}


void
cStaticLodChunk64::UpdateVBO( eNF_Index  iVBO_ID_index )
{
    if(glIsBuffer( mVBO_ID[ iVBO_ID_index ] ) == GL_TRUE)
        glDeleteBuffers( 1, &mVBO_ID[ iVBO_ID_index ] );

    glGenBuffers( 1, &mVBO_ID[ iVBO_ID_index ] );

    int stride = 6;
    mNVerticesVBOElem = OccupiedVolume() * stride;
    int index = 0;
    std::vector< sf::Vector3f > vertices;
    vertices.resize( mNVerticesVBOElem );
    int memsize = msElementSize * mNVerticesVBOElem;

    int colorstride = 6;
    mNColorsVBOElem = OccupiedVolume() * colorstride;
    int colorindex = 0;
    std::vector< sf::Vector3f > colors;
    colors.resize( mNColorsVBOElem );
    int memcolorsize = msElementSize * mNColorsVBOElem;

    eNF_Flag neighbourFlag = NF_IndexToFlag( iVBO_ID_index );

    for( tLocalDataIndex  i = 0; i < msSize; ++i )
    {
        for( tLocalDataIndex  j = 0; j < msSize; ++j )
        {
            for( tLocalDataIndex  k = 0; k < msSize; ++k )
            {
                cData* data = DataHandle( i, j, k );
                if( data->IsSolid() && !data->HasNeighbour( neighbourFlag ) )
                {
                    GenFace( iVBO_ID_index, index, vertices, i, j, k );
                    sf::Vector3f color = ColorFromVGAMaterial( data->GetMaterialField() );
                    colors[index + 0] = color;
                    colors[index + 1] = color;
                    colors[index + 2] = color;
                    colors[index + 3] = color;
                    colors[index + 4] = color;
                    colors[index + 5] = color;
                    index += stride;
                    colorindex += colorstride;
                }
            }
        }
    }

    glBindBuffer( GL_ARRAY_BUFFER, mVBO_ID[ iVBO_ID_index ] );

        glBufferData( GL_ARRAY_BUFFER, memsize + memcolorsize, 0, GL_STATIC_DRAW );
        glBufferSubData( GL_ARRAY_BUFFER, 0, memsize, &vertices[0] );
        glBufferSubData( GL_ARRAY_BUFFER, memsize, memcolorsize, &colors[0] );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    mVerticesMsize = memsize;
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------- Private OpenGL Object Rendering


void
cStaticLodChunk64::DrawVBO( eNF_Index  iVBO_ID_index, GLuint iShaderProgramID )
{
    SendUniformNormal( iVBO_ID_index, iShaderProgramID );

    glBindBuffer( GL_ARRAY_BUFFER, mVBO_ID[ iVBO_ID_index ] );

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET( 0 ) );
    glEnableVertexAttribArray( 0 );

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET( mVerticesMsize ) );
    glEnableVertexAttribArray( 1 );

    glDrawArrays( GL_TRIANGLES, 0, mNVerticesVBOElem );

    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}


void
cStaticLodChunk64::SendUniformNormal( eNF_Index  iVBO_ID_index, GLuint iShaderProgramID  )
{
    int location = glGetUniformLocation( iShaderProgramID, "normal" );
    auto normal = sgUniformFaceNormals[ iVBO_ID_index ];
    glUniform3f(location, normal.x, normal.y, normal.z );
}


void
cStaticLodChunk64::SendUniformDebugColor( GLuint iShaderProgramID  )
{
    int location = glGetUniformLocation( iShaderProgramID, "debugColor" );
    glUniform3f(location, mDebugColor.x, mDebugColor.y, mDebugColor.z );
}



} // namespace  nVolumetric

