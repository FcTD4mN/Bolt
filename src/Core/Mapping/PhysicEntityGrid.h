#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

class cEntity;

class cEntityGrid
{
public:
    // Contruction/Destruction
    ~cEntityGrid();
    cEntityGrid();

public:
    // Grid management
    void AddEntity( cEntity* iEntity );

        // This asssumes that iEntity still has the same position as when it was added
        // It allows for a fast removal
    void RemoveEntityNotUpdated( cEntity* iEntity );
    void GetSurroundingEntitiesOf( std::vector<cEntity*>* oEntities, cEntity* iEntity );
    void GetEntitiesFollwingVectorFromEntity( std::vector<cEntity*>* oEntities, cEntity* iEntity, const sf::Vector2f& iVector );

    void GetEntitiesInBoundingBox( std::vector<cEntity*>* oEntities, const sf::Rect< float >& iBBox );

private:
    // Private computing methods
    void GetEntityArea( int* oX, int* oY, int* oX2, int* oY2, cEntity* iEntity );
    void GetBBoxArea( int* oX, int* oY, int* oX2, int* oY2, const sf::Rect< float >& iBBox );
    void GetBBoxArea( int* oX, int* oY, int* oX2, int* oY2, float iX, float iY, float iX2, float iY2 );

private:
    std::vector< std::vector< std::vector < cEntity* > > > mGridMap;
    int mWidth;     // Rows
    int mHeight;    // Columns
    int mCellSize;  // Being a square shape, only one size value needed
};
