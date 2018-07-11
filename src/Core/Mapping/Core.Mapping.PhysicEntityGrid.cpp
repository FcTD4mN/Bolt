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
	mEntityMap(),
    mWidth( iWidth ),
    mHeight( iHeight ),
    mCellSize( iCellSize )
{
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
cEntityGrid::RemoveEntity( ::nECS::cEntity * iEntity )
{
	int x, y, x2, y2;
	GetEntityArea( &x, &y, &x2, &y2, iEntity, kCurrentValue );

	for( int i = x; i <= x2; ++i )
	{
		for( int j = y; j <= y2; ++j )
		{
			if( mEntityMap.find( std::pair( i, j ) ) == mEntityMap.end() )
				continue;

			for( int k = 0; k < mEntityMap[ std::pair( i, j ) ].size(); ++k )
			{
				if( mEntityMap[ std::pair( i, j ) ][ k ] == iEntity )
				{
					mEntityMap[ std::pair( i, j ) ].erase( mEntityMap[ std::pair( i, j ) ].begin() + k );
					mEntityMap.erase( std::pair( i, j ) );
					break; // iEntity should be present once per cell, no more, so when we found it --> NEXT
				}
			}
		}
	}
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

    // We remap every entities, as the grid is now changed in dimensions
    for( auto ent : mAllEntities )
    {
        SetEntityInGrid( ent );
    }
}


bool
cEntityGrid::IsEntityInGrid( const::nECS::cEntity * iEntity ) const
{
	for( auto entity : mAllEntities )
	{
		if( entity == iEntity )
			return  true;
	}

	return  false;
}


void
cEntityGrid::UpdateEntity( ::nECS::cEntity* iEntity )
{
	int x, y, x2, y2;
	GetEntityArea( &x, &y, &x2, &y2, iEntity, kOldValue );

	for( int i = x; i <= x2; ++i )
	{
		for( int j = y; j <= y2; ++j )
		{
			if( mEntityMap.find( std::pair( i, j ) ) == mEntityMap.end() )
				continue;

			// Pre storing them so we access only once to mEntityMap[ std::pair( i, j ) ], which is very cost heavy,
			// and we only compute size once, which is not the lightest on an unorderd map
			auto cell = mEntityMap[ std::pair( i, j ) ];
			size_t cellSize = cell.size();

			for( int k = 0; k < cellSize; ++k )
			{
				if( cell[ k ] == iEntity )
				{
					cell.erase( cell.begin() + k );
					mEntityMap.erase( std::pair( i, j ) );
					break; // iEntity should be present once per cell, no more, so when we found it --> NEXT
				}
			}
		}
	}

	SetEntityInGrid( iEntity );
}


void
cEntityGrid::RemoveEntityHard( ::nECS::cEntity * iEntity )
{
	for( auto cell : mEntityMap )
	{
		auto removedIterator = std::remove_if( cell.second.begin(),
						cell.second.end(),
						[ iEntity ] ( ::nECS::cEntity* iEnt )
		{
							return  iEnt == iEntity;
		});

		if( removedIterator != cell.second.end() )
			cell.second.erase( removedIterator );
	}

	mAllEntities.erase(
						std::remove_if( mAllEntities.begin(),
										mAllEntities.end(),
										[ iEntity ] ( ::nECS::cEntity* iEnt )
										{
											return  iEnt == iEntity;
										}
	) );
}


void
cEntityGrid::SetEntityInGrid( ::nECS::cEntity* iEntity )
{
    if( !IsEntityValid( iEntity ) )
        return;

    int x, y, x2, y2;
    GetEntityArea( &x, &y, &x2, &y2, iEntity, kCurrentValue );

    // We store the pointer of iEntity in every cell that it is contained within, so we know at any time which entity should be considered
    // when looking for collision
    for( int i = x; i <= x2; ++i )
    {
        for( int j = y; j <= y2; ++j )
        {
			mEntityMap[ std::pair( i, j ) ].push_back( iEntity );
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
cEntityGrid::GetSurroundingEntitiesOf( std::set< ::nECS::cEntity* >* oEntities, ::nECS::cEntity* iEntity, int iSurroundingSize )
{
    int x, y, x2, y2;
    GetEntityArea( &x, &y, &x2, &y2, iEntity, kCurrentValue );

    for( int i = x; i <= x2; ++i )
    {
        for( int j = y; j <= y2; ++j )
        {
			if( mEntityMap.find( std::pair( i, j ) ) == mEntityMap.end() )
				continue;

			// Pre storing them so we access only once to mEntityMap[ std::pair( i, j ) ], which is very cost heavy,
			// and we only compute size once, which is not the lightest on an unorderd map
			auto cell = mEntityMap[ std::pair( i, j ) ];
			size_t cellSize = cell.size();

            for( int k = 0; k < cellSize; ++k )
            {
                ::nECS::cEntity* ent = cell[ k ];
				if( ent != iEntity )
					( *oEntities ).insert( ent );
            }
        }
    }
}


void
cEntityGrid::GetEntitiesFollwingVectorFromEntity( std::set< ::nECS::cEntity* >* oEntities, ::nECS::cEntity* iEntity, const sf::Vector2f & iVector )
{
    int x, y, x2, y2;
    GetEntityArea( &x, &y, &x2, &y2, iEntity, kCurrentValue );

    float xLookup = float(x);
    float yLookup = float(y);
    int  xLookupToInt = int( xLookup );
    int  yLookupToInt = int( yLookup );

    while( xLookupToInt >= 0 && yLookupToInt >= 0 && xLookupToInt < mWidth && yLookupToInt < mHeight )
    {
		if ( mEntityMap.find( std::pair( xLookupToInt, yLookupToInt ) ) != mEntityMap.end() )
		{
			// Pre storing them so we access only once to mEntityMap[ std::pair( i, j ) ], which is very cost heavy,
			// and we only compute size once, which is not the lightest on an unorderd map
			auto cell = mEntityMap[ std::pair( xLookupToInt, yLookupToInt ) ];
			size_t cellSize = cell.size();

			for( int k = 0; k < cellSize; ++k )
			{
				::nECS::cEntity* ent = cell[ k ];
				if( ent != iEntity )
					( *oEntities ).insert( ent );
			}
		}

        xLookup += iVector.x;
        yLookup += iVector.y;
        xLookupToInt = int( xLookup );
        yLookupToInt = int( yLookup );
    }
}


void
cEntityGrid::GetEntitiesFollowingLineFromEntityToEntity( std::set<::nECS::cEntity*>* oEntities, ::nECS::cEntity * iEntitySrc, ::nECS::cEntity * iEntityDst, const::nMath::cEdgeF & iLine )
{
    sf::Vector2f P1 = iLine.mPoint                      / float(mCellSize);
    sf::Vector2f P2 = (iLine.mPoint + iLine.mDirection) / float(mCellSize);

    float dX = P2.x - P1.x;
    float dY = P2.y - P1.y;

    if( std::abs( dX ) < kEpsilonF )
    {
        GetEntitiesFollowingVLineFromEntity( oEntities, iEntitySrc, iEntityDst, int(P1.y), int(P2.y), int(P2.x) );
        return;
    }

    if( std::abs( dY ) < kEpsilonF )
    {
        GetEntitiesFollowingHLineFromEntity( oEntities, iEntitySrc, iEntityDst, int( P1.x ), int( P2.x ), int( P2.y ) );
        return;
    }

    float slope = dY / dX;
    float constant = P2.y - ( slope * P2.x );

    if( std::abs( slope ) <= 1 )
    {
        for(  int i = int(std::min( P1.x, P2.x )); i < int(std::max( P1.x, P2.x )); ++i )
        {
            int resultY = int(( slope * i ) + constant);

			if ( mEntityMap.find( std::pair( i, resultY ) ) == mEntityMap.end() )
				continue;

			// Pre storing them so we access only once to mEntityMap[ std::pair( i, j ) ], which is very cost heavy,
			// and we only compute size once, which is not the lightest on an unorderd map
			auto cell = mEntityMap[ std::pair( i, resultY ) ];
			size_t cellSize = cell.size();

            for( int k = 0; k < cellSize; ++k )
            {
                ::nECS::cEntity* ent = cell[ k ];
				if( ent != iEntitySrc && ent != iEntityDst )
					( *oEntities ).insert( ent );
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

			// Pre storing them so we access only once to mEntityMap[ std::pair( i, j ) ], which is very cost heavy,
			// and we only compute size once, which is not the lightest on an unorderd map
			auto cell = mEntityMap[ std::pair( resultX, i ) ];
			size_t cellSize = cell.size();

            for( int k = 0; k < cellSize; ++k )
            {
                ::nECS::cEntity* ent = cell[ k ];
				if( ent != iEntitySrc && ent != iEntityDst )
					( *oEntities ).insert( ent );
            }
        }
    }
}


void
cEntityGrid::GetEntitiesFollowingHLineFromEntity( std::set<::nECS::cEntity*>* oEntities, ::nECS::cEntity * iEntitySrc, ::nECS::cEntity * iEntityDst, int iP1X, int iP2X, int iPY )
{
   // for( int i = iP1X; i < iP2X; ++i )
   // {
   //     for( int k = 0; k < mGridMap[ i ][ iPY ].size(); ++k )
   //     {
			//if ( mEntityMap.find( std::pair( i, iPY ) ) == mEntityMap.end() )
			//	continue;

   //         ::nECS::cEntity* ent = mEntityMap[ std::pair( i, iPY ) ][ k ];
   //         if( ent != iEntitySrc && ent != iEntityDst && std::find( ( *oEntities ).begin(), ( *oEntities ).end(), ent ) == ( *oEntities ).end() )
   //             ( *oEntities ).push_back( ent );
   //     }
   // }
}


void
cEntityGrid::GetEntitiesFollowingVLineFromEntity( std::set<::nECS::cEntity*>* oEntities, ::nECS::cEntity * iEntitySrc, ::nECS::cEntity * iEntityDst, int  iP1Y, int  iP2Y, int  iPX )
{
   // for( int i = iP1Y; i < iP2Y; ++i )
   // {
   //     for( int k = 0; k < mGridMap[ iPX ][ i ].size(); ++k )
   //     {
			//if ( mEntityMap.find( std::pair( iPX, i) ) == mEntityMap.end() )
			//	continue;

   //         ::nECS::cEntity* ent = mEntityMap[ std::pair( iPX, i ) ][ k ];
   //         if( ent != iEntitySrc && ent != iEntityDst && std::find( ( *oEntities ).begin(), ( *oEntities ).end(), ent ) == ( *oEntities ).end() )
   //             ( *oEntities ).push_back( ent );
   //     }
   // }
}


void
cEntityGrid::GetEntitiesInBoundingBox( std::set< ::nECS::cEntity*>* oEntities, const sf::Rect<float>& iBBox )
{
    int x, y, x2, y2;
    GetBBoxArea( &x, &y, &x2, &y2, iBBox );

    for( int i = x; i < x2; ++i )
    {
        for( int j = y; j < y2; ++j )
        {
			if ( mEntityMap.find( std::pair( i, j ) ) == mEntityMap.end() )
				continue;

			// Pre storing them so we access only once to mEntityMap[ std::pair( i, j ) ], which is very cost heavy,
			// and we only compute size once, which is not the lightest on an unorderd map
			auto cell = mEntityMap[ std::pair( i, j ) ];
			size_t cellSize = cell.size();

            for( int k = 0; k < cellSize; ++k )
            {
                ::nECS::cEntity* ent = cell[ k ];
                ( *oEntities ).insert( ent );
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
cPhysicEntityGrid::GetEntityArea( int * oX, int * oY, int * oX2, int * oY2, ::nECS::cEntity * iEntity, eRelative iRelative )
{
    auto simplephysic = dynamic_cast< ::nECS::cSimplePhysic* >( iEntity->GetComponentByName( "simplephysic" ) );
    auto position = dynamic_cast< ::nECS::cPosition* >( iEntity->GetComponentByName( "position" ) );
    auto size = dynamic_cast< ::nECS::cSize* >( iEntity->GetComponentByName( "size" ) );

	if( !position || !simplephysic )
	{
		RemoveEntityHard( iEntity );
		*oX		= 0;
		*oX2	= 0;
		*oY		= 0;
		*oY2	= 0;
		return;
	}

    sf::Vector2f entityCenter = position->AsVector2F();
	if( iRelative == kOldValue )
		entityCenter = position->PreviousPosition();

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
cPositionSizeGrid::GetEntityArea( int * oX, int * oY, int * oX2, int * oY2, ::nECS::cEntity * iEntity, eRelative iRelative )
{
    auto position = dynamic_cast< ::nECS::cPosition* >( iEntity->GetComponentByName( "position" ) );

	if( !position )
	{
		RemoveEntityHard( iEntity );
		return;
	}

    double x = position->X();
    double y = position->Y();
	if ( iRelative == kOldValue )
	{
		x = position->PreviousPosition().x;
		y = position->PreviousPosition().y;
	}

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

