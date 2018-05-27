#include "GameMockup.ECS.System.SquareController.h"


#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"

#include "Core.ECS.Component.Position.h"
#include "Core.ECS.Component.SimplePhysic.h"
#include "Core.ECS.Component.Sound.h"
#include "Core.ECS.Component.SpriteAnimated.h"
#include "Core.ECS.Component.UserInput.h"

#include "Core.ECS.Utilities.EntityParser.h"

#include "GameMockup.Application.GameApplication.h"

#include "Core.Render.LayerEngine.h"


#include "SFML/Graphics.hpp"


#include <iostream>


namespace nECS {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSquareController::~cSquareController()
{
}


cSquareController::cSquareController() :
    tSuperClass(),
    mVieuxTimer( 0 )
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cSquareController::Initialize()
{
}


void
cSquareController::Finalize()
{
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cSquareController::Draw( sf::RenderTarget* iRenderTarget )
{
}


void
cSquareController::Update( unsigned int iDeltaTime )
{
    //return;
    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto userinput      = dynamic_cast< cUserInput* >( entity->GetComponentByName( "userinput" ) );
        auto simplephysic = dynamic_cast< cSimplePhysic* >( entity->GetComponentByName( "simplephysic" ) );
        auto spriteanimated = dynamic_cast< cSpriteAnimated* >( entity->GetComponentByName( "spriteanimated" ) );
        auto position = dynamic_cast< cPosition* >( entity->GetComponentByName( "position" ) );

        sf::Listener::setPosition( float(position->X()), float(position->Y()), 0.0F );

        simplephysic->mVelocity.x = 0;
        simplephysic->mVelocity.y = 0;

        for( int i = 0; i < userinput->mActions.size(); ++i )
        {
            if( userinput->mActions[ i ] == "moveup" )
            {
                simplephysic->mVelocity.y -= 1.0F;
            }
            else if( userinput->mActions[ i ] == "movedown" )
            {
                simplephysic->mVelocity.y += 1.0F;
            }
            else if( userinput->mActions[ i ] == "moveright" )
            {
                simplephysic->mVelocity.x += 1.0F;
                if( spriteanimated )
                    spriteanimated->Flip( true );
            }
            else if( userinput->mActions[ i ] == "moveleft" )
            {
                simplephysic->mVelocity.x -= 1.0F;
                if( spriteanimated )
                    spriteanimated->Flip( false );
            }
            else if( userinput->mActions[ i ] == "moveupslow" )
            {
                simplephysic->mVelocity.y -= 0.001F;
            }
            else if( userinput->mActions[ i ] == "movedownslow" )
            {
                simplephysic->mVelocity.y += 0.001F;
            }
            else if( userinput->mActions[ i ] == "moverightslow" )
            {
                simplephysic->mVelocity.x += 0.001F;
            }
            else if( userinput->mActions[ i ] == "moveleftslow" )
            {
                simplephysic->mVelocity.x -= 0.001F;
            }
            else if( userinput->mActions[ i ] == "attack" )
            {
            }

            // Basic test thing that assumes only one square is controlled
            // All the gamemockup part is testing anyway ...
            //auto window = ::nApplication::cGameApplication::App()->Window();
            //sf::View view = window->getDefaultView();
            //view.setCenter( position->AsVector2F() );
            //window->setView( view );

            auto world = ::nApplication::cGameApplication::App()->World();
            world->mLayerEngine->SetLayersCenter( position->AsVector2F() );

        }
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cSquareController::IncomingEntity( cEntity * iEntity )
{
    auto userinput = iEntity->GetComponentByName( "userinput" );
    auto simplephysic = iEntity->GetComponentByName( "simplephysic" );

    if( userinput && simplephysic )
        AcceptEntity( iEntity );
}


} // namespace ECS

