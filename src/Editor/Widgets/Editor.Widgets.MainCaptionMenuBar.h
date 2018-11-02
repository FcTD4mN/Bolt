#pragma once


#include <QMenuBar>


class QAction;
class QMenu;


namespace nEditor {
namespace nWidgets {


class cMainCaptionMenuBar :
    public QMenuBar
{
    Q_OBJECT

    typedef QMenuBar                tSuperClass;
    typedef cMainCaptionMenuBar     tSelf;

public:
    // Construction / Destruction
    virtual  ~cMainCaptionMenuBar();
    cMainCaptionMenuBar( QWidget*  parent = NULL );

private:
    // GUI utilities
    void  Init();
    void  Build();
    void  Compose();
    void  Destroy();

public:
    QMenu* mMenuFile;
        QAction* mActionNew;
        QAction* mActionOpen;
        QAction* mActionSave;
        QAction* mActionSaveAs;
        QAction* mActionExit;
    QMenu* mMenuEdit;
    QMenu* mMenuView;
    QMenu* mMenuAbout;
};


} // nWidgets
} // nEditor

