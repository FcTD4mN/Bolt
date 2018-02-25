#include "ECS/World.h"

#include "ECS/Entity.h"
#include "ECS/System.h"

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cWorld::~cWorld()
{
    for( int i = 0; i < mEntity.size(); ++i )
    {
        delete  mEntity[ i ];
    }

    for( int i = 0; i < mSystems.size(); ++i )
    {
        delete  mSystems[ i ];
    }
}


cWorld::cWorld()
{
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------- Main Running functions
// -------------------------------------------------------------------------------------


void
cWorld::Draw( sf::RenderTarget* iRenderTarget )
{
    for( int i = 0; i < mSystems.size(); ++i )
    {
        mSystems[ i ]->Draw( iRenderTarget );
    }
}


void
cWorld::Update( unsigned int iDeltaTime )
{
    for( int i = 0; i < mSystems.size(); ++i )
    {
        mSystems[ i ]->Update( iDeltaTime );
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


void
cWorld::AddEntity( cEntity* iEntity )
{
    mEntity.push_back( iEntity );
    UpdateWorldWithEntity( iEntity );
    iEntity->SetLoaded();
}


void
cWorld::RemoveEntity( cEntity* iEntity )
{
    for( int i = 0; i < mEntity.size(); ++i )
    {
        if( mEntity[ i ] == iEntity )
            mEntity.erase( mEntity.begin() + i );
    }
}


void
cWorld::UpdateWorldWithEntity( cEntity* iEntity )
{
    for( int i = 0; i < mSystems.size(); ++i )
    {
        mSystems[ i ]->IncomingEntity( iEntity );
    }
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------- Systems
// -------------------------------------------------------------------------------------


void
cWorld::AddSystem( cSystem * iSystem )
{
    mSystems.push_back( iSystem );
    iSystem->Initialize();
    for( int i = 0; i < mEntity.size(); ++i )
    {
        iSystem->IncomingEntity( mEntity[ i ] );
    }
}


void
cWorld::ConnectSystemToEvents( cSystem * iSystem )
{
    mEventRelatedSystems.push_back( iSystem );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cWorld::Resized( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->Resized( iEvent );
    }
}


void
cWorld::KeyPressed( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->KeyPressed( iEvent );
    }
}


void
cWorld::KeyReleased( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->KeyReleased( iEvent );
    }
}


void
cWorld::MouseWheelMoved( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->MouseWheelMoved( iEvent );
    }
}


void
cWorld::MouseWheelScrolled( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->MouseWheelScrolled( iEvent );
    }
}


void
cWorld::MouseButtonPressed( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->MouseButtonPressed( iEvent );
    }
}


void
cWorld::MouseButtonReleased( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->MouseButtonReleased( iEvent );
    }
}


void
cWorld::MouseMoved( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->MouseMoved( iEvent );
    }
}


void
cWorld::MouseEntered( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->MouseEntered( iEvent );
    }
}


void
cWorld::MouseLeft( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->MouseLeft( iEvent );
    }
}


void
cWorld::JoystickButtonPressed( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->JoystickButtonPressed( iEvent );
    }
}


void
cWorld::JoystickButtonReleased( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->JoystickButtonReleased( iEvent );
    }
}


void
cWorld::JoystickMoved( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->JoystickMoved( iEvent );
    }
}


void
cWorld::JoystickConnected( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->JoystickConnected( iEvent );
    }
}


void
cWorld::JoystickDisconnected( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->JoystickDisconnected( iEvent );
    }
}


void
cWorld::TouchBegan( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->TouchBegan( iEvent );
    }
}


void
cWorld::TouchMoved( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->TouchMoved( iEvent );
    }
}


void
cWorld::TouchEnded( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->TouchEnded( iEvent );
    }
}


void
cWorld::SensorChanged( const sf::Event& iEvent )
{
    for( int i = 0; i < mEventRelatedSystems.size(); ++i )
    {
        mEventRelatedSystems[ i ]->SensorChanged( iEvent );
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Input/Output
// -------------------------------------------------------------------------------------


void
cWorld::SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument )
{
    tinyxml2::XMLElement* entities = iDocument->NewElement( "entities" );

    for( int i = 0; i < mEntity.size(); ++i )
    {
        tinyxml2::XMLElement* entity = iDocument->NewElement( "entity" );
        mEntity[ i ]->SaveXML( entity, iDocument );
        entities->LinkEndChild( entity );
    }

    iNode->LinkEndChild( entities );
}


void
cWorld::LoadXML( tinyxml2::XMLElement* iNode )
{
    tinyxml2::XMLElement* entities = iNode->FirstChildElement( "entities" );

    for( tinyxml2::XMLElement* entity = entities->FirstChildElement( "entity" ); entity; entity = entity->NextSiblingElement() )
    {
        cEntity* loadedEntity = new cEntity( this );
        loadedEntity->LoadXML( entity );
        AddEntity( loadedEntity );
    }
}




