#include "SquareController.h"

#include "ECS/Entity.h"
#include "ECS/EntityParser.h"
#include "ECS/World.h"

#include "GameMockup/GameApplication.h"
#include "GameMockup/Components/SimplePhysic.h"
#include "GameMockup/Components/Position.h"
#include "GameMockup/Components/SpriteAnimated.h"
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
cSquareController::Update( unsigned int iDeltaTime )
{
    for( int i = 0; i < mEntityGroup.size(); ++i )
    {
        cEntity* entity = mEntityGroup[ i ];

        auto userinput      = dynamic_cast< cUserInput* >( entity->GetComponentByName( "userinput" ) );
        auto simplephysic = dynamic_cast< cSimplePhysic* >( entity->GetComponentByName( "simplephysic" ) );
        auto spriteanimated = dynamic_cast< cSpriteAnimated* >( entity->GetComponentByName( "spriteanimated" ) );

        simplephysic->mVelocity.x = 0;
        simplephysic->mVelocity.y = 0;

        for( int i = 0; i < userinput->mActions.size(); ++i )
        {
            if( userinput->mActions[ i ] == "moveup" )
            {
                simplephysic->mVelocity.y -= 1;
            }
            else if( userinput->mActions[ i ] == "movedown" )
            {
                simplephysic->mVelocity.y += 1;
            }
            else if( userinput->mActions[ i ] == "moveright" )
            {
                simplephysic->mVelocity.x += 1;
                if( spriteanimated )
                    spriteanimated->Flip();
            }
            else if( userinput->mActions[ i ] == "moveleft" )
            {
                simplephysic->mVelocity.x -= 1;
                if( spriteanimated )
                    spriteanimated->Unflip();
            }
            else if( userinput->mActions[ i ] == "attack" )
            {
                cEntity* bullet = cEntityParser::Instance()->CreateEntityFromPrototypeMap( "bullet" );
                float x = simplephysic->mHitBox.left + simplephysic->mHitBox.width + 5;
                float y = simplephysic->mHitBox.top - simplephysic->mHitBox.height / 2;
                auto pos = dynamic_cast< cPosition* >( bullet->GetComponentByName( "position" ) );
                pos->mPosition.x = x;
                pos->mPosition.y = y;

                auto phys = dynamic_cast< cSimplePhysic* >( bullet->GetComponentByName( "simplephysic" ) );
                phys->mHitBox.left = x;
                phys->mHitBox.top = y;

                phys->mVelocity.x = 0.1;
                cGameApplication::App()->World()->AddEntity( bullet );
                userinput->mActions.erase( userinput->mActions.begin() + i );
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
    auto simplephysic = iEntity->GetComponentByName( "simplephysic" );

    if( userinput && simplephysic )
        AcceptEntity( iEntity );
}

