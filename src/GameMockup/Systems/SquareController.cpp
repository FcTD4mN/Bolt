#include "SquareController.h"

#include "ECS/Entity.h"

#include "GameMockup/GameApplication.h"
#include "GameMockup/Components/Position.h"
#include "GameMockup/Components/UserInput.h"

#include <iostream>

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cSquareController::~cSquareController()
{
}


cSquareController::cSquareController() :
    tSuperClass()
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
cSquareController::Update()
{
    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto userinput = dynamic_cast< cUserInput* >( entity->GetComponentByName( "userinput" ) );
        auto position = dynamic_cast< cPosition* >( entity->GetComponentByName( "position" ) );

        for( int i = 0; i < userinput->mActions.size(); ++i )
        {
            if( userinput->mActions[ i ] == "moveup" )
            {
                position->mPosition.y--;
            }
            else if( userinput->mActions[ i ] == "movedown" )
            {
                position->mPosition.y++;
            }
            else if( userinput->mActions[ i ] == "moveright" )
            {
                position->mPosition.x++;
            }
            else if( userinput->mActions[ i ] == "moveleft" )
            {
                position->mPosition.x--;
            }
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
    auto position = iEntity->GetComponentByName( "position" );

    if( userinput && position )
        AcceptEntity( iEntity );
}

