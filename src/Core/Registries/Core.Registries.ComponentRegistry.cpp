#include "Core.Registries.ComponentRegistry.h"


#include "Core.ECS.Core.Component.h"
#include "Core.ECS.Component.Animations.h"
#include "Core.ECS.Component.BehaviourTree.h"
#include "Core.ECS.Component.Color.h"
#include "Core.ECS.Component.Direction.h"
#include "Core.ECS.Component.FieldOfView.h"
#include "Core.ECS.Component.OcclusionFactor.h"
#include "Core.ECS.Component.SimplePhysic.h"
#include "Core.ECS.Component.Sound.h"
#include "Core.ECS.Component.Text.h"
#include "Core.ECS.Component.Transformation.h"
#include "Core.ECS.Component.UserInput.h"
#include "Core.Application.GlobalAccess.h"


#include <algorithm>


namespace nCore {
namespace nRegistries {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cComponentRegistry::~cComponentRegistry()
{
}


cComponentRegistry::cComponentRegistry()
{
}


// -------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------- Instance
// -------------------------------------------------------------------------------------


cComponentRegistry*
cComponentRegistry::Instance()
{
    static cComponentRegistry* sgComponentsRegistry = 0;
    if( !sgComponentsRegistry )
        sgComponentsRegistry = new cComponentRegistry();

    return  sgComponentsRegistry;
}


::nCore::nECS::nCore::cComponent*
cComponentRegistry::CreateComponentFromName( const std::string & iName )
{
    return  GetItemByName( iName )->Clone();
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cComponentRegistry::Initialize()
{
    // First : The defined components are registrered
    RegisterItem( "animations", new ::nCore::nECS::nComponent::cAnimations(), "void" );
    RegisterItem( "behaviourtree", new ::nCore::nECS::nComponent::cBehaviourTree(), "void" );
    RegisterItem( "color", new ::nCore::nECS::nComponent::cColor(), "void" );
    RegisterItem( "direction", new ::nCore::nECS::nComponent::cDirection(), "void" );
    RegisterItem( "fieldofview", new ::nCore::nECS::nComponent::cFieldOfView(), "void" );
    RegisterItem( "occlusionfactor", new ::nCore::nECS::nComponent::cOcclusionFactor(), "void" );
    RegisterItem( "simplephysic", new ::nCore::nECS::nComponent::cSimplePhysic(), "void" );
    RegisterItem( "sound", new ::nCore::nECS::nComponent::cSound(), "void" );
    RegisterItem( "text", new ::nCore::nECS::nComponent::cText(), "void" );
    RegisterItem( "transformation", new ::nCore::nECS::nComponent::cTransformation(), "void" );
    RegisterItem( "userinput", new ::nCore::nECS::nComponent::cUserInput(), "void" );

    // Then we get all file based components
    nStdFileSystem::path componentsDir = PROJECTDIR + "/Assets/Components/";
    if( nStdFileSystem::exists( componentsDir ) )
    {
        nStdFileSystem::directory_iterator end{};
        tinyxml2::XMLDocument doc;

        for( nStdFileSystem::directory_iterator it { componentsDir }; it != end; ++it )
        {
            if( nStdFileSystem::is_regular_file( *it ) )
            {
                tinyxml2::XMLError error = doc.LoadFile( it->path().string().c_str() );
                if( error )
                    continue;

                auto component = new ::nCore::nECS::nCore::cComponentGeneric( it->path().filename().string().c_str() );
                component->LoadXML( doc.FirstChildElement( "component" ) );

                RegisterItem( component->ID(), component, it->path() );
                doc.Clear();
            }
        }
    }
}


void
cComponentRegistry::Finalize()
{
    for( auto it = mItems.begin(); it != mItems.end(); ++it )
        delete  it->second.mItem;

    mItems.clear();
}


} // namespace nRegistries
} // namespace nCore

