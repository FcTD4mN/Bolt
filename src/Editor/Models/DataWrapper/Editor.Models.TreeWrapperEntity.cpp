#include "Editor.Models.TreeWrapperEntity.h"

#include "Core.ECS.Core.Component.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.Registries.EntityRegistry.h"
#include "Core.Base.Variant.h"

namespace nQt {
namespace nModels {


cTreeWrapperNodeEntity::~cTreeWrapperNodeEntity()
{
}


 cTreeWrapperNodeEntity::cTreeWrapperNodeEntity( cTreeWrapperNode* iParent, ::nCore::nECS::nCore::cEntityHandle iEntity ) :
    tSuperClass( iParent ),
     mEntity( iEntity )
{
     if( mEntity.IsHandleValid() )
        AppendData( "" );
     else
        AppendData( "New Component" );


     AppendData( "" );
}


std::string
cTreeWrapperNodeEntity::Type() const
{
    return  "Entity";
}


// ------ DATA


int
cTreeWrapperNodeEntity::DataCount() const
{
    return  2;
}


QVariant
cTreeWrapperNodeEntity::DataAtColumn( int iColumn )
{
    if( iColumn == 0 )
    {
        return  "ID";
    }
    else
    {
        auto entity = mEntity.GetEntity();
        if( !entity )
            return  "INVALID ENTITY";
        else
            return  entity->ID().c_str();
    }
}


bool
cTreeWrapperNodeEntity::SetData( int iIndex, const QVariant & iData )
{
    if( iIndex != 1 )
        return  false;

    auto entity = mEntity.GetEntity();
    if( !entity )
        return  false;

    auto entityParser = ::nCore::nRegistries::cEntityRegistry::Instance();
    auto filename = entityParser->GetItemFileByItemName( entity->ID() );

    // We update index id
    entityParser->UnregisterItemByName( mEntity.GetEntity()->ID() );
    entity->SetID( iData.toString().toStdString() );
    entityParser->RegisterItem( mEntity.GetEntity()->ID(), entity );

    entityParser->SetItemFileUsingItemName( mEntity.GetEntity()->ID(), filename );

    return  true;
}


::nCore::nECS::nCore::cEntityHandle
cTreeWrapperNodeEntity::Entity()
{
    return  mEntity;
}


// ======================================================================
// ======================================================================
// ======================================================================


cTreeWrapperNodeComponent::~cTreeWrapperNodeComponent()
{
}


 cTreeWrapperNodeComponent::cTreeWrapperNodeComponent( cTreeWrapperNode* iParent, ::nCore::nECS::nCore::cComponent* iComponent ) :
    tSuperClass( iParent ),
     mComponent( iComponent )
{
     if( mComponent )
        AppendData( mComponent->ID().c_str() );
     else
        AppendData( "New Component" );


     AppendData( "" );
}


std::string
cTreeWrapperNodeComponent::Type() const
{
    return  "Component";
}


::nCore::nECS::nCore::cComponentGeneric *
cTreeWrapperNodeComponent::Component()
{
    return  dynamic_cast< ::nCore::nECS::nCore::cComponentGeneric* >(mComponent);
}


// ======================================================================
// ======================================================================
// ======================================================================


cTreeWrapperNodeTag::~cTreeWrapperNodeTag()
{
}


cTreeWrapperNodeTag::cTreeWrapperNodeTag( cTreeWrapperNode* iParent, ::nCore::nECS::nCore::cEntityHandle iEntity, int iTagIndex ) :
    tSuperClass( iParent ),
    mEntity( iEntity ),
    mTagIndex( iTagIndex )
{
    if( mEntity.IsHandleValid() && iTagIndex >= 0 && iTagIndex < mEntity.GetEntity()->GetTagCount() )
        AppendData( mEntity.GetEntity()->GetTagAtIndex( mTagIndex ).c_str() );
    else
        AppendData( "New Component" );


    AppendData( "" );
}


std::string
cTreeWrapperNodeTag::Type() const
{
    return  "Tag";
}

bool
cTreeWrapperNodeTag::SetData( int iIndex, const QVariant & iData )
{
    auto entity = mEntity.GetEntity();
    if( !entity )
        return  false;

    entity->SetTagAtIndex( mTagIndex, iData.toString().toStdString() );
    return  tSuperClass::SetData( iIndex, iData );
}


const std::string
cTreeWrapperNodeTag::Tag()
{
    auto entity = mEntity.GetEntity();
    if( !entity )
        return  "INVALID ENTITY";

    return  entity->GetTagAtIndex( mTagIndex );
}


void
cTreeWrapperNodeTag::SetTagIndex( int iIndex )
{
    mTagIndex = iIndex;
}


// ===========================================================================
// ===========================================================================
// ===========================================================================


cTreeWrapperNodeVariable::~cTreeWrapperNodeVariable()
{
}


cTreeWrapperNodeVariable::cTreeWrapperNodeVariable( cTreeWrapperNode * iParent, ::nCore::nECS::nCore::cComponentGeneric* iComponent, int iVarIndex ) :
    tSuperClass( iParent ),
    mComponent( iComponent ),
    mVarIndex( iVarIndex )
{
    if( mComponent && mVarIndex != -1 )
    {
        AppendData( mComponent->GetVarNameAtIndex( mVarIndex ).c_str() );
        AppendData( mComponent->GetVarAtIndex( mVarIndex )->ToString().c_str() );
    }
    else
    {
        AppendData( ( "New Variable" + std::to_string( mComponent->VarCount() ) ).c_str() );
        AppendData( "" );
    }
}


std::string
cTreeWrapperNodeVariable::Type() const
{
    return  "Variable";
}


// ------ DATA


int
cTreeWrapperNodeVariable::DataCount() const
{
    return  2;
}


QVariant
cTreeWrapperNodeVariable::DataAtColumn( int iColumn )
{
    if( iColumn == 0 )
    {
        return  mComponent->GetVarNameAtIndex( mVarIndex ).c_str();
    }
    else
    {
        ::nCore::nBase::cVariant* var = mComponent->GetVarAtIndex( mVarIndex );
        switch( var->Type() )
        {
            case ::nCore::nBase::kNumber:
                return  var->GetValueNumber();
                break;
            case ::nCore::nBase::kString:
                return  var->GetValueString().c_str();
                break;
            case ::nCore::nBase::kBoolean:
                return  var->GetValueBool();
                break;
            default:
                break;
        }
    }

    return  QVariant();
}


bool
cTreeWrapperNodeVariable::SetData( int iIndex, const QVariant & iData )
{
    if( iIndex == 0 ) // Setting variable name
    {
        tSuperClass::SetData( 0, iData );
    }
    else if( iIndex == 1 )
    {
        ::nCore::nBase::cVariant* var = mComponent->GetVarAtIndex( mVarIndex );
        switch( var->Type() )
        {
            case ::nCore::nBase::kNumber:
                var->SetValueNumber( iData.toDouble() );
                break;
            case ::nCore::nBase::kString:
                var->SetValueString( iData.toString().toStdString() );
                break;
            case ::nCore::nBase::kBoolean:
                var->SetValueBool( iData.toBool() );
                break;
            default:
                break;
        }

        tSuperClass::SetData( 1, iData );
    }

    return false;
}

} //nModels
} //nQt

