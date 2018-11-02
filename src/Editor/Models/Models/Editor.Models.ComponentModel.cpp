#include "Editor.Models.ComponentModel.h"

#include "Core.ECS.Core.Component.h"

#include "Core.Registries.ComponentRegistry.h"


#include "Editor.Delegates.ComponentProperties.h"

#include "Editor.Models.TreeWrapper.h"
#include "Editor.Models.TreeWrapperComponent.h"



namespace  nQt {
namespace  nModels {


cComponentModel::~cComponentModel()
{
}


cComponentModel::cComponentModel( ::nCore::nECS::nCore::cComponent* iComponent, QObject* iParent ) :
    tSuperClass( iParent ),
    mComponent( iComponent ),
    mVariableParentNode( 0 )
{
    BuildData();
}


cComponentModel::cComponentModel( cComponentModel & iRef ) :
    mComponent( iRef.mComponent ),
    mVariableParentNode( 0 )
{
    BuildData();
}


// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------ Interface Overrides
// --------------------------------------------------------------------------------------------------------------


Qt::ItemFlags
cComponentModel::flags( const QModelIndex & iIndex ) const
{
    if( !iIndex.isValid() )
        return 0;

    auto item = ExtractTreeWrapper( iIndex );
    if( item->Type() == "Component" && iIndex.column() == 0 ) // Can't edit the "Name" field, which is the name of the property
        return  QAbstractItemModel::flags( iIndex );
    else if( item->Type() == "BaseNode" && iIndex.column() == 0 ) // Can't edit the "folder" nodes
        return  QAbstractItemModel::flags( iIndex );

    return Qt::ItemIsEditable | QAbstractItemModel::flags( iIndex );
}


bool
cComponentModel::insertColumns( int position, int columns, const QModelIndex & parent )
{
    return  false; // Can't add columns
}


bool
cComponentModel::removeColumns( int iIndex, int iCount, const QModelIndex & parent )
{
    return  false; // Can't remove columns
}


bool
cComponentModel::insertRows( int iIndex, int iCount, const QModelIndex & parent )
{
    return  false; // Can't use this basic function
}


bool
cComponentModel::removeRows( int iIndex, int iCount, const QModelIndex & iParent )
{
    return  false; // Can't use this basic function
}


void
cComponentModel::BuildData()
{
    if( mRootItem )
        return;

    mRootItem = new cTreeWrapperNode( 0 );
    mRootItem->AppendData( "Name" );
    mRootItem->AppendData( "Type" );

    cTreeWrapperNodeComponentEditor* nameRoot = new  cTreeWrapperNodeComponentEditor( mRootItem, mComponent );

    mVariableParentNode = new cTreeWrapperNode( mRootItem );
    mVariableParentNode->AppendData( "Variables" );
    mVariableParentNode->AppendData( "" );

    auto compAsGen = dynamic_cast<::nCore::nECS::nCore::cComponentGeneric*>( mComponent );
    if( compAsGen )
    {
        for( int j = 0; j < compAsGen->VarCount(); ++j )
        {
            ::nCore::nBase::cVariant* var = compAsGen->GetVarAtIndex( j );
            auto varNode = new cTreeWrapperNodeComponentEditorVariable( mVariableParentNode, compAsGen, compAsGen->GetVarNameAtIndex( j ) );
        }
    }
}


// --------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------- ContextualMenu
// --------------------------------------------------------------------------------------------------------------


QStringList
cComponentModel::ContextualMenuAllowedActionForIndex( QModelIndex iIndex )
{
    QStringList outputList;

    auto treeNode = dynamic_cast< cTreeWrapperNode* >( ExtractTreeWrapper( iIndex ) );

    // VARIABLES
    if( treeNode->Type() == "BaseNode" && treeNode->DataAtColumn( 0 ) == "Variables" )
    {
        outputList.push_back( "Add" ); // OK
    }
    else if( treeNode->Type() == "Variable" ) // OK
    {
        outputList.push_back( "Delete" ); // OK
    }

    return  outputList;
}


void
cComponentModel::ExecuteActionOnIndex( const QString & iAction, const QModelIndex & iIndex )
{
    auto treeNode = dynamic_cast< cTreeWrapperNode* >( ExtractTreeWrapper( iIndex ) );

    if( treeNode->Type() == "BaseNode" && treeNode->DataAtColumn( 0 ) == "Variables" && iAction == "Add" )
        AddNewVariable();
    else if( treeNode->Type() == "Variable" && iAction == "Delete" )
        RemoveVariable( iIndex );
}


// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------- ItemDelegate
// --------------------------------------------------------------------------------------------------------------


QStyledItemDelegate *
cComponentModel::CreateModelDelegate()
{
    auto theDelegate = new cComponentEditorDelegate();
    theDelegate->SetModel( this );
    return  theDelegate;
}


// --------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------- Variable controls
// --------------------------------------------------------------------------------------------------------------


bool
cComponentModel::AddNewVariable()
{
    auto compAsGen = dynamic_cast<::nCore::nECS::nCore::cComponentGeneric*>( mComponent );
    if( !compAsGen )
        return  false;

    int lastElementIndex = mVariableParentNode->ChildrenCount();

    if( compAsGen )
    {
        beginInsertRows( GetModelIndexFromWrapper( mVariableParentNode ), lastElementIndex, lastElementIndex );

        std::string varName = "NewVariable";
        int i = 1;
        while( compAsGen->GetVar( varName ) != nullptr )
        {
            varName = "NewVariable" + std::to_string( i );
            ++i;
        }

        compAsGen->AddNewVariable( varName, new ::nCore::nBase::cNumber( 0.0 ) );
        new cTreeWrapperNodeComponentEditorVariable( mVariableParentNode, compAsGen, varName );

        endInsertRows();
    }

    return  true;
}


bool
cComponentModel::RemoveVariable( const QModelIndex & iIndex )
{
    cTreeWrapperNode* item = ExtractTreeWrapper( iIndex );
    cTreeWrapperNode* parent = item->Parent();
    bool result = false;

    if( parent && parent->Type() == "BaseNode" && parent->DataAtColumn( 0 ) == "Variables" )
    {
        beginRemoveRows( iIndex.parent(), iIndex.row(), iIndex.row() );

        result = parent->RemoveChildrenAtIndex( iIndex.row(), 1 );

        endRemoveRows();
    }

    return  result;
}

} //nQt
} //nModels
