#include "Editor.BoltQtModels.TreeWrapperEntity.h"

#include "Core.ECS.Core.Component.h"
#include "Core.ECS.Utilities.ComponentRegistry.h"
#include "Core.Base.Variant.h"

namespace nQt {
namespace nModels {


cTreeWrapperNodeEntity::~cTreeWrapperNodeEntity()
{
}


 cTreeWrapperNodeEntity::cTreeWrapperNodeEntity( cTreeWrapperNode* iParent, ::nECS::cEntity* iEntity ) :
    tSuperClass( iParent ),
     mEntity( iEntity )
{
     if( mEntity )
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


::nECS::cEntity *
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


 cTreeWrapperNodeComponent::cTreeWrapperNodeComponent( cTreeWrapperNode* iParent, ::nECS::cComponent* iComponent ) :
    tSuperClass( iParent ),
     mComponent( iComponent )
{
     if( mComponent )
        AppendData( mComponent->Name().c_str() );
     else
        AppendData( "New Component" );


     AppendData( "" );
}


std::string
cTreeWrapperNodeComponent::Type() const
{
    return  "Component";
}


::nECS::cComponentGeneric *
cTreeWrapperNodeComponent::Component()
{
    return  dynamic_cast< ::nECS::cComponentGeneric* >(mComponent);
}


// ===========================================================================
// ===========================================================================
// ===========================================================================


cTreeWrapperNodeVariable::~cTreeWrapperNodeVariable()
{
}


cTreeWrapperNodeVariable::cTreeWrapperNodeVariable( cTreeWrapperNode * iParent, ::nECS::cComponentGeneric* iComponent, int iVarIndex ) :
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


bool
cTreeWrapperNodeVariable::SetData( int iIndex, const QVariant & iData )
{
    if( iIndex == 0 ) // Setting variable name
    {
        tSuperClass::SetData( 0, iData );
    }
    else if( iIndex == 1 )
    {
        ::nBase::cVariant* var = mComponent->GetVarAtIndex( mVarIndex );
        if( var->Type() == ::nBase::kNumber )
        {
            var->SetValueNumber( iData.toDouble() );
        }
        else if( var->Type() == ::nBase::kString )
        {
            var->SetValueString( iData.toString().toStdString() );
        }
        else if( var->Type() == ::nBase::kBoolean )
        {
            var->SetValueBool( iData.toBool() );
        }

        tSuperClass::SetData( 1, iData );
    }

    return false;
}

} //nModels
} //nQt

