#include "PhysicEntityGrid.h"


#include "ECS/Core/Entity.h"
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
    mCellSize( 32 )
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

    // We crop so that entities that are part outside the grid and part inside can be treated
    int left   = x     <   0 ? 0 : x;
    int top    = y     <   0 ? 0 : y;
    int right  = x2    >= mWidth - 1 ? mWidth - 1 : x2;
    int bottom = y2    >= mWidth - 1 ? mWidth - 1 : y2;

    // We store the pointer of iEntity in every cell that it is contained within, so we know at any time which entity should be considered
    // when looking for collision
    for( int i = left; i <= right; ++i )
    {
        for( int j = top; j <= bottom; ++j )
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

    // We crop so that entities that are part outside the grid and part inside can be treated
    int left = x     <   0 ? 0 : x;
    int top = y     <   0 ? 0 : y;
    int right = x2 >= mWidth - 1 ? mWidth - 1 : x2;
    int bottom = y2 >= mWidth - 1 ? mWidth - 1 : y2;

    for( int i = left; i <= right; ++i )
    {
        for( int j = top; j <= bottom; ++j )
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


void
cEntityGrid::GetSurroundingEntitiesOf( std::vector<cEntity*>* oEntities, cEntity* iEntity )
{
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
                if( ent != iEntity && std::find( ( *oEntities ).begin(), ( *oEntities ).end(), ent ) == ( *oEntities ).end() )
                    ( *oEntities ).push_back( ent );
            }
        }
    }
}


void
cEntityGrid::GetEntitiesFollwingVectorFromEntity( std::vector<cEntity*>* oEntities, cEntity * iEntity, const sf::Vector2f & iVector )
{
    int x, y, x2, y2;
    GetEntityArea( &x, &y, &x2, &y2, iEntity );

    float xLookup = float(x);
    float yLookup = float(y);
    int  xLookupToInt = int( xLookup );
    int  yLookupToInt = int( yLookup );

    while( xLookupToInt >= 0 && yLookupToInt >= 0 && xLookupToInt < mWidth && yLookupToInt < mHeight )
    {
        for( int k = 0; k < mGridMap[ xLookupToInt ][ yLookupToInt ].size(); ++k )
        {
            cEntity* ent = mGridMap[ xLookupToInt ][ yLookupToInt ][ k ];
            if( ent != iEntity && std::find( ( *oEntities ).begin(), ( *oEntities ).end(), ent ) == ( *oEntities ).end() )
                ( *oEntities ).push_back( ent );
        }
        xLookup += iVector.x;
        yLookup += iVector.y;
        xLookupToInt = int( xLookup );
        yLookupToInt = int( yLookup );
    }
}


void
cEntityGrid::GetEntitiesInBoundingBox( std::vector<cEntity*>* oEntities, const sf::Rect<float>& iBBox )
{
    int x, y, x2, y2;
    GetBBoxArea( &x, &y, &x2, &y2, iBBox );

    for( int i = x; i < x2; ++i )
    {
        for( int j = y; j < y2; ++j )
        {
            for( int k = 0; k < mGridMap[ i ][ j ].size(); ++k )
            {
                cEntity* ent = mGridMap[ i ][ j ][ k ];
                if( std::find( (*oEntities).begin(), ( *oEntities ).end(), ent ) == ( *oEntities ).end() )
                    ( *oEntities ).push_back( ent );
            }
        }
    }
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------- Private computing methods
// -------------------------------------------------------------------------------------


void
cEntityGrid::GetEntityArea( int* oX, int* oY, int* oX2, int* oY2, cEntity* iEntity )
{
    auto simplephysic = dynamic_cast< cSimplePhysic* >( iEntity->GetComponentByName( "simplephysic" ) );

    GetBBoxArea( oX, oY, oX2, oY2, simplephysic->mHitBox.left, simplephysic->mHitBox.top, simplephysic->mHitBox.left + simplephysic->mHitBox.width, simplephysic->mHitBox.top + simplephysic->mHitBox.height );
}


void
cEntityGrid::GetBBoxArea( int * oX, int * oY, int * oX2, int * oY2, const sf::Rect<float>& iBBox )
{
    GetBBoxArea( oX, oY, oX2, oY2, iBBox.left, iBBox.top, iBBox.left + iBBox.width, iBBox.top + iBBox.height );
}


void cEntityGrid::GetBBoxArea( int * oX, int * oY, int * oX2, int * oY2, float iX, float iY, float iX2, float iY2 )
{
    *oX = int( iX ) / mCellSize;
    *oY = int( iY ) / mCellSize;

    *oX2 = int( iX2 ) / mCellSize;
    *oY2 = int( iY2 ) / mCellSize;

    // If an entity wants to be added out of grid bouds, it justs sets ox2 and oy2 so that we won't get in any of the "for" loops
    if( *oX >= mWidth || *oY >= mHeight || *oX2 < 0 || *oY2 < 0 )
    {
        *oX2 = *oX - 1;
        *oY2 = *oY - 1;
        return;
    }

    // Clamping to avoid seeking out of bounds
    if( *oX < 0 )
        *oX = 0;
    if( *oY < 0 )
        *oY = 0;
    if( *oX2 > mWidth - 1 )
        *oX2 = mWidth - 1;
    if( *oY2 > mHeight - 1 )
        *oY2 = mHeight - 1;
}
