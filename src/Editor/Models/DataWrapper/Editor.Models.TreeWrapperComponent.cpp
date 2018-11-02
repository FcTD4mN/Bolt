#include "Editor.Models.TreeWrapperComponent.h"

#include "Core.ECS.Core.Component.h"
#include "Core.Registries.ComponentRegistry.h"
#include "Core.Base.Variant.h"

namespace nQt {
namespace nModels {


cTreeWrapperNodeComponentEditor::~cTreeWrapperNodeComponentEditor()
{
}


 cTreeWrapperNodeComponentEditor::cTreeWrapperNodeComponentEditor( cTreeWrapperNode* iParent, ::nCore::nECS::nCore::cComponent* iComponent ) :
    tSuperClass( iParent ),
     mComponent( iComponent )
{
}


std::string
cTreeWrapperNodeComponentEditor::Type() const
{
    return  "Component";
}


void
cTreeWrapperNodeComponentEditor::AddChild()
{
    ::nCore::nECS::nCore::cComponentGeneric* componentGen = Component();
    if( componentGen )
    {
        std::string varName = "NewVariable";
        int i = 1;
        while( componentGen->GetVar( varName ) != nullptr )
        {
            varName = "NewVariable" + std::to_string( i );
            ++i;
        }

        componentGen->AddNewVariable( varName, new ::nCore::nBase::cNumber( 0.0 ) );
        new cTreeWrapperNodeComponentEditorVariable( this, componentGen, varName );
    }
}


bool
cTreeWrapperNodeComponentEditor::RemoveChildrenAtIndex( int iIndex, int iCount )
{
    if( iIndex < 0 || iIndex + iCount > mChildren.size() )
        return false;

    for( int i = 0; i < iCount; ++i )
    {
        QString varName = mChildren[ iIndex + i ]->DataAtColumn( 0 ).toString();
        ::nCore::nECS::nCore::cComponentGeneric* componentGen = Component();
        componentGen->RemoveVar( varName.toStdString() );
    }

   return  tSuperClass::RemoveChildrenAtIndex( iIndex, iCount );
}


int
cTreeWrapperNodeComponentEditor::DataCount() const
{
    return  2;
}


QVariant
cTreeWrapperNodeComponentEditor::DataAtColumn( int iColumn )
{
    if( iColumn == 0 )
        return  "Name";
    else
        return  mComponent->Name().c_str();
}


bool
cTreeWrapperNodeComponentEditor::SetData( int iIndex, const QVariant & iData )
{
    if( iIndex == 1 )
    {
        auto componentReg = ::nCore::nRegistries::cComponentRegistry::Instance();
        auto filename = componentReg->GetItemFileByItemName( mComponent->Name() );

        // We update index id
        componentReg->UnregisterItemByName( mComponent->Name() );
        mComponent->Name( iData.toString().toStdString() );
        componentReg->RegisterItem( mComponent->Name(), mComponent );

        componentReg->SetItemFileUsingItemName( mComponent->Name(), filename );
    }

    return  true;
}


::nCore::nECS::nCore::cComponentGeneric*
cTreeWrapperNodeComponentEditor::Component()
{
    return  dynamic_cast< ::nCore::nECS::nCore::cComponentGeneric* >( mComponent );
}


// ===========================================================================
// ===========================================================================
// ===========================================================================


cTreeWrapperNodeComponentEditorVariable::~cTreeWrapperNodeComponentEditorVariable()
{
}


cTreeWrapperNodeComponentEditorVariable::cTreeWrapperNodeComponentEditorVariable( cTreeWrapperNode * iParent, ::nCore::nECS::nCore::cComponentGeneric* iComponent, const std::string& iVarName ) :
    tSuperClass( iParent ),
    mComponent( iComponent ),
    mVarName( iVarName )
{
    if( mComponent )
    {
        AppendData( mVarName.c_str() );
        AppendData( mComponent->GetVar( mVarName )->TypeAsString().c_str() );
    }
    else
    {
        AppendData( ( "New Variable" + std::to_string( mComponent->VarCount() ) ).c_str() );
        AppendData( "Type" );
    }
}


std::string
cTreeWrapperNodeComponentEditorVariable::Type() const
{
    return  "Variable";
}


void
cTreeWrapperNodeComponentEditorVariable::AddChild()
{
    // Do nothing, we can't add child to variables
}


bool
cTreeWrapperNodeComponentEditorVariable::SetData( int iIndex, const QVariant & iData )
{
    if( iIndex == 0 ) // Setting variable name
    {
        tSuperClass::SetData( 0, iData );
        mComponent->RenameVar( mVarName, iData.toString().toStdString() );
        mVarName = iData.toString().toStdString();
    }
    else if( iIndex == 1 )
    {
        QString newType = iData.toString();

        if( newType == mData[ 1 ] )
        {
            return  false;
        }
        else if( newType == "Number" )
        {
            mComponent->AddNewVariable( mVarName, new ::nCore::nBase::cNumber( 0.0 ) );
        }
        else if( newType == "String" )
        {
            mComponent->AddNewVariable( mVarName, new ::nCore::nBase::cString( "" ) );
        }
        else if( newType == "Boolean" )
        {
            mComponent->AddNewVariable( mVarName, new ::nCore::nBase::cBoolean( true ) );
        }

        tSuperClass::SetData( 1, iData );
    }

    return false;
}

} //nModels
} //nQt

