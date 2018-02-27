#include "PhysicEntityGrid.h"


#include "ECS/Entity.h"
#include "GameMockup/Components/SimplePhysic.h"

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------- Contruction/Destruction
// -------------------------------------------------------------------------------------


cEntityGrid::~cEntityGrid()
{
}


cEntityGrid::cEntityGrid() :
    mGridMap(),
    mWidth( 256 ),
    mHeight( 256 ),
    mCellSize( 16 )
{
    mGridMap.reserve( mWidth );
    for( int i = 0; i < mWidth; ++i )
    {
        mGridMap.push_back( std::vector< std::vector< cEntity* > >( mHeight ) );
    }
}


// -------------------------------------------------------------------------------------
// --------------------------------------------------------------------- Grid management
// -------------------------------------------------------------------------------------


void
cEntityGrid::AddEntity( cEntity* iEntity )
{
    auto simplephysic = dynamic_cast< cSimplePhysic* >( iEntity->GetComponentByName( "simplephysic" ) );
    if( !simplephysic )
        return;

    int x, y, x2, y2;
    GetEntityArea( &x, &y, &x2, &y2, iEntity );

    // We store the pointer of iEntity in every cell that it is contained within, so we know at any time which entity should be considered
    // when looking for collision
    for( int i = x; i <= x2; ++i )
    {
        for( int j = y; j <= y2; ++j )
        {
            mGridMap[ i ][ j ].push_back( iEntity );
        }
    }
}


void
cEntityGrid::RemoveEntityNotUpdated( cEntity* iEntity )
{
    int x, y, x2, y2;
    GetEntityArea( &x, &y, &x2, &y2, iEntity );

    for( int i = x; i <= x2; ++i )
    {
        for( int j = y; j <= y2; ++j )
        {
            for( int k = 0; k < mGridMap[ i ][ j ].size(); ++k )
            {
                if( mGridMap[ i ][ j ][ k ] == iEntity )
                {
                    mGridMap[ i ][ j ].erase( mGridMap[ i ][ j ].begin() + k );
                    break; // iEntity should be present once per cell, no more, so when we found it --> NEXT
                }
            }
        }
    }
}


std::vector< cEntity* >
cEntityGrid::GetSurroundingEntitiesOf( cEntity* iEntity )
{
    std::vector< cEntity* > result;
    int x, y, x2, y2;
    GetEntityArea( &x, &y, &x2, &y2, iEntity );

    for( int i = x-1; i <= x2+1; ++i )
    {
        for( int j = y-1; j <= y2+1; ++j )
        {
            for( int k = 0; k < mGridMap[ i ][ j ].size(); ++k )
            {
                result.push_back( mGridMap[ i ][ j ][ k ] );
            }
        }
    }

    return  result;
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------- Private computing methods
// -------------------------------------------------------------------------------------


void
cEntityGrid::GetEntityArea( int* oX, int* oY, int* oX2, int* oY2, cEntity* iEntity )
{
    auto simplephysic = dynamic_cast< cSimplePhysic* >( iEntity->GetComponentByName( "simplephysic" ) );

    *oX = int( simplephysic->mHitBox.left ) / mCellSize;
    *oY = int( simplephysic->mHitBox.top ) / mCellSize;

    *oX2 = int( simplephysic->mHitBox.left + simplephysic->mHitBox.width ) / mCellSize;
    *oY2 = int( simplephysic->mHitBox.top + simplephysic->mHitBox.height ) / mCellSize;
}
