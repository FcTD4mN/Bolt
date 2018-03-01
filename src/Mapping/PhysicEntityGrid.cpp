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
    mWidth( 1024 ),
    mHeight( 1024 ),
    mCellSize( 2 )
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

    // We compute the enlarged rectangle that represent "one cell distance"
    int left    = x - 1     <   0           ? 0         : x - 1;
    int top     = y - 1     <   0           ? 0         : y - 1;
    int right   = x2 + 1    >=  mWidth -1   ? mWidth -1 : x2 + 1;
    int bottom  = y2 + 1    >=  mWidth -1   ? mWidth -1 : y2 + 1;

    for( int i = left; i <= right; ++i )
    {
        for( int j = top; j <= bottom; ++j )
        {
            for( int k = 0; k < mGridMap[ i ][ j ].size(); ++k )
            {
                cEntity* ent = mGridMap[ i ][ j ][ k ];
                if( ent != iEntity && std::find( result.begin(), result.end(), ent ) == result.end() )
                    result.push_back( ent );
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
