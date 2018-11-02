#include "Core.ECS.Core.World.h"


#include "Core.Base.Utilities.h"

#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.System.h"
#include "Core.Registries.SystemRegistry.h"

#include "Core.Mapping.PhysicEntityGrid.h"

#include "Core.Render.Layer.h"
#include "Core.Render.LayerEngine.h"

#include "Core.Shader.Shader2D.h"


namespace nCore {
namespace nECS {
namespace nCore {


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
    delete  mEntityMap;
    delete  mLayerEngine;
}


cWorld::cWorld() :
    mLayerEngine( 0 ),
    mUseLayerEngine( false ),
    mEntityMap( new ::nCore::nMapping::cPhysicEntityGrid( 100, 100, 32 ) )
{
    SetUseLayerEngine( true ); // This will probably be the only possible thing
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------- Main Running functions
// -------------------------------------------------------------------------------------


void
cWorld::Draw( sf::RenderTarget* iRenderTarget )
{
    auto view = iRenderTarget->getView();

    // Layer drawing first
    mLayerEngine->Draw( iRenderTarget );

    // We reset the view because each layer sets its own, so we go back to the original one here.
    iRenderTarget->setView( view );

    // General purpose drawing then
    // Is there a better way to allow systems such as sight system for example to draw global stuff
    // that is not related to specific entities, and thus, not drawn each time in a drawEntity func ?
    // PROBLEM here is we call some empty functions, BUT : there are not a billion system either, so it should be fine.
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


void
cWorld::SetUseLayerEngine( bool iValue )
{
    mUseLayerEngine = iValue;
    if( !mLayerEngine )
        mLayerEngine = new ::nCore::nRender::cLayerEngine();
}


::nCore::nRender::cLayerEngine*
cWorld::LayerEngine()
{
    return  mLayerEngine;
}


void
cWorld::AddLayer( const sf::Vector2f& iViewSize, float iDistance )
{
    mLayerEngine->AddLayer( iViewSize, iDistance );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Entity
// -------------------------------------------------------------------------------------


int
cWorld::AddEntityAndPutInLayer( cEntity* iEntity, ::nCore::nRender::cLayer* iLayer )
{
    _AddEntityToWorld( iEntity );

    // Adding in the given layer, if no layer set, we put in 0 by default
    if( iLayer )
        return  iLayer->AddEntity( iEntity );
    else
        return  mLayerEngine->AddEntityInLayer( iEntity, 0 );
}


int
cWorld::AddEntityAndPutInLayer( cEntity* iEntity, int iLayerIndex )
{
    int indexInLayer = mLayerEngine->AddEntityInLayer( iEntity, iLayerIndex );
    _AddEntityToWorld( iEntity );

    return  indexInLayer;
}


void
cWorld::LayersEnumerator( std::function< void( ::nCore::nRender::cLayer* ) > iFunction )
{
    mLayerEngine->LayersEnumerator( iFunction );
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
cWorld::DestroyEntity( cEntity* iEntity )
{
    mEntitiesToDestroy.push_back( iEntity );
}


void
cWorld::DestroyEntityByID( const  std::string& iID )
{
    mEntitiesToDestroy.push_back( mEntities[ iID ] );
}


cEntity*
cWorld::GetEntityByID( const  std::string& iID )
{
    return  mEntities[ iID ];
}


cEntity*
cWorld::GetEntityAtIndex( int iIndex )
{
    auto it = mEntities.begin();
    for( int i = 0; i < iIndex; ++i )
        ++it;
    return  it->second;
}


void
cWorld::DestroyAllEntities()
{
    for( auto it : mEntities )
    {
        it.second->Destroy();
    }
    PurgeEntities();
}


void cWorld::PurgeEntities()
{
    while( mEntitiesToDestroy.size() > 0 )
    {
        cEntity* ent = mEntitiesToDestroy.back();
        RemoveEntity( ent );
        delete  ent;
        mEntitiesToDestroy.pop_back();
    }
}


void
cWorld::EntityEnumerator( std::function< void( cEntity* ) > iEnumeratorFunction )
{
    for( auto pair : mEntities )
        iEnumeratorFunction( pair.second );
}


bool
cWorld::IsIDUnique( const std::string& iID ) const
{
    for( auto it : mEntities )
    {
        if( it.second->ID() == iID )
            return  false;
    }

    return  true;
}


void
cWorld::_AddEntityToWorld( cEntity* iEntity )
{
    if( mEntities[ iEntity->ID() ] == iEntity )
        return;

    if( iEntity->mWorld != NULL && iEntity->mWorld != this )
        iEntity->mWorld->RemoveEntity( iEntity );

    mEntities[ iEntity->ID() ] = iEntity;
    UpdateWorldWithEntity( iEntity );
    iEntity->SetWorld( this );
    iEntity->SetLoaded();
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------- Systems
// -------------------------------------------------------------------------------------


void
cWorld::AddSystem( cSystem* iSystem )
{
    InsertSystem( iSystem, int(mSystems.size()) );
}


void
cWorld::InsertSystem( cSystem* iSystem, int iIndex )
{
    auto sysIT = mSystems.begin();
    for( int i = 0; i < iIndex; ++i )
    {
        if( sysIT == mSystems.end() )
            break;

        ++sysIT;
    }

    mSystems.insert( sysIT, iSystem );
    iSystem->mWorld = this;
    iSystem->Initialize();
    for( auto it = mEntities.begin(); it != mEntities.end(); ++it )
        iSystem->IncomingEntity( it->second );

    if( iSystem->IsEventConnected() )
        ConnectSystemToEvents( iSystem );
}


void
cWorld::RemoveSystem( cSystem* iSystem )
{
    auto it = mSystems.begin();
    for( auto sys : mSystems )
    {
        if( sys == iSystem )
            break;
        ++it;
    }

    if( it == mSystems.end() )
        return;

    mSystems.erase( it );
    iSystem->mWorld = 0;
    iSystem->Finalize();

    for( auto it : mEntities )
        ::nCore::nBase::EraseElementFromVector( &it.second->mObserverSystems, iSystem );
}


void
cWorld::RemoveSystemByName( const std::string& iSysName )
{
    auto it = mSystems.begin();
    for( auto sys : mSystems )
    {
        if( sys->Name() == iSysName )
            break;
        ++it;
    }

    if( it == mSystems.end() )
        return;

    (*it)->mWorld = 0;
    (*it)->Finalize();

    for( auto it2 : mEntities )
        ::nCore::nBase::EraseElementFromVector( &it2.second->mObserverSystems, *it );

    mSystems.erase( it );
}


void
cWorld::ConnectSystemToEvents( cSystem* iSystem )
{
    if( std::find( mEventRelatedSystems.begin(), mEventRelatedSystems.end(), iSystem ) == mEventRelatedSystems.end() )
        mEventRelatedSystems.push_back( iSystem );
}


void
cWorld::DisconnectSystemToEvents( cSystem* iSystem )
{
    ::nCore::nBase::EraseElementFromVector( &mEventRelatedSystems, iSystem );
}


cSystem*
cWorld::GetSystemAtIndex( int iIndex )
{
    if( iIndex < 0 || iIndex >= mSystems.size() )
        return  0;

    return  mSystems[ iIndex ];
}


cSystem*
cWorld::GetSystemByName( const std::string& iName )
{
    for( auto system : mSystems )
        if( system->Name() == iName )
            return  system;

    return  0;
}


bool
cWorld::HasSystem( const std::string& iSysName ) const
{
    for( auto sys : mSystems )
        if( sys->Name() == iSysName )
            return  true;

    return  false;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Access
// -------------------------------------------------------------------------------------


int
cWorld::EntityCount() const
{
    return  int(mEntities.size());
}


int
cWorld::SystemCount() const
{
    return  int(mSystems.size());
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------- Private
// -------------------------------------------------------------------------------------


void
cWorld::RemoveEntity( cEntity* iEntity )
{
    mEntities.erase( iEntity->ID() );
}


// -------------------------------------------------------------------------------------
// --------------------------------------------------------------------------- EntityMap
// -------------------------------------------------------------------------------------


void
cWorld::SetEntityMapDimensions( int iWidth, int iHeight, int iCellSize )
{
    mEntityMap->SetGridDimensions( iWidth, iHeight, iCellSize );
}


::nCore::nMapping::cEntityGrid*
cWorld::EntityMap()
{
    return  mEntityMap;
}


void
cWorld::EntityMapEnumerator( std::function< void( ::nCore::nMapping::cEntityGrid* iEntityGrid ) > iFunction )
{
    if ( !mUseLayerEngine )
    {
        iFunction( mEntityMap );
    }
    else
    {
        for ( int i = 0; i < mLayerEngine->LayerCount(); ++i )
        {
            ::nCore::nRender::cLayer* layer = mLayerEngine->LayerAtIndex( i );
            iFunction( layer->EntityGrid() );
        }
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
cWorld::SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument ) const
{
    // ENTITY MAP
    tinyxml2::XMLElement* entityMap = iDocument->NewElement( "entityMap" );
    entityMap->SetAttribute( "width", mEntityMap->Width() );
    entityMap->SetAttribute( "height", mEntityMap->Height() );
    entityMap->SetAttribute( "cellsize", mEntityMap->CellSize() );
    iNode->LinkEndChild( entityMap );

    // LAYERS + ENTITIES
    iNode->SetAttribute( "uselayer", mUseLayerEngine );
    tinyxml2::XMLElement* layersNode = iDocument->NewElement( "layers" );
    mLayerEngine->SaveXML( layersNode, iDocument );
    iNode->LinkEndChild( layersNode );

    // SYSTEMS
    tinyxml2::XMLElement* systemsNode = iDocument->NewElement( "systems" );
    for( auto system : mSystems )
    {
        tinyxml2::XMLElement* systemNode = iDocument->NewElement( "system" );
        bool eventConnected = ::nCore::nBase::VectorContains( mEventRelatedSystems, system );
        systemNode->SetAttribute( "name", system->Name().c_str() );
        systemNode->SetAttribute( "eventconnected", eventConnected );
        systemsNode->LinkEndChild( systemNode );
    }

    iNode->LinkEndChild( systemsNode );
}


void
cWorld::LoadXML( tinyxml2::XMLElement* iNode )
{
    DestroyAllEntities();

    // ====================== EntityMap
    tinyxml2::XMLElement* entityMap = iNode->FirstChildElement( "entityMap" );
    int eMapWidth = entityMap->IntAttribute( "width" );
    int eMapHeight = entityMap->IntAttribute( "height" );
    int eMapCellSize = entityMap->IntAttribute( "cellsize" );

    // Loading means we want a fresh entity map and a fresh world, so if they already exist, we diss them for brand new ones
    if( mEntityMap )
        delete  mEntityMap;
    mEntityMap = new ::nCore::nMapping::cPhysicEntityGrid( eMapWidth, eMapHeight, eMapCellSize );

    // ====================== Layers
    mUseLayerEngine = iNode->BoolAttribute( "uselayer" );
    mLayerEngine = new ::nCore::nRender::cLayerEngine();

    tinyxml2::XMLElement* layers = iNode->FirstChildElement( "layers" );
    int layerIndex = 0;
    for( tinyxml2::XMLElement* layer = layers->FirstChildElement( "layer" ); layer; layer = layer->NextSiblingElement() )
    {
        // Layer's view size
        float zLayer= layer->FloatAttribute( "zlayer" );
        mLayerEngine->AddLayer( sf::Vector2f(), zLayer );
        auto addedLayer = mLayerEngine->LayerAtIndex( mLayerEngine->LayerCount() - 1 );
        addedLayer->LoadXML( layer ); // This will manage simple properties, not the entity containement

        // Layer's Shaders
        tinyxml2::XMLElement* shaders = layer->FirstChildElement( "shaders" );
        if( shaders )
        {
            for( tinyxml2::XMLElement* shader = shaders->FirstChildElement( "shader" ); shader; shader = shader->NextSiblingElement() )
            {
                ::nCore::nShader::cShader2D* theShader = new  ::nCore::nShader::cShader2D( shader->Attribute( "file" ), shader->Attribute( "name" ) );
                theShader->LoadXML( shader );
                theShader->ApplyUniforms();
                mLayerEngine->AddShaderToLayer( theShader, layerIndex );
            }
        }

        // =================== Entities
        tinyxml2::XMLElement* entities = layer->FirstChildElement( "entities" );
        for( tinyxml2::XMLElement* entity = entities->FirstChildElement( "entity" ); entity; entity = entity->NextSiblingElement() )
        {
            cEntity* loadedEntity = new cEntity();
            loadedEntity->LoadXML( entity );
            AddEntityAndPutInLayer( loadedEntity, layerIndex );
            loadedEntity->mContainerLayer = mLayerEngine->LayerAtIndex( layerIndex );
        }

        ++layerIndex;
    }

    // ====================== Systems
    tinyxml2::XMLElement* systems = iNode->FirstChildElement( "systems" );
    for( tinyxml2::XMLElement* system = systems->FirstChildElement( "system" ); system; system = system->NextSiblingElement() )
    {
        ::nCore::nECS::nCore::cSystem* sys = ::nCore::nRegistries::cSystemRegistry::Instance()->CreateSystemFromName( system->Attribute( "name" ) );
        if( sys )
        {
            AddSystem( sys );
            if( system->BoolAttribute( "eventconnected" ) )
                ConnectSystemToEvents( sys );
        }
    }
}


} // namespace nCore
} // namespace nECS
} // namespace nCore

