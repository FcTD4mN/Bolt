#pragma once

#include <vector>

class cEntity;

class cEntityGrid
{
public:
    // Contruction/Destruction
    ~cEntityGrid();
    cEntityGrid();

public:
    // Grid management
    void AddObject( cEntity* iObject );
    std::vector< cEntity* > GetSurroundingEntitiesOf( cEntity* iEntity );

private:
    std::vector< std::vector< std::vector < cEntity* > > > mGridMap;
    int mWidth;     // Rows
    int mHeight;    // Columns
    int mCellSize;  // Being a square shape, only one size value needed
};
