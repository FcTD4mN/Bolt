#include "Core.Mapping.PhysicEntityGrid.h"


#include "Core.ECS.Component.SimplePhysic.h"
#include "Core.ECS.Component.Position.h"
#include "Core.ECS.Component.Size.h"
#include "Core.ECS.Core.Entity.h"


namespace nMapping {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------- Contruction/Destruction
// -------------------------------------------------------------------------------------


cEntityGrid::~cEntityGrid()
{
}


cEntityGrid::cEntityGrid( int iWidth, int iHeight, int iCellSize ) :
    mGridMap(),
    mWidth( iWidth ),
    mHeight( iHeight ),
    mCellSize( iCellSize )
{
    mGridMap.reserve( mWidth );
    for( int i = 0; i < mWidth; ++i )
    {
        mGridMap.push_back( std::vector< std::vector< ::nECS::cEntity* > >( mHeight ) );
    }
}


// -------------------------------------------------------------------------------------
// --------------------------------------------------------------------- Grid management
// -------------------------------------------------------------------------------------


void
cEntityGrid::AddEntity( ::nECS::cEntity* iEntity )
{
    if( !IsEntityValid( iEntity ) )
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
cEntityGrid::ClearEntityMap()
{
    for( int i = 0; i <= mWidth; ++i )
    {
        for( int j = 0; j <= mHeight; ++j )
        {
            mGridMap[ i ][ j ].clear();
        }
    }
}


void
cEntityGrid::RemoveEntityNotUpdated( ::nECS::cEntity* iEntity )
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
cEntityGrid::GetSurroundingEntitiesOf( std::vector< ::nECS::cEntity* >* oEntities, ::nECS::cEntity* iEntity )
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
                ::nECS::cEntity* ent = mGridMap[ i ][ j ][ k ];
                if( ent != iEntity && std::find( ( *oEntities ).begin(), ( *oEntities ).end(), ent ) == ( *oEntities ).end() )
                    ( *oEntities ).push_back( ent );
            }
        }
    }
}


void
cEntityGrid::GetEntitiesFollwingVectorFromEntity( std::vector< ::nECS::cEntity* >* oEntities, ::nECS::cEntity* iEntity, const sf::Vector2f & iVector )
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
            ::nECS::cEntity* ent = mGridMap[ xLookupToInt ][ yLookupToInt ][ k ];
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
cEntityGrid::GetEntitiesInBoundingBox( std::vector< ::nECS::cEntity*>* oEntities, const sf::Rect<float>& iBBox )
{
    int x, y, x2, y2;
    GetBBoxArea( &x, &y, &x2, &y2, iBBox );

    for( int i = x; i < x2; ++i )
    {
        for( int j = y; j < y2; ++j )
        {
            for( int k = 0; k < mGridMap[ i ][ j ].size(); ++k )
            {
                ::nECS::cEntity* ent = mGridMap[ i ][ j ][ k ];
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
cEntityGrid::GetBBoxArea( int * oX, int * oY, int * oX2, int * oY2, const sf::Rect<float>& iBBox )
{
    GetBBoxArea( oX, oY, oX2, oY2, iBBox.left, iBBox.top, iBBox.left + iBBox.width, iBBox.top + iBBox.height );
}


void cEntityGrid::GetBBoxArea( int * oX, int * oY, int * oX2, int * oY2, float iX, float iY, float iX2, float iY2 )
{
    *oX = int( iX ) / mCellSize;
    *oY = int( iY ) / mCellSize;

    *oX2 = int( iX2 ) / mCellSize + 1; // To grab the last cell as well
    *oY2 = int( iY2 ) / mCellSize + 1; // To grab the last cell as well

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


// ====================================================================================
// ====================================================================================
// ====================================================================================


cPhysicEntityGrid::~cPhysicEntityGrid()
{
}


cPhysicEntityGrid::cPhysicEntityGrid( int iWidth, int iHeight, int iCellSize ) :
    tSuperClass( iWidth, iHeight, iCellSize )
{
}


void
cPhysicEntityGrid::GetEntityArea( int * oX, int * oY, int * oX2, int * oY2, ::nECS::cEntity * iEntity )
{
    auto simplephysic = dynamic_cast< ::nECS::cSimplePhysic* >( iEntity->GetComponentByName( "simplephysic" ) );
    auto position = dynamic_cast< ::nECS::cPosition* >( iEntity->GetComponentByName( "position" ) );
    auto size = dynamic_cast< ::nECS::cSize* >( iEntity->GetComponentByName( "size" ) );

    sf::Vector2f entityCenter = position->AsVector2F();
    if( size )
        entityCenter += size->AsVector2F() / 2.0F;

    sf::FloatRect entityHitBox;
    entityHitBox = simplephysic->GetAbsoluteHitBoxUsingCenterPosition( entityCenter );

    tSuperClass::GetBBoxArea( oX, oY, oX2, oY2, entityHitBox.left, entityHitBox.top,
                              entityHitBox.left + entityHitBox.width, entityHitBox.top + entityHitBox.height );
}


bool cPhysicEntityGrid::IsEntityValid( ::nECS::cEntity * iEntity ) const
{
    auto position = dynamic_cast< ::nECS::cPosition* >( iEntity->GetComponentByName( "position" ) );
    auto size = dynamic_cast< ::nECS::cSize* >( iEntity->GetComponentByName( "size" ) );
    auto simplephysic = dynamic_cast< ::nECS::cSimplePhysic* >( iEntity->GetComponentByName( "simplephysic" ) );
    if( !position || !size || ! simplephysic )
        return  false;

    return  true;
}


// ====================================================================================
// ====================================================================================
// ====================================================================================


cPositionSizeGrid::~cPositionSizeGrid()
{
}


cPositionSizeGrid::cPositionSizeGrid( int iWidth, int iHeight, int iCellSize ) :
    tSuperClass( iWidth, iHeight, iCellSize )
{
}


void
cPositionSizeGrid::GetEntityArea( int * oX, int * oY, int * oX2, int * oY2, ::nECS::cEntity * iEntity )
{
    auto position = dynamic_cast< ::nECS::cPosition* >( iEntity->GetComponentByName( "position" ) );
    double x = position->X();
    double y = position->Y();
    double w = 1;
    double h = 1;
    auto size = dynamic_cast< ::nECS::cSize* >( iEntity->GetComponentByName( "size" ) );
    if( size )
    {
        w = size->W();
        h = size->H();
    }

    tSuperClass::GetBBoxArea( oX, oY, oX2, oY2, float(x), float(y), float(x + w), float(y + h ) );
}


bool
cPositionSizeGrid::IsEntityValid( ::nECS::cEntity * iEntity ) const
{
    auto position = dynamic_cast< ::nECS::cPosition* >( iEntity->GetComponentByName( "position" ) );
    if( !position )
        return  false;

    return  true;
}

} // namespace nMapping

