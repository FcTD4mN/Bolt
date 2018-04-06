#include "BoltEditor.h"

#include "Application/EditorApplication.h"
#include "QtModels/QtModels.EntityListModel.h"

#include "QtWidgets/qtableview.h"


cBoltEditor::~cBoltEditor()
{
    delete  mModel;
}


cBoltEditor::cBoltEditor( QWidget *parent ) :
    QMainWindow( parent )
{
    ui.setupUi( this );
}


void
cBoltEditor::Setup()
{
    mApp = cEditorApplication::App();
    mApp->Initialize();

    ui.widget->SetEditorApp( mApp );

    mModel = new cEntityListModel( 0 );
    ui.listView->setModel( mModel );

    connect(
        ui.listView, &QListView::clicked,
        ui.widget, &MyCanvas::CurrentPrototypeChanged
    );

}

