#include "Core.Registries.EntityRegistry.h"


#include "Core.Application.GlobalAccess.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"


#include <SFML/System.hpp>
#include <tinyxml2.h>


namespace nCore {
namespace nRegistries {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cEntityRegistry::~cEntityRegistry()
{
}


cEntityRegistry::cEntityRegistry()
{
}


// -------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------- Instance
// -------------------------------------------------------------------------------------


// static
cEntityRegistry*
    cEntityRegistry::Instance()
{
    static cEntityRegistry* sgEntityParser = 0;
    if( !sgEntityParser )
        sgEntityParser = new cEntityRegistry();

    return  sgEntityParser;
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------- Initialize/Finalize
// -------------------------------------------------------------------------------------


void
cEntityRegistry::Initialize()
{
    ParseFolder();
}


void
cEntityRegistry::Finalize()
{
    for( auto it = mItems.begin(); it != mItems.end(); ++it )
        delete  it->second.mItem;

    mItems.clear();
}


void
cEntityRegistry::ParseFolder()
{
    nStdFileSystem::path entityPath = PROJECTDIR + "/Assets/Entities/";
    if( nStdFileSystem::exists( entityPath ) )
    {
        nStdFileSystem::directory_iterator end{};
        tinyxml2::XMLDocument doc;

        for( nStdFileSystem::directory_iterator it { entityPath }; it != end; ++it )
        {
            if( nStdFileSystem::is_regular_file( *it ) )
            {
                tinyxml2::XMLError error = doc.LoadFile( it->path().string().c_str() );
                if( error )
                    continue;

                auto* entity = new ::nCore::nECS::nCore::cEntity();
                entity->LoadXML( doc.FirstChildElement( "entity" ) );

                RegisterItem( entity->ID(), entity, it->path() );
                doc.Clear();
            }
        }
    }
}


// -------------------------------------------------------------------------------------
// --------------------------------------------------------------------------- Functions
// -------------------------------------------------------------------------------------


::nCore::nECS::nCore::cEntity*
cEntityRegistry::CreateEntityFromFile( const std::string& iFile, ::nCore::nECS::nCore::cWorld* iWorld )
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.LoadFile( iFile.c_str() );
    if( error )
        return  0;

    auto* entity = new ::nCore::nECS::nCore::cEntity();
    entity->LoadXML( doc.FirstChildElement( "entity" ) );

    return  entity;
}


::nCore::nECS::nCore::cEntity*
cEntityRegistry::CreateEntityFromPrototypeMap( const std::string& iEntityName )
{
    ::nCore::nECS::nCore::cEntity* proto = mItems[ iEntityName ].mItem;
    if( proto )
        return  proto->Clone();

    return  0;
}


bool
cEntityRegistry::IsIDAvailable( const std::string& iID )
{
    if( !IsItemNameAlreadyInRegistry( iID ) )
        return  true;

     if( mItems[ iID ].mItem == nullptr )
         return  true;

    return  false;
}


} // namespace nRegistries
} // namespace nCore

