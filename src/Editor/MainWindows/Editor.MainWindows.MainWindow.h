#pragma once

#ifdef USE_RIVET

#include <RivetCustomMainWindow>


namespace nCore { namespace nProject { class cProject; } }
namespace nEditor { namespace nWidgets { class cMainCaption; } }
namespace nEditor { namespace nWidgets { class cMainContent; } }
namespace nQt { namespace  nModels { class cProjectHierarchyModel; } }
namespace nQt { namespace nModels { class cEntityListModel; } }


namespace nEditor {
namespace nMainWindows {


class cMainWindow :
    public ::Rivet::CustomMainWindow
{
    Q_OBJECT

    typedef ::Rivet::CustomMainWindow   tSuperClass;
    typedef cMainWindow                 tSelf;

public:
    // Construction / Destruction
    virtual  ~cMainWindow();
    cMainWindow( QWidget*  parent = NULL );

public slots:
    // Slots
    void  NewProjectDialog();
    void  OpenProjectDialog();

private:
    // GUI utilities
    void  Init();
    void  Build();
    void  Compose();
    void  Destroy();

private:
    ::nEditor::nWidgets::cMainCaption* mMainCaptionWidget;
    ::nEditor::nWidgets::cMainContent* mMainContentWidget;

    ::nCore::nProject::cProject*            mProject;
    ::nQt::nModels::cEntityListModel*       mEntityListModel;
    ::nQt::nModels::cProjectHierarchyModel* mProjectHierarchyModel;

};


} // nMainWindows
} // nEditor

#endif // USE_RIVET
