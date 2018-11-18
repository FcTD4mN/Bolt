#include "Core.ECS.Core.Entity.h"

#include "Core.Base.CommonIncludes.h"

#include "Core.ECS.Core.Component.h"
#include "Core.ECS.Core.World.h"
#include "Core.ECS.Core.System.h"

#include "Core.Render.Layer.h"

#include "Core.Registries.ComponentRegistry.h"



namespace nCore {
namespace nECS {
namespace nCore {


static unsigned int sgEntityCount = 0;


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cEntity::~cEntity()
{
    for( auto it = mComponents.begin(); it != mComponents.end(); ++it )
        delete  it->value;
}


cEntity::cEntity() :
    mWorld( 0 ),
    mContainerLayer( 0 ),
    mID( "idontknow" + std::to_string( sgEntityCount ) ),
    mComponents(),
    mTags(),
    mObserverSystems(),
    mLoaded( false ),
    mDead( false ),
    mIDForHandles( 1 )
{
    mComponents.reserve( 16 );
    mTags.reserve( 64 );
    ++sgEntityCount;
}


cEntity::cEntity( const cEntity& iEntity ) :
    mWorld( iEntity.mWorld ),
    mContainerLayer( iEntity.mContainerLayer ),
    mID( iEntity.mID + "c" + std::to_string( sgEntityCount ) ),
    mComponents(),                                  // This will need to get copied
    mTags( iEntity.mTags ),                         // This can be copied, as there is no pointer
    mObserverSystems( iEntity.mObserverSystems ),   // Same systems will observe this entity
    mLoaded( iEntity.mLoaded ),
    mDead( iEntity.mDead ),
    mIDForHandles( iEntity.mIDForHandles + 1 )
{
    mComponents.reserve( iEntity.mComponents.size() );
    mTags.reserve( iEntity.mTags.size() );
    for( auto it = iEntity.mComponents.begin(); it != iEntity.mComponents.end(); ++it )
    {
        auto clonedComponent = it->value->Clone();
        clonedComponent->mEntityOwner = this;
        sPair pair;
        pair.key = it->key;
        pair.value = clonedComponent;
        mComponents.push_back( pair );
    }
    ++sgEntityCount;

    // We add the clone to the world and layer of the original
    if( mWorld )
        mWorld->AddEntityAndPutInLayer( this, mContainerLayer );

    // We recreate all internal connections
    for( auto tuple : iEntity.mAllInternalComponentsConnections )
        ConnectComponentsVariables( std::get< 0 >( tuple ), std::get< 1 >( tuple ), std::get< 2 >( tuple ), std::get< 3 >( tuple ) );

    if( mWorld )
    {
        // We recreate all external connections
        for( auto tuple : iEntity.mAllExternalComponentsConnections )
            ConnectComponentsVariablesFromEntity( std::get< 0 >( tuple ), std::get< 1 >( tuple ), std::get< 2 >( tuple ), std::get< 3 >( tuple ), std::get< 4 >( tuple ) );
    }
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Copy
// -------------------------------------------------------------------------------------


cEntity*
cEntity::Clone() const
{
    return  new cEntity( *this );
}


void
cEntity::LeaveAllSystems()
{
    for( int i = 0; i < mObserverSystems.size(); ++i )
        mObserverSystems[ i ]->EntityLost( this );

    mObserverSystems.clear();
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------- Components
// -------------------------------------------------------------------------------------


void
cEntity::AddComponent( ::nCore::nECS::nCore::cComponent * iComponent )
{
    iComponent->mEntityOwner = this;

    sPair pair;
    pair.key = iComponent->ID();
    pair.value = iComponent;
    mComponents.push_back( pair );

    if( mLoaded )
    {
        LeaveAllSystems();
        mWorld->UpdateWorldWithEntity( this );
    }

    IncIDForHandles();
}


void
cEntity::SetComponent( cComponent * iComponent )
{
    for( int i = 0; i < mComponents.size(); ++i )
    {
        if( mComponents[ i ].key == iComponent->ID() )
        {
            delete  mComponents[ i ].value;
            mComponents[ i ].value = iComponent;
        }
    }

    //IncIDForHandles(); // Should we invalid handle in this case ? or just if component count changed ?
}


void
cEntity::RemoveComponent( cComponent * iComponent )
{
    for( int i = 0; i < mComponents.size(); ++i )
    {
        if( mComponents[ i ].key == iComponent->ID() && mComponents[ i ].value == iComponent )
            mComponents.erase( mComponents.begin() + i );
    }

    if( mLoaded )
    {
        LeaveAllSystems();
        mWorld->UpdateWorldWithEntity( this );
    }

    delete  iComponent;

    IncIDForHandles();
}


void
cEntity::RemoveComponentByID( const std::string & iComponentID )
{
    ::nCore::nECS::nCore::cComponent* component = 0;
    for( int i = 0; i < mComponents.size(); ++i )
    {
        if( mComponents[i].key == iComponentID )
        {
            component = mComponents[i].value;
            mComponents.erase( mComponents.begin() + i );
        }
    }

    if( mLoaded )
    {
        LeaveAllSystems();
        mWorld->UpdateWorldWithEntity( this );
    }

    delete  component;

    IncIDForHandles();
}


cComponent*
cEntity::GetComponentByID( const std::string & iComponentID )
{
    for( int i = 0; i < mComponents.size(); ++i )
    {
        if( mComponents[ i ].key == iComponentID )
            return  mComponents[ i ].value;
    }

    return  0;
}


void
cEntity::ConnectComponentsVariables( const std::string & iComponentAName, const std::string & iVariableAName, const std::string & iComponentBName, const std::string & iVariableBName )
{
    auto  componentA = GetComponentByIDAs< cComponentGeneric* >( iComponentAName );
    auto  componentB = GetComponentByIDAs< cComponentGeneric* >( iComponentBName );
    assert( componentA && componentB );
    componentA->ConnectVariable( iVariableAName, componentB, iVariableBName );

    mAllInternalComponentsConnections.push_back( std::make_tuple( iComponentAName, iVariableAName, iComponentBName, iVariableBName ) );
}


void
cEntity::ConnectComponentsVariablesFromEntity( const std::string & iComponentAName, const std::string & iVariableAName, const std::string & iEntityBID, const std::string & iComponentBName, const std::string & iVariableBName )
{
    assert( mWorld && "A world is needed to connect to entity" );
    auto  componentA = GetComponentByIDAs< cComponentGeneric* >( iComponentAName );

    auto entityB = mWorld->GetEntityByID( iEntityBID );
    assert( entityB );
    if( !entityB )
        return;

    auto  componentB = entityB->GetComponentByIDAs< cComponentGeneric* >( iComponentBName );
    assert( componentA && componentB );
    if( !componentA || !componentB )
        return;

    componentA->ConnectVariable( iVariableAName, componentB, iVariableBName );

    mAllExternalComponentsConnections.push_back( std::make_tuple( iComponentAName, iVariableAName, iEntityBID, iComponentBName, iVariableBName ) );
}

void
cEntity::ConnectComponentsVariablesFromEntity( const std::string & iComponentAName, const std::string & iVariableAName, const cEntity * iEntityB, const std::string & iComponentBName, const std::string & iVariableBName )
{
    ConnectComponentsVariablesFromEntity( iComponentAName, iVariableAName, iEntityB->ID(), iComponentBName, iVariableBName );
}


cComponent*
cEntity::GetComponentAtIndex( int iIndex )
{
    return  mComponents[ iIndex ].value;
}


void
cEntity::RemoveComponentAtIndex( int iIndex )
{
    ::nCore::nECS::nCore::cComponent* component = mComponents[ iIndex ].value;

    if( mLoaded )
    {
        LeaveAllSystems();
        mComponents.erase( mComponents.begin() + iIndex );
        mWorld->UpdateWorldWithEntity( this );
    }
    else // Yes erase is done in both cases, but first case require it to be
    {
        mComponents.erase( mComponents.begin() + iIndex );
    }

    delete  component;

    IncIDForHandles();
}


unsigned int
cEntity::GetComponentCount() const
{
    return  (unsigned int)( mComponents.size() );
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------- Tags
// -------------------------------------------------------------------------------------


void
cEntity::AddTag( const std::string & iTag )
{
    mTags.push_back( iTag );
    IncIDForHandles();
}


void
cEntity::RemoveTag( const std::string & iTag )
{
    for( int i = 0; i < mTags.size(); ++i )
    {
        if( mTags[ i ] == iTag )
            mTags.erase( mTags.begin() + i );
    }

    IncIDForHandles();
}


bool
cEntity::HasTag( const std::string & iTag )
{
    for( int i = 0; i < mTags.size(); ++i )
    {
        if( mTags[ i ] == iTag )
            return  true;
    }

    return  false;
}


const std::string&
cEntity::GetTagAtIndex( int iIndex )
{
    return  mTags[ iIndex ];
}


void
cEntity::SetTagAtIndex( int iIndex, const std::string& iTag )
{
    mTags[ iIndex ] = iTag;
}


unsigned int
cEntity::GetTagCount() const
{
    return  (unsigned int)( mTags.size() );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Access
// -------------------------------------------------------------------------------------



::nCore::nRender::cLayer*
cEntity::Layer()
{
    return  mContainerLayer;
}


const ::nCore::nRender::cLayer*
cEntity::Layer() const
{
    return  mContainerLayer;
}


bool
cEntity::IsDead() const
{
    return  mDead;
}


void
cEntity::SetLoaded()
{
    mLoaded = true;
}


void
cEntity::SetWorld( cWorld * iWorld )
{
    mWorld = iWorld;
}


const std::string&
cEntity::ID() const
{
    return  mID;
}


bool
cEntity::SetID( const std::string & iID )
{
    if( mWorld && !mWorld->IsIDUnique( iID ) )
        return  false;

    mID = iID;
    return  true;
}


void
cEntity::Destroy()
{
    // To prevent unneeded multiple destructions
    if( mDead )
        return;

    LeaveAllSystems();
    mContainerLayer->RemoveEntity( this );

    mWorld->DestroyEntity( this );

    mDead = true;
    IncIDForHandles();
}


cEntityHandle
cEntity::GetHandle()
{
    return  cEntityHandle( this );
}


unsigned int
cEntity::GetIDForHandle() const
{
    return  mIDForHandles;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ System
// -------------------------------------------------------------------------------------


void
cEntity::AddSystemObserver( cSystem * iSystem )
{
    mObserverSystems.push_back( iSystem );
}


void
cEntity::DrawUsingObserverSystems( sf::RenderTarget * iRenderTarget )
{
    for( auto sys : mObserverSystems )
    {
        sys->DrawEntity( iRenderTarget, this );
    }
}


void
cEntity::IncIDForHandles()
{
    mIDForHandles = ( mIDForHandles + 1 ) % 99999;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Input/Output
// -------------------------------------------------------------------------------------


void
cEntity::SaveXML( tinyxml2::XMLElement * iNode, tinyxml2::XMLDocument* iDocument ) const
{
    iNode->SetAttribute( "id", mID.c_str() );

    tinyxml2::XMLElement* components = iDocument->NewElement( "components" );

    for( auto it = mComponents.begin(); it != mComponents.end(); ++it )
    {
        // Thing is wherever you do a mComponents[ "something" ], it creates a key value pair : {"something", NULL}
        if( it->value )
        {
            tinyxml2::XMLElement* component = iDocument->NewElement( "component" );
            it->value->SaveXML( component, iDocument );
            components->LinkEndChild( component );
        }
    }

    iNode->LinkEndChild( components );

    tinyxml2::XMLElement* tags = iDocument->NewElement( "tags" );

    for( auto it = mTags.begin(); it != mTags.end(); ++it )
    {
        tinyxml2::XMLElement* tag = iDocument->NewElement( "tag" );
        tag->SetAttribute( "name", it->c_str() );
        tags->LinkEndChild( tag );
    }

    iNode->LinkEndChild( tags );


    tinyxml2::XMLElement* internConnections = iDocument->NewElement( "internalConnections" );
    for( auto tuple : mAllInternalComponentsConnections )
    {
        tinyxml2::XMLElement* connection = iDocument->NewElement( "connection" );
        connection->SetAttribute( "compA", std::get< 0 >( tuple ).c_str() );
        connection->SetAttribute( "varA",  std::get< 1 >( tuple ).c_str() );
        connection->SetAttribute( "compB", std::get< 2 >( tuple ).c_str() );
        connection->SetAttribute( "varB",  std::get< 3 >( tuple ).c_str() );
        internConnections->LinkEndChild( connection );
    }

    iNode->LinkEndChild( internConnections );


    tinyxml2::XMLElement* externConnections = iDocument->NewElement( "externalConnections" );
    for( auto tuple : mAllExternalComponentsConnections )
    {
        tinyxml2::XMLElement* connection = iDocument->NewElement( "connection" );
        connection->SetAttribute( "compA", std::get< 0 >( tuple ).c_str() );
        connection->SetAttribute( "varA", std::get< 1 >( tuple ).c_str() );
        connection->SetAttribute( "entityB", std::get< 2 >( tuple ).c_str() );
        connection->SetAttribute( "compB", std::get< 3 >( tuple ).c_str() );
        connection->SetAttribute( "varB", std::get< 4 >( tuple ).c_str() );
        externConnections->LinkEndChild( connection );
    }

    iNode->LinkEndChild( externConnections );
}


void
cEntity::LoadXML( tinyxml2::XMLElement * iNode )
{
    mID = iNode->Attribute( "id" );
    tinyxml2::XMLElement* components = iNode->FirstChildElement( "components" );

    for( tinyxml2::XMLElement* component = components->FirstChildElement( "component" ); component; component = component->NextSiblingElement() )
    {
        cComponent* comp = ::nCore::nRegistries::cComponentRegistry::Instance()->CreateComponentFromName( component->Attribute( "id" ) );
        if( comp )
        {
            comp->LoadXML( component );
            AddComponent( comp );
        }
        else
        {
            cComponentGeneric* genComp = new cComponentGeneric( component->Attribute( "id" ) );
            genComp->LoadXML( component );
            AddComponent( genComp );
        }
    }

    tinyxml2::XMLElement* tags = iNode->FirstChildElement( "tags" );

    for( tinyxml2::XMLElement* tag = tags->FirstChildElement( "tag" ); tag; tag = tag->NextSiblingElement() )
    {
        AddTag( tag->Attribute( "name" ) );
    }

    tinyxml2::XMLElement* internalConnections = iNode->FirstChildElement( "internalConnections" );
    if( internalConnections )
    {
        for( tinyxml2::XMLElement* connection = internalConnections->FirstChildElement( "connection" ); connection; connection = connection->NextSiblingElement() )
        {
            std::string compA = connection->Attribute( "compA" );
            std::string varA = connection->Attribute( "varA" );
            std::string compB = connection->Attribute( "compB" );
            std::string varB = connection->Attribute( "varB" );

            ConnectComponentsVariables( compA, varA, compB, varB );
        }
    }
}



// =================================================
// ===================== HANDLE ====================
// =================================================



cEntityHandle::~cEntityHandle()
{
}


cEntityHandle::cEntityHandle( cEntity* iEntity ) :
    mEntity( iEntity ),
    mHandleID( iEntity->GetIDForHandle() )
{
}


cEntity *
cEntityHandle::GetEntity()
{
    if( !IsHandleValid() && !SyncHandle() )
        return  0;

    return  mEntity;
}


bool
cEntityHandle::IsHandleValid()
{
    return  mEntity->GetIDForHandle() == mHandleID;
}


bool
cEntityHandle::SyncHandle()
{
    if( mEntity->IsDead() )
    {
        return  false;
    }
    else
    {
        mHandleID = mEntity->GetIDForHandle();
        return  true;
    }
}


} // namespace nCore
} // namespace nECS
} // namespace nCore

