#include "ComponentRegistry.h"

#include "ECS/Core/Component.h"

#include "GameMockup/Components/Color.h"
#include "GameMockup/Components/Direction.h"
#include "GameMockup/Components/FieldOfView.h"
#include "GameMockup/Components/Position.h"
#include "GameMockup/Components/Size.h"
#include "GameMockup/Components/SimplePhysic.h"
#include "GameMockup/Components/SpriteAnimated.h"
#include "GameMockup/Components/UserInput.h"

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


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cComponentRegistry::Initialize()
{
    cColor*             colorPrototype          = new cColor();
    cDirection*         directionPrototype      = new cDirection();
    cFieldOfView*       fovPrototype            = new cFieldOfView();
    cPosition*          positionPrototype       = new cPosition();
    cSize*              sizePrototype           = new cSize();
    cSpriteAnimated*    spriteAnimatedPrototype = new cSpriteAnimated();
    cUserInput*         userInputPrototype      = new cUserInput();
    cSimplePhysic*      simplePhysicPrototype   = new cSimplePhysic();

    mComponents.insert( std::make_pair( colorPrototype->Name(), colorPrototype ) );
    mComponents.insert( std::make_pair( directionPrototype->Name(), directionPrototype ) );
    mComponents.insert( std::make_pair( fovPrototype->Name(), fovPrototype ) );
    mComponents.insert( std::make_pair( positionPrototype->Name(), positionPrototype ) );
    mComponents.insert( std::make_pair( sizePrototype->Name(), sizePrototype ) );
    mComponents.insert( std::make_pair( spriteAnimatedPrototype->Name(), spriteAnimatedPrototype ) );
    mComponents.insert( std::make_pair( userInputPrototype->Name(), userInputPrototype ) );
    mComponents.insert( std::make_pair( simplePhysicPrototype->Name(), simplePhysicPrototype ) );
}


void
cComponentRegistry::Finalize()
{
    for( auto it = mComponents.begin(); it != mComponents.end(); ++it )
    {
        delete  it->second;
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------ Registry functions
// -------------------------------------------------------------------------------------


void
cComponentRegistry::RegisterComponent( cComponent * iComponent )
{
    mComponents.insert( std::make_pair( iComponent->Name(), iComponent ) );
}


cComponent*
cComponentRegistry::CreateComponentFromName( const std::string & iName )
{
    return  mComponents[ iName ]->Clone();
}
