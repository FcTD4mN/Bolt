#include "Volumetric/Static64/StaticLodChunk64.h"


namespace  nVolumetric
{

//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction


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
//---------------------------------------------------------------- Public OpenGL Object Building


void
cStaticLodChunk64::BuildVBOs()
{
}


//----------------------------------------------------------------------------------------------
//--------------------------------------------------------------- Private OpenGL Object Building


void
cStaticLodChunk64::InitVBOs()
{
    if(glIsBuffer( mVBO_ID[0] ) == GL_TRUE)
        return;

    glGenBuffers( 6, mVBO_ID );

    float   voidData = 0.f;
    int     defaultSize = 0;

    //glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID[ eFaceIndex::kTop ]);
    //glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
    //glBufferSubData(GL_ARRAY_BUFFER, shift, size, data);
    //glBindBuffer(GL_ARRAY_BUFFER, 0);

    glNamedBufferData( mVBO_ID[ eFaceIndex::kTop ],     defaultSize, &voidData, GL_DYNAMIC_DRAW );
    glNamedBufferData( mVBO_ID[ eFaceIndex::kBot ],     defaultSize, &voidData, GL_DYNAMIC_DRAW );
    glNamedBufferData( mVBO_ID[ eFaceIndex::kFront ],   defaultSize, &voidData, GL_DYNAMIC_DRAW );
    glNamedBufferData( mVBO_ID[ eFaceIndex::kBack ],    defaultSize, &voidData, GL_DYNAMIC_DRAW );
    glNamedBufferData( mVBO_ID[ eFaceIndex::kLeft ],    defaultSize, &voidData, GL_DYNAMIC_DRAW );
    glNamedBufferData( mVBO_ID[ eFaceIndex::kRight ],   defaultSize, &voidData, GL_DYNAMIC_DRAW );
}


void
cStaticLodChunk64::DestroyVBOs()
{
    glDeleteBuffers( 6, mVBO_ID );
}



void
cStaticLodChunk64::UpdateVBOs()
{
    UpdateVBO( eFaceIndex::kTop );
    UpdateVBO( eFaceIndex::kBot );
    UpdateVBO( eFaceIndex::kFront );
    UpdateVBO( eFaceIndex::kBack );
    UpdateVBO( eFaceIndex::kLeft );
    UpdateVBO( eFaceIndex::kRight );
}


void
cStaticLodChunk64::UpdateVBO( eFaceIndex  iVBO_ID_index )
{
    glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID[ iVBO_ID_index ] );

        void *VBO_adress = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
        if(VBO_adress == NULL)
        {
            //Error
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            return; 
        }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------- Neighbour Accessors


cStaticLodChunk64*
cStaticLodChunk64::GetNeighbour( eFaceIndex  iNeighbour )  const
{
    return  mNeighbour[ iNeighbour ];
}


void cStaticLodChunk64::SetNeighbour( eFaceIndex iNeighbour, cStaticLodChunk64* iAdress )
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
        currentHandle->SetNeighbour( cData::eDataNeighbourFlag::kTop, topDataHandle->IsSolid() );
        topDataHandle->SetNeighbour( cData::eDataNeighbourFlag::kBot, currentIsSolid );
    }

    if( botDataHandle )
    {
        currentHandle->SetNeighbour( cData::eDataNeighbourFlag::kBot, botDataHandle->IsSolid() );
        botDataHandle->SetNeighbour( cData::eDataNeighbourFlag::kTop, currentIsSolid );
    }

    if( frontDataHandle )
    {
        currentHandle->SetNeighbour( cData::eDataNeighbourFlag::kFront, frontDataHandle->IsSolid() );
        frontDataHandle->SetNeighbour( cData::eDataNeighbourFlag::kBack, currentIsSolid );
    }

    if( backDataHandle )
    {
        currentHandle->SetNeighbour( cData::eDataNeighbourFlag::kBack, backDataHandle->IsSolid() );
        backDataHandle->SetNeighbour( cData::eDataNeighbourFlag::kFront, currentIsSolid );
    }

    if( leftDataHandle )
    {
        currentHandle->SetNeighbour( cData::eDataNeighbourFlag::kLeft, leftDataHandle->IsSolid() );
        leftDataHandle->SetNeighbour( cData::eDataNeighbourFlag::kRight, currentIsSolid );
    }

    if( rightDataHandle )
    {
        currentHandle->SetNeighbour( cData::eDataNeighbourFlag::kRight, rightDataHandle->IsSolid() );
        rightDataHandle->SetNeighbour( cData::eDataNeighbourFlag::kLeft, currentIsSolid );
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
        if( iY == -1 )      return  mNeighbour[ eFaceIndex::kTop ];
        if( iY == msSize )  return  mNeighbour[ eFaceIndex::kBot ];
        if( iZ == -1 )      return  mNeighbour[ eFaceIndex::kFront ];
        if( iZ == msSize )  return  mNeighbour[ eFaceIndex::kBack ];
        if( iX == -1 )      return  mNeighbour[ eFaceIndex::kLeft ];
        if( iX == msSize )  return  mNeighbour[ eFaceIndex::kRight ];
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
//------------------------------------------------------------------------------ Naive Rendering


void
cStaticLodChunk64::DrawVBOs()
{
    DrawVBO( eFaceIndex::kTop );
    DrawVBO( eFaceIndex::kBot );
    DrawVBO( eFaceIndex::kFront );
    DrawVBO( eFaceIndex::kBack );
    DrawVBO( eFaceIndex::kLeft );
    DrawVBO( eFaceIndex::kRight );
}


void
cStaticLodChunk64::DrawVBO( eFaceIndex  iVBO_ID_index )
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

