#include "Volumetric/Static64/StaticLodChunk64.h"
#include "Volumetric/Static64/VUtils.h"


namespace  nVolumetric
{

//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


cStaticLodChunk64::~cStaticLodChunk64()
{
    DestroyVBOs();
}


cStaticLodChunk64::cStaticLodChunk64() :
    mOccupiedVolume( 0 )
{
}


 cStaticLodChunk64::cStaticLodChunk64( tByte iVal ) :
    mOccupiedVolume( 0 )
{
    Fill( iVal );
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
    cData* topDataHandle    = GetSafeExternDataHandle( iX,     iY-1,   iZ      );
    cData* botDataHandle    = GetSafeExternDataHandle( iX,     iY+1,   iZ      );
    cData* frontDataHandle  = GetSafeExternDataHandle( iX,     iY,     iZ-1    );
    cData* backDataHandle   = GetSafeExternDataHandle( iX,     iY,     iZ+1    );
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

    tLocalDataIndex safeX = iX % msSize;
    tLocalDataIndex safeY = iY % msSize;
    tLocalDataIndex safeZ = iZ % msSize;
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
cStaticLodChunk64::DirectDraw()
{
    for( tLocalDataIndex  i = 0; i < msSize; ++i )
    {
        for( tLocalDataIndex  j = 0; j < msSize; ++j )
        {
            for( tLocalDataIndex  k = 0; k < msSize; ++k )
            {
                glPushMatrix();
                glTranslatef( i, j, k );

                if( IsSolid( i, j, k ) )
                    DirectDrawCube( GetMaterial( i, j, k ) );

                glPopMatrix();
            }
        }
    }
}


void
cStaticLodChunk64::DirectDrawCube( tByte iMaterial )
{
    float g = float( iMaterial ) / 255.f;
    glBegin(GL_QUADS);
    glColor3f( g, g, g );

    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f,  0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);

    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f,  0.5f, 0.5f);
    glVertex3f( 0.5f,  0.5f, 0.5f);
    glVertex3f( 0.5f, -0.5f, 0.5f);

    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f, -0.5f);
    glVertex3f(-0.5f,  0.5f,  0.5f);
    glVertex3f(-0.5f, -0.5f,  0.5f);

    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f,  0.5f, -0.5f);
    glVertex3f(0.5f,  0.5f,  0.5f);
    glVertex3f(0.5f, -0.5f,  0.5f);

    glVertex3f(-0.5f, -0.5f,  0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f,  0.5f);

    glVertex3f(-0.5f, 0.5f,  0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f( 0.5f, 0.5f, -0.5f);
    glVertex3f( 0.5f, 0.5f,  0.5f);

    glEnd();
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

    int size = mOccupiedVolume * 6 * 3;
    float* vertices = new float[ size ];
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
                    GenFace( iVBO_ID_index, 64, 4096, vertices, i, j, k );
                }
            }
        }
    }

    glBindBuffer( GL_ARRAY_BUFFER, mVBO_ID[ iVBO_ID_index ] );

        glBufferData( GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------- Private OpenGL Object Rendering


void
cStaticLodChunk64::DrawVBOs()
{
    DrawVBO( eNF_Index::kIndexTop );
    DrawVBO( eNF_Index::kIndexBot );
    DrawVBO( eNF_Index::kIndexFront );
    DrawVBO( eNF_Index::kIndexBack );
    DrawVBO( eNF_Index::kIndexLeft );
    DrawVBO( eNF_Index::kIndexRight );
}


void
cStaticLodChunk64::DrawVBO( eNF_Index  iVBO_ID_index )
{
    // void glVertexAttribPointer(GLuint index, GLuint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer);

    glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID[ iVBO_ID_index ] );

        // Accès aux vertices dans la mémoire vidéo
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET( 0 ) );
        glEnableVertexAttribArray(0);

        // Accès aux couleurs dans la mémoire vidéo
        //glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 0, shift );
        //glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


} // namespace  nVolumetric

