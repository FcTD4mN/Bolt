#include "SquareController.h"

#include "ECS/Entity.h"

#include "GameMockup/GameApplication.h"
#include "GameMockup/Components/Position.h"
#include "GameMockup/Components/UserInput.h"
#include "GameMockup/Components/SpriteAnimated.h"

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
        auto spriteanimated = dynamic_cast< cSpriteAnimated* >( entity->GetComponentByName( "spriteanimated" ) );

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
                spriteanimated->Flip();
            }
            else if( userinput->mActions[ i ] == "moveleft" )
            {
                position->mPosition.x--;
                spriteanimated->Unflip();
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
    auto spriteanimated = iEntity->GetComponentByName( "spriteanimated" );

    if( userinput && position && spriteanimated )
        AcceptEntity( iEntity );
}

