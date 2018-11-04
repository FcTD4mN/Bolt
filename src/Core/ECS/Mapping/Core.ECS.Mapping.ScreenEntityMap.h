//#pragma once
//
//
//#include <tinyxml2.h>
//
//
//#include <unordered_map>
//#include <vector>
//
//
//namespace nCore { namespace nMapping { class cEntityGrid; } }
//
//
//namespace nCore {
//namespace nECS {
//namespace nMapping {
//
//
//// Going for singleton, because i would imagine in the future, some games will require other structures
//// and we'll need a map generic concept, that basically, allows to query for entities
//class cScreenEntityMap
//{
//public:
//    // Contruction/Destruction
//    ~cScreenEntityMap();
//    cScreenEntityMap();
//
//public:
//    static cScreenEntityMap* Instance();
//
//public:
//    // Init/Finalize
//    void Initialize( int iWidth, int iHeight, int iCellSize );
//    void Finalize();
//
//public:
//    ::nCore::nMapping::cEntityGrid*  mEntityGrid;
//};
//
//
//} // namespace nMapping
//} // namespace nECS
//} // namespace nCore
//
