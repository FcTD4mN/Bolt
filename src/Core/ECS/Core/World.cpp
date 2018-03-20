#include "ECS/Core/World.h"

#include "ECS/Core/Entity.h"
#include "ECS/Core/System.h"

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cWorld::~cWorld()
{
    DestroyAllEntities();

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
    PurgeEntities();
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
    mEntity[ iEntity->ID() ] = iEntity;
    UpdateWorldWithEntity( iEntity );
    iEntity->SetLoaded();
}


void
cWorld::RemoveEntity( cEntity* iEntity )
{
    mEntity.erase( iEntity->ID() );
}


void
cWorld::UpdateWorldWithEntity( cEntity* iEntity )
{
    for( int i = 0; i < mSystems.size(); ++i )
    {
        mSystems[ i ]->IncomingEntity( iEntity );
    }
}


void
cWorld::DestroyEntity( cEntity * iEntity )
{
    mEntitiesToDestroy.push_back( iEntity );
}


void
cWorld::DestroyEntityByID( const  std::string& iID )
{
    mEntity.erase( iID );
}


cEntity*
cWorld::GetEntityByID( const  std::string& iID )
{
    return  mEntity[ iID ];
}


void
cWorld::DestroyAllEntities()
{
    for( auto it : mEntity )
    {
        it.second->Destroy();
    }
    PurgeEntities();
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------- Systems
// -------------------------------------------------------------------------------------


void
cWorld::AddSystem( cSystem * iSystem )
{
    mSystems.push_back( iSystem );
    iSystem->Initialize();
    for( auto it = mEntity.begin(); it != mEntity.end(); ++it )
    {
        iSystem->IncomingEntity( it->second );
    }
}


void
cWorld::ConnectSystemToEvents( cSystem * iSystem )
{
    mEventRelatedSystems.push_back( iSystem );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Access
// -------------------------------------------------------------------------------------


size_t
cWorld::EntityCount() const
{
    return  mEntity.size();
}


void cWorld::PurgeEntities()
{
    //OPTI: This is not ideal, as remove entity is o(n) worst case
    while( mEntitiesToDestroy.size() > 0 )
    {
        cEntity* ent = mEntitiesToDestroy.back();
        RemoveEntity( ent );
        delete  ent;
        mEntitiesToDestroy.pop_back();
    }
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

    for( auto it = mEntity.begin(); it != mEntity.end(); ++it )
    {
        tinyxml2::XMLElement* entity = iDocument->NewElement( "entity" );
        it->second->SaveXML( entity, iDocument );
        entities->LinkEndChild( entity );
    }

    iNode->LinkEndChild( entities );
}


void
cWorld::LoadXML( tinyxml2::XMLElement* iNode )
{
    DestroyAllEntities();
    tinyxml2::XMLElement* entities = iNode->FirstChildElement( "entities" );

    for( tinyxml2::XMLElement* entity = entities->FirstChildElement( "entity" ); entity; entity = entity->NextSiblingElement() )
    {
        cEntity* loadedEntity = new cEntity( this );
        loadedEntity->LoadXML( entity );
        AddEntity( loadedEntity );
    }
}




