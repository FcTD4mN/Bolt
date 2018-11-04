#include "GameMockup.ECS.System.SquareController.h"


#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"

#include "Core.ECS.Component.Transformation.h"
#include "Core.ECS.Component.SimplePhysic.h"
#include "Core.ECS.Component.Sound.h"
#include "Core.ECS.Component.Animations.h"
#include "Core.ECS.Component.UserInput.h"

#include "Core.Screen.Screen.h"

#include "GameMockup.Application.GameApplication.h"

#include "Core.Render.LayerEngine.h"


#include "SFML/Graphics.hpp"


#include <iostream>


#include "Core.Registries.SystemRegistry.h"

namespace nECS {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSquareController::~cSquareController()
{
}


cSquareController::cSquareController() :
    tSuperClass( "SquareController" ),
    mVieuxTimer( 0 )
{
}


cSquareController::cSquareController( const cSquareController & iSys ) :
    tSuperClass( iSys ),
    mVieuxTimer( iSys.mVieuxTimer )
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


::nCore::nECS::nCore::cSystem*
cSquareController::Clone() const
{
    return  new  cSquareController( *this );
}

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
    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        ::nCore::nECS::nCore::cEntity* entity = mEntityGroup[ i ];

        auto userinput          = dynamic_cast< ::nCore::nECS::nComponent::cUserInput* >( entity->GetComponentByID( "userinput" ) );
        auto simplephysic       = dynamic_cast< ::nCore::nECS::nComponent::cSimplePhysic* >( entity->GetComponentByID( "simplephysic" ) );
        auto animations         = dynamic_cast< ::nCore::nECS::nComponent::cAnimations* >( entity->GetComponentByID( "animations" ) );
        auto transformation     = dynamic_cast< ::nCore::nECS::nComponent::cTransformation* >( entity->GetComponentByID( "transformation" ) );

        sf::Listener::setPosition( float( transformation->X()), float( transformation->Y()), 0.0F );

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
                if( animations )
                    animations->CurrentAnimationIsFlipped( true );
            }
            else if( userinput->mActions[ i ] == "moveleft" )
            {
                simplephysic->mVelocity.x -= 1.0F;
                if( animations )
                    animations->CurrentAnimationIsFlipped( false );
            }
            else if( userinput->mActions[ i ] == "moveupslow" )
            {
                animations->CurrentAnimationCurrentFrame( 5 );
            }
            else if( userinput->mActions[ i ] == "movedownslow" )
            {
                animations->CurrentAnimationCurrentFrame( 1 );
            }
            else if( userinput->mActions[ i ] == "moverightslow" )
            {
                animations->CurrentAnimationNextFrame();
            }
            else if( userinput->mActions[ i ] == "moveleftslow" )
            {
                animations->CurrentAnimationPrevFrame();
            }
            else if( userinput->mActions[ i ] == "attack" )
            {
                userinput->mActions.erase( userinput->mActions.begin() + i );

                if( animations->CurrentAnimation() == "second" )
                {
                    animations->CurrentAnimation( "mainAnimation" );
                }
                else if( animations->CurrentAnimation() == "mainAnimation" )
                {
                    animations->CurrentAnimation( "second" );
                    animations->CurrentAnimationPlay();
                }
            }

            // Basic test thing that assumes only one square is controlled
            // All the gamemockup part is testing anyway ...
            auto window = ::nCore::nApplication::cApplication::App()->Window();
            sf::View view = window->getDefaultView();
            view.setCenter( transformation->PositionAsVector2F() );

            auto screen = ::nCore::nApplication::cApplication::App()->CurrentScreen();
            screen->View( view );
        }
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cSquareController::IncomingEntity( ::nCore::nECS::nCore::cEntity * iEntity )
{
    auto userinput = iEntity->GetComponentByID( "userinput" );
    auto simplephysic = iEntity->GetComponentByID( "simplephysic" );

    if( userinput && simplephysic )
        AcceptEntity( iEntity );
}


} // namespace ECS

