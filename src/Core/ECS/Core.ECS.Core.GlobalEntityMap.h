#pragma once

#include <vector>

namespace nMapping { class cEntityGrid; }

namespace nECS {


class cGlobalEntityMap
{
public:
    // Contruction/Destruction
    ~cGlobalEntityMap();
    cGlobalEntityMap();

public:
    static cGlobalEntityMap* Instance();

public:
    // Init/Finalize
    void Initialize( int iWidth, int iHeight, int iCellSize );
    void Finalize();

public:
    ::nMapping::cEntityGrid*  mEntityGrid;
};

} //nECS

