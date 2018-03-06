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
    std::vector< cEntity* > GetSurroundingEntitiesOf( cEntity* iEntity );
    std::vector< cEntity* > GetEntitiesFollwingVectorFromEntity( cEntity* iEntity, const sf::Vector2f& iVector );

private:
    // Private computing methods
    void GetEntityArea( int* oX, int* oY, int* oX2, int* oY2, cEntity* iEntity );

private:
    std::vector< std::vector< std::vector < cEntity* > > > mGridMap;
    int mWidth;     // Rows
    int mHeight;    // Columns
    int mCellSize;  // Being a square shape, only one size value needed
};
