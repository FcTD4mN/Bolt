#include "Core.Mapping.EntityMap.h"


#include "Core.ECS.Component.SimplePhysic.h"
#include "Core.ECS.Component.Transformation.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.Math.Utils.h"


namespace nCore {
namespace nMapping {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------- Contruction/Destruction
// -------------------------------------------------------------------------------------


cEntityMap::~cEntityMap()
{
}


cEntityMap::cEntityMap( int iWidth, int iHeight, int iCellSize ) :
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
cEntityMap::AddEntity( ::nCore::nECS::nCore::cEntity* iEntity )
{
    SetEntityInGrid( iEntity );

    mAllEntities.push_back( iEntity );
}


void
cEntityMap::RemoveEntity( ::nCore::nECS::nCore::cEntity * iEntity )
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
                    if( mEntityMap[ std::pair( i, j ) ].size() == 0 ) // To clear empty cells
                        mEntityMap.erase( std::pair( i, j ) );
                    break; // iEntity should be present once per cell, no more, so when we found it --> NEXT
                }
            }
        }
    }

    int vieuxCompteur = 0;
    for( auto ent : mAllEntities )
    {
        if( ent == iEntity )
        {
            mAllEntities.erase( mAllEntities.begin() + vieuxCompteur );
            break;
        }
        ++vieuxCompteur;
    }
}


void
cEntityMap::ClearEntityMap()
{
    ClearGrid();
    mAllEntities.clear();
}


void
cEntityMap::SetGridDimensions( int iWidth, int iHeight, int iCellSize )
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
cEntityMap::IsEntityInGrid( const::nCore::nECS::nCore::cEntity * iEntity ) const
{
    for( auto entity : mAllEntities )
    {
        if( entity == iEntity )
            return  true;
    }

    return  false;
}


void
cEntityMap::UpdateEntity( ::nCore::nECS::nCore::cEntity* iEntity )
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
            auto& cell = mEntityMap[ std::pair( i, j ) ];
            size_t cellSize = cell.size();

            for( int k = 0; k < cellSize; ++k )
            {
                if( cell[ k ] == iEntity )
                {
                    cell.erase( cell.begin() + k );
                    if( cell.size() == 0 )
                        mEntityMap.erase( std::pair( i, j ) );
                    break; // iEntity should be present once per cell, no more, so when we found it --> NEXT
                }
            }
        }
    }

#ifdef _DEBUG // Quick debugging spot, if dealing with one single entity in the map, you should never break on BP = 0, if you do, there is a leak in the map
    if( mEntityMap.size() > 0 )
        int BP = 0;
#endif

    SetEntityInGrid( iEntity );
}


void
cEntityMap::RemoveEntityHard( ::nCore::nECS::nCore::cEntity * iEntity )
{
    for( auto& cell : mEntityMap )
    {
        auto removedIterator = std::remove_if( cell.second.begin(),
                                                cell.second.end(),
                                                [ iEntity ] ( ::nCore::nECS::nCore::cEntity* iEnt )
                                                {
                                                    return  iEnt == iEntity;
                                                });

        if( removedIterator != cell.second.end() )
            cell.second.erase( removedIterator );
    }

    mAllEntities.erase( std::remove_if( mAllEntities.begin(),
                                        mAllEntities.end(),
                                        [ iEntity ] ( ::nCore::nECS::nCore::cEntity* iEnt )
                                        {
                                            return  iEnt == iEntity;
                                        }
    ) );
}


void
cEntityMap::SetEntityInGrid( ::nCore::nECS::nCore::cEntity* iEntity )
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
cEntityMap::ClearGrid()
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
cEntityMap::Width() const
{
    return  mWidth;
}


int
cEntityMap::Height() const
{
    return  mHeight;
}


int
cEntityMap::CellSize() const
{
    return  mCellSize;
}


void
cEntityMap::GetSurroundingEntitiesOf( std::set< ::nCore::nECS::nCore::cEntity* >* oEntities, ::nCore::nECS::nCore::cEntity* iEntity, int iSurroundingSize )
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
            auto& cell = mEntityMap[ std::pair( i, j ) ];
            size_t cellSize = cell.size();

            for( int k = 0; k < cellSize; ++k )
            {
                ::nCore::nECS::nCore::cEntity* ent = cell[ k ];
                if( ent != iEntity )
                    ( *oEntities ).insert( ent );
            }
        }
    }
}


void
cEntityMap::GetEntitiesFollwingVectorFromEntity( std::set< ::nCore::nECS::nCore::cEntity* >* oEntities, ::nCore::nECS::nCore::cEntity* iEntity, const sf::Vector2f & iVector )
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
            auto& cell = mEntityMap[ std::pair( xLookupToInt, yLookupToInt ) ];
            size_t cellSize = cell.size();

            for( int k = 0; k < cellSize; ++k )
            {
                ::nCore::nECS::nCore::cEntity* ent = cell[ k ];
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
cEntityMap::GetEntitiesFollowingLineFromEntityToEntity( std::set<::nCore::nECS::nCore::cEntity*>* oEntities, ::nCore::nECS::nCore::cEntity * iEntitySrc, ::nCore::nECS::nCore::cEntity * iEntityDst, const::nCore::nMath::cEdgeF & iLine )
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
            auto& cell = mEntityMap[ std::pair( i, resultY ) ];
            size_t cellSize = cell.size();

            for( int k = 0; k < cellSize; ++k )
            {
                ::nCore::nECS::nCore::cEntity* ent = cell[ k ];
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
            auto& cell = mEntityMap[ std::pair( resultX, i ) ];
            size_t cellSize = cell.size();

            for( int k = 0; k < cellSize; ++k )
            {
                ::nCore::nECS::nCore::cEntity* ent = cell[ k ];
                if( ent != iEntitySrc && ent != iEntityDst )
                    ( *oEntities ).insert( ent );
            }
        }
    }
}


void
cEntityMap::GetEntitiesFollowingHLineFromEntity( std::set<::nCore::nECS::nCore::cEntity*>* oEntities, ::nCore::nECS::nCore::cEntity * iEntitySrc, ::nCore::nECS::nCore::cEntity * iEntityDst, int iP1X, int iP2X, int iPY )
{
   // for( int i = iP1X; i < iP2X; ++i )
   // {
   //     for( int k = 0; k < mGridMap[ i ][ iPY ].size(); ++k )
   //     {
            //if ( mEntityMap.find( std::pair( i, iPY ) ) == mEntityMap.end() )
            //  continue;

   //         ::nCore::nECS::nCore::cEntity* ent = mEntityMap[ std::pair( i, iPY ) ][ k ];
   //         if( ent != iEntitySrc && ent != iEntityDst && std::find( ( *oEntities ).begin(), ( *oEntities ).end(), ent ) == ( *oEntities ).end() )
   //             ( *oEntities ).push_back( ent );
   //     }
   // }
}


void
cEntityMap::GetEntitiesFollowingVLineFromEntity( std::set<::nCore::nECS::nCore::cEntity*>* oEntities, ::nCore::nECS::nCore::cEntity * iEntitySrc, ::nCore::nECS::nCore::cEntity * iEntityDst, int  iP1Y, int  iP2Y, int  iPX )
{
   // for( int i = iP1Y; i < iP2Y; ++i )
   // {
   //     for( int k = 0; k < mGridMap[ iPX ][ i ].size(); ++k )
   //     {
            //if ( mEntityMap.find( std::pair( iPX, i) ) == mEntityMap.end() )
            //  continue;

   //         ::nCore::nECS::nCore::cEntity* ent = mEntityMap[ std::pair( iPX, i ) ][ k ];
   //         if( ent != iEntitySrc && ent != iEntityDst && std::find( ( *oEntities ).begin(), ( *oEntities ).end(), ent ) == ( *oEntities ).end() )
   //             ( *oEntities ).push_back( ent );
   //     }
   // }
}


void
cEntityMap::GetEntitiesInBoundingBox( std::set< ::nCore::nECS::nCore::cEntity*>* oEntities, const sf::Rect<float>& iBBox )
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
            auto& cell = mEntityMap[ std::pair( i, j ) ];
            size_t cellSize = cell.size();

            for( int k = 0; k < cellSize; ++k )
            {
                ::nCore::nECS::nCore::cEntity* ent = cell[ k ];
                ( *oEntities ).insert( ent );
            }
        }
    }
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------- Private computing methods
// -------------------------------------------------------------------------------------


void
cEntityMap::GetBBoxArea( int * oX, int * oY, int * oX2, int * oY2, const sf::Rect<float>& iBBox )
{
    GetBBoxArea( oX, oY, oX2, oY2, iBBox.left, iBBox.top, iBBox.left + iBBox.width, iBBox.top + iBBox.height );
}


void cEntityMap::GetBBoxArea( int * oX, int * oY, int * oX2, int * oY2, float iX, float iY, float iX2, float iY2 )
{
    *oX = int( iX ) / mCellSize;
    *oY = int( iY ) / mCellSize;

    *oX2 = int( iX2 ) / mCellSize + 1; // To grab the last cell as well
    *oY2 = int( iY2 ) / mCellSize + 1; // To grab the last cell as well
}


// ====================================================================================
// ====================================================================================
// ====================================================================================


cPhysicEntityMap::~cPhysicEntityMap()
{
}


cPhysicEntityMap::cPhysicEntityMap( int iWidth, int iHeight, int iCellSize ) :
    tSuperClass( iWidth, iHeight, iCellSize )
{
}


void
cPhysicEntityMap::GetEntityArea( int * oX, int * oY, int * oX2, int * oY2, ::nCore::nECS::nCore::cEntity * iEntity, eRelative iRelative )
{
    auto simplephysic = dynamic_cast< ::nCore::nECS::nComponent::cSimplePhysic* >( iEntity->GetComponentByID( "simplephysic" ) );
    auto transformation = dynamic_cast< ::nCore::nECS::nComponent::cTransformation* >( iEntity->GetComponentByID( "transformation" ) );

    if( !transformation || !simplephysic )
    {
        RemoveEntityHard( iEntity );
        *oX     = 0;
        *oX2    = 0;
        *oY     = 0;
        *oY2    = 0;
        return;
    }

    sf::Vector2f entityCenter = transformation->PositionAsVector2F() + transformation->SizeAsVector2F() / 2.0F;
    if( iRelative == kOldValue )
        entityCenter = transformation->PreviousPosition() + transformation->PreviousSize() / 2.0F;


    sf::FloatRect entityHitBox;
    entityHitBox = simplephysic->GetAbsoluteHitBoxUsingCenterPosition( entityCenter );

    tSuperClass::GetBBoxArea( oX, oY, oX2, oY2, entityHitBox.left, entityHitBox.top,
                              entityHitBox.left + entityHitBox.width, entityHitBox.top + entityHitBox.height );
}


bool cPhysicEntityMap::IsEntityValid( ::nCore::nECS::nCore::cEntity * iEntity ) const
{
    auto transformation = dynamic_cast< ::nCore::nECS::nComponent::cTransformation* >( iEntity->GetComponentByID( "transformation" ) );
    auto simplephysic = dynamic_cast< ::nCore::nECS::nComponent::cSimplePhysic* >( iEntity->GetComponentByID( "simplephysic" ) );
    if( !transformation || ! simplephysic )
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
cPositionSizeGrid::GetEntityArea( int * oX, int * oY, int * oX2, int * oY2, ::nCore::nECS::nCore::cEntity * iEntity, eRelative iRelative )
{
    auto transformation = dynamic_cast< ::nCore::nECS::nComponent::cTransformation* >( iEntity->GetComponentByID( "transformation" ) );

    if( !transformation )
    {
        RemoveEntityHard( iEntity );
        return;
    }

    double x = transformation->X();
    double y = transformation->Y();
    double w = transformation->W();
    double h = transformation->H();

    if ( iRelative == kOldValue )
    {
        x = transformation->PreviousPosition().x;
        y = transformation->PreviousPosition().y;
        w = transformation->PreviousSize().x;
        h = transformation->PreviousSize().y;
    }

    tSuperClass::GetBBoxArea( oX, oY, oX2, oY2, float(x), float(y), float(x + w), float(y + h ) );
}


bool
cPositionSizeGrid::IsEntityValid( ::nCore::nECS::nCore::cEntity * iEntity ) const
{
    auto transformation = dynamic_cast< ::nCore::nECS::nComponent::cTransformation* >( iEntity->GetComponentByID( "transformation" ) );
    if( !transformation )
        return  false;

    return  true;
}


} // namespace nMapping
} // namespace nCore

