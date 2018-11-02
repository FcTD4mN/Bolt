#include "Editor.Widgets.Editors.DrawingToolEditor.h"


#include "Core.Animation.Animation.h"

#include "Editor.Models.DrawingToolModelBase.h"


#include <QColorDialog>


cDrawingToolEditor::~cDrawingToolEditor()
{
    delete  mTreeView;
    delete  mMainLayout;
    delete  mModelDelegate;
}


cDrawingToolEditor::cDrawingToolEditor( QWidget * iParent ) :
    tSuperClass( iParent ),
    mDrawingToolModelBase( 0 ),
    mModelDelegate( 0 )
{
    setFixedWidth( 200 );

    mTreeView = new  QTreeView( this );
    mMainLayout = new QHBoxLayout();
    mMainLayout->addWidget( mTreeView );
    mTreeView->setEditTriggers( QAbstractItemView::AllEditTriggers );

    setLayout( mMainLayout );
}


void
cDrawingToolEditor::ShowTool( ::nQt::nModels::cDrawingToolModelBase* iDrawingToolModelBase )
{
    mDrawingToolModelBase = iDrawingToolModelBase;

    mTreeView->setModel( mDrawingToolModelBase );
    mTreeView->resizeColumnToContents( 0 );
    mTreeView->resizeColumnToContents( 1 );


    mModelDelegate = mDrawingToolModelBase->CreateModelDelegate();
    if( mModelDelegate )
    {
        delete  mTreeView->itemDelegate(); // So we don't forget to delete the default one when first showing tool
        mTreeView->setItemDelegate( mModelDelegate );
    }
}

