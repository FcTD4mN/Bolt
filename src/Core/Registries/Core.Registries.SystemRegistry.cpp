#include "Core.Registries.SystemRegistry.h"


#include "Core.Application.GlobalAccess.h"
#include "Core.ECS.Core.System.h"
#include "Core.ECS.System.AnimationRenderer.h"
#include "Core.ECS.System.InputConverter.h"
#include "Core.ECS.System.SimplerRenderer.h"
#include "Core.ECS.System.SimplePhysics.h"
#include "Core.ECS.System.SightSystem.h"
#include "Core.ECS.System.SoundMixer.h"
#include "Core.ECS.System.SoundOcclusion.h"
#include "Core.ECS.System.BehaviourTreeSystem.h"

#include <tinyxml2.h>
#include <algorithm>


namespace nCore {
namespace nRegistries {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cSystemRegistry::~cSystemRegistry()
{
}


cSystemRegistry::cSystemRegistry()
{
}


// -------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------- Instance
// -------------------------------------------------------------------------------------


cSystemRegistry*
cSystemRegistry::Instance()
{
    static cSystemRegistry* sgSystemsRegistry = 0;
    if( !sgSystemsRegistry )
        sgSystemsRegistry = new cSystemRegistry();

    return  sgSystemsRegistry;
}


::nCore::nECS::nCore::cSystem*
cSystemRegistry::CreateSystemFromName( const std::string & iName )
{
    return  mItems[ iName ].mItem->Clone();
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cSystemRegistry::Initialize()
{
    // Registering all basic systems
    RegisterItem( "AnimationRenderer", new ::nCore::nECS::nSystem::cAnimationRenderer(), "void" );
    RegisterItem( "BehaviourTreeSystem", new ::nCore::nECS::nSystem::cBehaviourTreeSystem(), "void" );
    RegisterItem( "InputConverter", new ::nCore::nECS::nSystem::cInputConverter(), "void" );
    RegisterItem( "SightSystem", new ::nCore::nECS::nSystem::cSightSystem(), "void" );
    RegisterItem( "SimplePhysics", new ::nCore::nECS::nSystem::cSimplePhysics(), "void" );
    RegisterItem( "SimpleRenderer", new ::nCore::nECS::nSystem::cSimplerRenderer(), "void" );
    RegisterItem( "SoundMixer", new ::nCore::nECS::nSystem::cSoundMixer(), "void" );
    RegisterItem( "SoundOcclusion", new ::nCore::nECS::nSystem::cSoundOcclusion(), "void" );

    //TODO:
    // Parsing file based systems
    // Then we get all file based components
    nStdFileSystem::path systemDir = PROJECTDIR + "/Assets/Systems/";
    if( nStdFileSystem::exists( systemDir ) )
    {
        nStdFileSystem::directory_iterator end{};
        tinyxml2::XMLDocument doc;

        for( nStdFileSystem::directory_iterator it { systemDir }; it != end; ++it )
        {
            if( nStdFileSystem::is_regular_file( *it ) )
            {
                tinyxml2::XMLError error = doc.LoadFile( it->path().string().c_str() );
                if( error )
                    continue;

                // This will be SystemPython instead of SystemGeneric
                //cSystemGeneric* system = new cSystemGeneric( it->path().string().c_str() );
                //System->LoadXML( doc.FirstChildElement( "system" ) );
                //RegisterItem( system->Name(), system );
                //SetItemFileUsingItemName( system->Name(), it->path() );
                //doc.Clear();
            }
        }
    }
}


void
cSystemRegistry::Finalize()
{
    for( auto it = mItems.begin(); it != mItems.end(); ++it )
        delete  it->second.mItem;

    mItems.clear();
}


} // namespace nRegistries
} // namespace nCore

