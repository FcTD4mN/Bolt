#pragma once

#include "Core.Math.Edge.h"

#include <SFML/Graphics.hpp>


#include <vector>


namespace nECS { class cEntity; }


namespace nMapping {


class cEntityGrid
{
public:
    // Contruction/Destruction
    ~cEntityGrid();
    cEntityGrid( int iWidth, int iHeight, int iCellSize );

public:
    // Grid management
    void AddEntity( ::nECS::cEntity* iEntity );
    void ClearEntityMap();
    void SetGridDimensions( int iWidth, int iHeight, int iCellSize );
private:
    void SetEntityInGrid( ::nECS::cEntity* iEntity );

private:
    void ClearGrid();

public:
    // Access/Get
    int Width() const;
    int Height() const;
    int CellSize() const;

public:
        // This asssumes that iEntity still has the same position as when it was added
        // It allows for a fast removal
    void RemoveEntityNotUpdated( ::nECS::cEntity* iEntity );
    void GetSurroundingEntitiesOf( std::vector<::nECS::cEntity*>* oEntities, ::nECS::cEntity* iEntity, int iSurroundingSize );
    void GetEntitiesFollwingVectorFromEntity( std::vector<::nECS::cEntity*>* oEntities, ::nECS::cEntity* iEntity, const sf::Vector2f& iVector );
    void GetEntitiesFollowingLineFromEntityToEntity( std::vector<::nECS::cEntity*>* oEntities, ::nECS::cEntity* iEntitySrc, ::nECS::cEntity* iEntityDst, const ::nMath::cEdgeF& iLine );

private:
    void GetEntitiesFollowingHLineFromEntity( std::vector<::nECS::cEntity*>* oEntities, ::nECS::cEntity* iEntitySrc, ::nECS::cEntity * iEntityDst, int iP1X, int iP2X, int iPY );
    void GetEntitiesFollowingVLineFromEntity( std::vector<::nECS::cEntity*>* oEntities, ::nECS::cEntity* iEntitySrc, ::nECS::cEntity * iEntityDst, int iP1Y, int iP2Y, int iPX );

public:
    void GetEntitiesInBoundingBox( std::vector<::nECS::cEntity*>* oEntities, const sf::Rect< float >& iBBox );

protected:
    // Private computing methods
    virtual  void   GetEntityArea( int* oX, int* oY, int* oX2, int* oY2, ::nECS::cEntity* iEntity ) = 0;
    virtual  bool   IsEntityValid( ::nECS::cEntity* iEntity ) const = 0;
    void            GetBBoxArea( int* oX, int* oY, int* oX2, int* oY2, const sf::Rect< float >& iBBox );
    void            GetBBoxArea( int* oX, int* oY, int* oX2, int* oY2, float iX, float iY, float iX2, float iY2 );

private:
    std::vector< std::vector< std::vector < ::nECS::cEntity* > > >  mGridMap;
    std::vector< ::nECS::cEntity* >                                 mAllEntities; // This allows the grid to know all entities inside without having to go throught the actual grid
    int                                                             mWidth;     // Rows
    int                                                             mHeight;    // Columns
    int                                                             mCellSize;  // Being a square shape, only one size value needed

};


//========================
//========================
//========================


class cPhysicEntityGrid :
    public cEntityGrid
{
public:
    typedef  cEntityGrid  tSuperClass;

public:
    // Contruction/Destruction
    ~cPhysicEntityGrid();
    cPhysicEntityGrid( int iWidth, int iHeight, int iCellSize );

protected:
    // Private computing methods
    virtual  void GetEntityArea( int* oX, int* oY, int* oX2, int* oY2, ::nECS::cEntity* iEntity ) override;
    virtual  bool IsEntityValid( ::nECS::cEntity* iEntity ) const override;

};


//========================
//========================
//========================


class cPositionSizeGrid :
    public cEntityGrid
{
public:
    typedef  cEntityGrid  tSuperClass;

public:
    // Contruction/Destruction
    ~cPositionSizeGrid();
    cPositionSizeGrid( int iWidth, int iHeight, int iCellSize );

protected:
    // Private computing methods
    virtual  void GetEntityArea( int* oX, int* oY, int* oX2, int* oY2, ::nECS::cEntity* iEntity ) override;
    virtual  bool IsEntityValid( ::nECS::cEntity* iEntity ) const override;

};


} // namespace nMapping

