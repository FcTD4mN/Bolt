#include "Editor.BoltQtMainWindows.BoltEditor.h"

#include "Editor.Application.EditorApplication.h"
#include "Editor.BoltQtModels.EntityListModel.h"

#include <QtWidgets/QTableView>

namespace nQt {

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
    mApp = ::nApplication::cEditorApplication::App();
    mApp->Initialize();

    ui.widget->SetEditorApp( mApp );

    mModel = new ::nQt::nModels::cEntityListModel( 0 );
    ui.listView->setModel( mModel );

    connect(
        ui.listView, &QListView::clicked,
        ui.widget, &MyCanvas::CurrentPrototypeChanged
    );

}

} //nQt
