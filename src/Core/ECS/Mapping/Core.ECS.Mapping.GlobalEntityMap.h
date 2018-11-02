#pragma once

#include <vector>


namespace nCore { namespace nMapping { class cEntityGrid; } }


namespace nCore {
namespace nECS {
namespace nMapping {


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
    ::nCore::nMapping::cEntityGrid*  mEntityGrid;
};


} // namespace nMapping
} // namespace nECS
} // namespace nCore

