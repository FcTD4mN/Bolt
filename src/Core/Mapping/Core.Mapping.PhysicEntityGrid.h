#pragma once

#include "Core.Math.Edge.h"

#include <SFML/Graphics.hpp>


#include <vector>
#include <unordered_map>
#include <set>


namespace nECS { class cEntity; }


namespace nMapping {


// HASH FUNCTIONS
template <class T>
inline
void
hash_combine( std::size_t & seed, const T & v )
{
	std::hash< T > hasher;
	seed ^= hasher( v ) + 0x9e3779b9 + ( seed << 6 ) + ( seed >> 2 );
}


template<typename S, typename T>
struct
std::hash< std::pair< S, T > >
{
	inline size_t operator()( const std::pair< S, T >& v ) const
	{
		size_t seed = 0;
		::nMapping::hash_combine( seed, v.first );
		::nMapping::hash_combine( seed, v.second );
		return  seed;
	}
};


// ===================================
// ===================================


class cEntityGrid
{
protected:
	enum eRelative
	{
		kOldValue,
		kCurrentValue
	};

public:
    // Contruction/Destruction
    ~cEntityGrid();
    cEntityGrid( int iWidth, int iHeight, int iCellSize );

public:
    // Grid management
    void AddEntity( ::nECS::cEntity* iEntity );
    void RemoveEntity( ::nECS::cEntity* iEntity );
    void ClearEntityMap();
    void SetGridDimensions( int iWidth, int iHeight, int iCellSize );
	bool IsEntityInGrid( const ::nECS::cEntity* iEntity ) const;
    void UpdateEntity( ::nECS::cEntity* iEntity );

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
    void GetSurroundingEntitiesOf( std::set<::nECS::cEntity*>* oEntities, ::nECS::cEntity* iEntity, int iSurroundingSize );
    void GetEntitiesFollwingVectorFromEntity( std::set<::nECS::cEntity*>* oEntities, ::nECS::cEntity* iEntity, const sf::Vector2f& iVector );
    void GetEntitiesFollowingLineFromEntityToEntity( std::set<::nECS::cEntity*>* oEntities, ::nECS::cEntity* iEntitySrc, ::nECS::cEntity* iEntityDst, const ::nMath::cEdgeF& iLine );

private:
    void GetEntitiesFollowingHLineFromEntity( std::set<::nECS::cEntity*>* oEntities, ::nECS::cEntity* iEntitySrc, ::nECS::cEntity * iEntityDst, int iP1X, int iP2X, int iPY );
    void GetEntitiesFollowingVLineFromEntity( std::set<::nECS::cEntity*>* oEntities, ::nECS::cEntity* iEntitySrc, ::nECS::cEntity * iEntityDst, int iP1Y, int iP2Y, int iPX );

public:
    void GetEntitiesInBoundingBox( std::set<::nECS::cEntity*>* oEntities, const sf::Rect< float >& iBBox );

protected:
    // Private computing methods
    virtual  void   GetEntityArea( int* oX, int* oY, int* oX2, int* oY2, ::nECS::cEntity* iEntity, eRelative iRelative ) = 0;
    virtual  bool   IsEntityValid( ::nECS::cEntity* iEntity ) const = 0;
    void            GetBBoxArea( int* oX, int* oY, int* oX2, int* oY2, const sf::Rect< float >& iBBox );
    void            GetBBoxArea( int* oX, int* oY, int* oX2, int* oY2, float iX, float iY, float iX2, float iY2 );

private:
	std::unordered_map< std::pair< int, int >, std::vector< ::nECS::cEntity* > >	mEntityMap;
    std::vector< ::nECS::cEntity* >													mAllEntities;	// This allows the grid to know all entities inside without having to go throught the actual grid
    int																				mWidth;			// Rows
    int																				mHeight;		// Columns
    int																				mCellSize;		// Being a square shape, only one size value needed

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
    virtual  void GetEntityArea( int* oX, int* oY, int* oX2, int* oY2, ::nECS::cEntity* iEntity, eRelative iRelative ) override;
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
    virtual  void GetEntityArea( int* oX, int* oY, int* oX2, int* oY2, ::nECS::cEntity* iEntity, eRelative iRelative ) override;
    virtual  bool IsEntityValid( ::nECS::cEntity* iEntity ) const override;

};


} // namespace nMapping

