#include "Editor.BoltQtModels.TreeWrapperComponent.h"

#include "Core.ECS.Core.Component.h"
#include "Core.ECS.Utilities.ComponentRegistry.h"
#include "Core.Base.Variant.h"

namespace nQt {
namespace nModels {


cTreeWrapperNodeComponentEditor::~cTreeWrapperNodeComponentEditor()
{
}


 cTreeWrapperNodeComponentEditor::cTreeWrapperNodeComponentEditor( cTreeWrapperNode* iParent, ::nECS::cComponent* iComponent ) :
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
cTreeWrapperNodeComponentEditor::Type() const
{
    return  "Component";
}


void
cTreeWrapperNodeComponentEditor::AddChild()
{
    ::nECS::cComponentGeneric* componentGen = Component();
    if( componentGen )
    {
        std::string varName = "NewVariable";
        int i = 1;
        while( componentGen->GetVar( varName ) != nullptr )
        {
            varName = "NewVariable" + std::to_string( i );
            ++i;
        }

        componentGen->SetVar( varName, new ::nBase::cNumber( 0.0 ) );
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
        ::nECS::cComponentGeneric* componentGen = Component();
        componentGen->RemoveVar( varName.toStdString() );
    }

   return  tSuperClass::RemoveChildrenAtIndex( iIndex, iCount );
}


::nECS::cComponentGeneric *
cTreeWrapperNodeComponentEditor::Component()
{
    return  dynamic_cast< ::nECS::cComponentGeneric* >( mComponent );
}


// ===========================================================================
// ===========================================================================
// ===========================================================================


cTreeWrapperNodeComponentEditorVariable::~cTreeWrapperNodeComponentEditorVariable()
{
}


cTreeWrapperNodeComponentEditorVariable::cTreeWrapperNodeComponentEditorVariable( cTreeWrapperNode * iParent, ::nECS::cComponentGeneric* iComponent, const std::string& iVarName ) :
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
            mComponent->SetVar( mVarName, new ::nBase::cNumber( 0.0 ) );
        }
        else if( newType == "String" )
        {
            mComponent->SetVar( mVarName, new ::nBase::cString( "" ) );
        }
        else if( newType == "Boolean" )
        {
            mComponent->SetVar( mVarName, new ::nBase::cBoolean( true ) );
        }

        tSuperClass::SetData( 1, iData );
    }

    return false;
}

} //nModels
} //nQt

