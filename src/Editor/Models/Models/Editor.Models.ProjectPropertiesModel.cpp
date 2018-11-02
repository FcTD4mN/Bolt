#include "Editor.Models.ProjectPropertiesModel.h"

#include "Core.Project.Project.h"

#include "Editor.Models.TreeWrapperProjectProperties.h"

namespace  nQt {
namespace  nModels {


cProjectPropertiesModel::~cProjectPropertiesModel()
{
}


cProjectPropertiesModel::cProjectPropertiesModel( ::nCore::nProject::cProject* iProject, QObject* iParent ) :
    tSuperClass( iParent ),
    mProject( iProject )
{
    BuildData();
}


cProjectPropertiesModel::cProjectPropertiesModel( cProjectPropertiesModel & iRef ) :
    mProject( iRef.mProject )
{
    BuildData();
}


// --------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------ Interface Overrides
// --------------------------------------------------------------------------------------------------------------


Qt::ItemFlags
cProjectPropertiesModel::flags( const QModelIndex & iIndex ) const
{
    if( !iIndex.isValid() )
        return 0;

    return Qt::ItemIsEditable | QAbstractItemModel::flags( iIndex );
}


void
cProjectPropertiesModel::BuildData()
{
    if( mRootItem )
        return;

    mRootItem = new cTreeWrapperNode( 0 );
    mRootItem->AppendData( "Name" );
    mRootItem->AppendData( "Value" );

    if( !mProject )
        return;

    cTreeWrapperNodeProjectProperties* projectName = new cTreeWrapperNodeProjectProperties( mRootItem, mProject );
    projectName->AppendData( "Project Name" );

    cTreeWrapperNodeProjectProperties* resolutionWidth = new cTreeWrapperNodeProjectProperties( mRootItem, mProject );
    resolutionWidth->AppendData( "Resolution Width" );

    cTreeWrapperNodeProjectProperties* resolutionHeight = new cTreeWrapperNodeProjectProperties( mRootItem, mProject );
    resolutionHeight->AppendData( "Resolution Height" );

    cTreeWrapperNodeProjectProperties* framerate = new cTreeWrapperNodeProjectProperties( mRootItem, mProject );
    framerate->AppendData( "Limit Framerate" );
}

} //nQt
} //nModels
