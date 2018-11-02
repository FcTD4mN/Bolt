#include "Editor.Models.SystemModel.h"

#include "Core.ECS.Core.Entity.h"

#include "Editor.Models.TreeWrapperSystem.h"

namespace  nQt {
namespace  nModels {


cSystemModel::~cSystemModel()
{
}


cSystemModel::cSystemModel( ::nCore::nECS::nCore::cSystem* iSystem, QObject* iParent ) :
    tSuperClass( iParent ),
    mSystem( iSystem )
{
    BuildData();
}


cSystemModel::cSystemModel( cSystemModel & iRef ) :
    mSystem( iRef.mSystem )
{
    BuildData();
}


// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------ Interface Overrides
// --------------------------------------------------------------------------------------------------------------


Qt::ItemFlags
cSystemModel::flags( const QModelIndex & iIndex ) const
{
    if( !iIndex.isValid() )
        return 0;

    return  QAbstractItemModel::flags( iIndex );


    // Right now, nothing can be edited via editor
    // Right now, nothing can be edited via editor
    // Right now, nothing can be edited via editor
    // because systems are never created in editor, all systems visible are c++ integrated systems, that already have a name and a connection to event set or notset
    // so there is nothing to do here in the editor really
    if( iIndex.column() == 0 )
        return  QAbstractItemModel::flags( iIndex );

    auto node = dynamic_cast< cTreeWrapperNodeSystem* >( ExtractTreeWrapper( iIndex ) );
    if( node )
    {
        if( node->DataAtColumn( 0 ) == "System Name" ) // Can't edit name for now, when we allow it, don't forget to maintain the register etc...
            return  QAbstractItemModel::flags( iIndex );
    }

    return  Qt::ItemIsEditable | QAbstractItemModel::flags( iIndex );
}


void
cSystemModel::BuildData()
{
    if( mRootItem )
        return;

    mRootItem = new cTreeWrapperNode( 0 );
    mRootItem->AppendData( "Name" );
    mRootItem->AppendData( "Value" );

    if( !mSystem )
        return;

    cTreeWrapperNodeSystem* name   = new cTreeWrapperNodeSystem( mRootItem, mSystem );
    name->AppendData( "System Name" );
    cTreeWrapperNodeSystem* eventsNode   = new cTreeWrapperNodeSystem( mRootItem, mSystem );
    eventsNode->AppendData( "Connected to Events" );
}

} //nQt
} //nModels
