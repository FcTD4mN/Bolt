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
cEntityGrid::AddObject( cEntity* iEntity )
{
    auto simplephysic = dynamic_cast< cSimplePhysic* >( iEntity->GetComponentByName( "simplephysic" ) );
    if( !simplephysic )
        return;

    int x = int( simplephysic->mHitBox.left ) / mCellSize;
    int y = int( simplephysic->mHitBox.top )  / mCellSize;

    int x2 = int( simplephysic->mHitBox.left + simplephysic->mHitBox.width ) / mCellSize;
    int y2 = int( simplephysic->mHitBox.top + simplephysic->mHitBox.height ) / mCellSize;


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


std::vector< cEntity* >
cEntityGrid::GetSurroundingEntitiesOf( cEntity* iEntity )
{
    std::vector< cEntity* > result;
    auto simplephysic = dynamic_cast< cSimplePhysic* >( iEntity->GetComponentByName( "simplephysic" ) );
    int x = int( simplephysic->mHitBox.left ) / mCellSize;
    int y = int( simplephysic->mHitBox.top ) / mCellSize;


    mGridMap[ x ][ y ].push_back( iEntity );

    return  result;
}
