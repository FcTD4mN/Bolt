#include "Core.Mapping.PhysicEntityGrid.h"


#include "Core.ECS.Component.SimplePhysic.h"
#include "Core.ECS.Component.Position.h"
#include "Core.ECS.Component.Size.h"
#include "Core.ECS.Core.Entity.h"

#include "Core.Math.Utils.h"

namespace nMapping {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------- Contruction/Destruction
// -------------------------------------------------------------------------------------


cEntityGrid::~cEntityGrid()
{
}


cEntityGrid::cEntityGrid( int iWidth, int iHeight, int iCellSize ) :
    mGridMap(),
	mEntityMap(),
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
    SetEntityInGrid( iEntity );

    mAllEntities.push_back( iEntity );
}


void
cEntityGrid::ClearEntityMap()
{
    ClearGrid();
    mAllEntities.clear();
}


void
cEntityGrid::SetGridDimensions( int iWidth, int iHeight, int iCellSize )
{
    mWidth = iWidth;
    mHeight = iHeight;
    mCellSize = iCellSize;

    ClearGrid();

    mGridMap.reserve( mWidth );
    for( int i = 0; i < mWidth; ++i )
    {
        mGridMap.push_back( std::vector< std::vector< ::nECS::cEntity* > >( mHeight ) );
    }

    // We remap every entities, as the grid is now changed in dimensions
    for( auto ent : mAllEntities )
    {
        SetEntityInGrid( ent );
    }
}


bool
cEntityGrid::IsEntityInGrid( const::nECS::cEntity * iEntity ) const
{
	for ( auto entity : mAllEntities )
	{
		if( entity == iEntity )
			return  true;
	}

	return  false;
}


void
cEntityGrid::SetEntityInGrid( ::nECS::cEntity* iEntity )
{
    if( !IsEntityValid( iEntity ) )
        return;

    int x, y, x2, y2;
    GetEntityArea( &x, &y, &x2, &y2, iEntity );

    // We crop so that entities that are part outside the grid and part inside can be treated
    int left = x     <   0 ? 0 : x;
    int top = y     <   0 ? 0 : y;
    int right = x2 >= mWidth - 1 ? mWidth - 1 : x2;
    int bottom = y2 >= mWidth - 1 ? mWidth - 1 : y2;


    // We store the pointer of iEntity in every cell that it is contained within, so we know at any time which entity should be considered
    // when looking for collision
    for( int i = left; i <= right; ++i )
    {
        for( int j = top; j <= bottom; ++j )
        {
			mEntityMap[ std::pair( i, j ) ].push_back( iEntity );
            mGridMap[ i ][ j ].push_back( iEntity );
        }
    }
}


void
cEntityGrid::ClearGrid()
{
    for( int i = 0; i <= mWidth; ++i )
    {
        for( int j = 0; j <= mHeight; ++j )
        {
			mEntityMap.clear();
            mGridMap[ i ][ j ].clear();
        }
    }
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------- Access/Get
// -------------------------------------------------------------------------------------


int
cEntityGrid::Width() const
{
    return  mWidth;
}


int
cEntityGrid::Height() const
{
    return  mHeight;
}


int
cEntityGrid::CellSize() const
{
    return  mCellSize;
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
			if( mEntityMap.find( std::pair( i, j ) ) == mEntityMap.end() )
				continue;

            for( int k = 0; k < mEntityMap[ std::pair( i, j ) ].size(); ++k )
            {
                if( mEntityMap[ std::pair( i, j ) ][ k ] == iEntity )
                {
                    mEntityMap[ std::pair( i, j ) ].erase( mEntityMap[ std::pair( i, j ) ].begin() + k );
                    mEntityMap.erase( std::pair( i, j ) );
                    //mGridMap[ i ][ j ].erase( mGridMap[ i ][ j ].begin() + k );
                    break; // iEntity should be present once per cell, no more, so when we found it --> NEXT
                }
            }
        }
    }

    for( int i = 0; i < mAllEntities.size(); ++i )
    {
        if( mAllEntities[ i ] == iEntity )
        {
            mAllEntities.erase( mAllEntities.begin() + i );
            break;
        }
    }

}


void
cEntityGrid::GetSurroundingEntitiesOf( std::vector< ::nECS::cEntity* >* oEntities, ::nECS::cEntity* iEntity, int iSurroundingSize )
{
    int x, y, x2, y2;
    GetEntityArea( &x, &y, &x2, &y2, iEntity );

    // We compute the enlarged rectangle that represent "iSurroundingSize cells distance"
    int left    = x - iSurroundingSize     <   0			? 0         : x - iSurroundingSize;
    int top     = y - iSurroundingSize     <   0			? 0         : y - iSurroundingSize;
    int right   = x2 + iSurroundingSize >=  mWidth -1		? mWidth -1 : x2 + iSurroundingSize;
    int bottom  = y2 + iSurroundingSize >=  mWidth -1		? mWidth -1 : y2 + iSurroundingSize;

    for( int i = left; i <= right; ++i )
    {
        for( int j = top; j <= bottom; ++j )
        {
			if( mEntityMap.find( std::pair( i, j ) ) == mEntityMap.end() )
				continue;

            for( int k = 0; k < mEntityMap[ std::pair( i, j ) ].size(); ++k )
            {
                ::nECS::cEntity* ent = mEntityMap[ std::pair( i, j ) ][ k ];
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
		if ( mEntityMap.find( std::pair( xLookupToInt, yLookupToInt ) ) != mEntityMap.end() )
		{
			for( int k = 0; k < mEntityMap[ std::pair( xLookupToInt, yLookupToInt ) ].size(); ++k )
			{
				::nECS::cEntity* ent = mEntityMap[ std::pair( xLookupToInt, yLookupToInt ) ][ k ];
				if( ent != iEntity && std::find( ( *oEntities ).begin(), ( *oEntities ).end(), ent ) == ( *oEntities ).end() )
					( *oEntities ).push_back( ent );
			}
		}

        xLookup += iVector.x;
        yLookup += iVector.y;
        xLookupToInt = int( xLookup );
        yLookupToInt = int( yLookup );
    }
}


void
cEntityGrid::GetEntitiesFollowingLineFromEntityToEntity( std::vector<::nECS::cEntity*>* oEntities, ::nECS::cEntity * iEntitySrc, ::nECS::cEntity * iEntityDst, const::nMath::cEdgeF & iLine )
{
    sf::Vector2f P1 = iLine.mPoint                      / float(mCellSize);
    sf::Vector2f P2 = (iLine.mPoint + iLine.mDirection) / float(mCellSize);

    float dX = P2.x - P1.x;
    float dY = P2.y - P1.y;

    if( abs( dX ) < kEpsilonF )
    {
        GetEntitiesFollowingVLineFromEntity( oEntities, iEntitySrc, iEntityDst, int(P1.y), int(P2.y), int(P2.x) );
        return;
    }

    if( abs( dY ) < kEpsilonF )
    {
        GetEntitiesFollowingHLineFromEntity( oEntities, iEntitySrc, iEntityDst, int( P1.x ), int( P2.x ), int( P2.y ) );
        return;
    }

    float slope = dY / dX;
    float constant = P2.y - ( slope * P2.x );

    if( abs( slope ) <= 1 )
    {
        for(  int i = int(std::min( P1.x, P2.x )); i < int(std::max( P1.x, P2.x )); ++i )
        {
            int resultY = int(( slope * i ) + constant);

			if ( mEntityMap.find( std::pair( i, resultY ) ) == mEntityMap.end() )
				continue;

            for( int k = 0; k < mEntityMap[ std::pair( i, resultY ) ].size(); ++k )
            {
                ::nECS::cEntity* ent = mEntityMap[ std::pair( i, resultY ) ][ k ];
                if( ent != iEntitySrc && ent != iEntityDst && std::find( ( *oEntities ).begin(), ( *oEntities ).end(), ent ) == ( *oEntities ).end() )
                    ( *oEntities ).push_back( ent );
            }
        }
    }
    else
    {
        for( int i = int(std::min( P1.y, P2.y )); i < int(std::max( P1.y, P2.y)); ++i )
        {
            int  resultX = int(( i - constant ) / slope);

			if ( mEntityMap.find( std::pair( resultX, i ) ) == mEntityMap.end() )
				continue;

            for( int k = 0; k < mEntityMap[ std::pair( resultX, i ) ].size(); ++k )
            {
                ::nECS::cEntity* ent = mEntityMap[ std::pair( resultX, i ) ][ k ];
                if( ent != iEntitySrc && ent != iEntityDst && std::find( ( *oEntities ).begin(), ( *oEntities ).end(), ent ) == ( *oEntities ).end() )
                    ( *oEntities ).push_back( ent );
            }
        }
    }
}


void
cEntityGrid::GetEntitiesFollowingHLineFromEntity( std::vector<::nECS::cEntity*>* oEntities, ::nECS::cEntity * iEntitySrc, ::nECS::cEntity * iEntityDst, int iP1X, int iP2X, int iPY )
{
    for( int i = iP1X; i < iP2X; ++i )
    {
        for( int k = 0; k < mGridMap[ i ][ iPY ].size(); ++k )
        {
			if ( mEntityMap.find( std::pair( i, iPY ) ) == mEntityMap.end() )
				continue;

            ::nECS::cEntity* ent = mEntityMap[ std::pair( i, iPY ) ][ k ];
            if( ent != iEntitySrc && ent != iEntityDst && std::find( ( *oEntities ).begin(), ( *oEntities ).end(), ent ) == ( *oEntities ).end() )
                ( *oEntities ).push_back( ent );
        }
    }
}


void
cEntityGrid::GetEntitiesFollowingVLineFromEntity( std::vector<::nECS::cEntity*>* oEntities, ::nECS::cEntity * iEntitySrc, ::nECS::cEntity * iEntityDst, int  iP1Y, int  iP2Y, int  iPX )
{
    for( int i = iP1Y; i < iP2Y; ++i )
    {
        for( int k = 0; k < mGridMap[ iPX ][ i ].size(); ++k )
        {
			if ( mEntityMap.find( std::pair( iPX, i) ) == mEntityMap.end() )
				continue;

            ::nECS::cEntity* ent = mEntityMap[ std::pair( iPX, i ) ][ k ];
            if( ent != iEntitySrc && ent != iEntityDst && std::find( ( *oEntities ).begin(), ( *oEntities ).end(), ent ) == ( *oEntities ).end() )
                ( *oEntities ).push_back( ent );
        }
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
			if ( mEntityMap.find( std::pair( i, j ) ) == mEntityMap.end() )
				continue;

            for( int k = 0; k < mEntityMap[ std::pair( i, j ) ].size(); ++k )
            {
                ::nECS::cEntity* ent = mEntityMap[ std::pair( i, j ) ][ k ];
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

