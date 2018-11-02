#pragma once

#ifdef USE_RIVET

#include <QWidget>
#include <RivetTabArea>


class QStackedWidget;


namespace nEditor {
namespace nWidgets {


class cMainTools :
    public QWidget
{
    Q_OBJECT

    typedef QWidget tSuperClass;

public:
    // Construction / Destruction
    virtual  ~cMainTools();
    cMainTools( QWidget*  parent = NULL );

protected:
    // Event
    virtual  void  resizeEvent( QResizeEvent*   event )  override;

private:
    // GUI utilities
    void  Init();
    void  Build();
    void  Compose();
    void  Destroy();

private:
    // Data;
    ::Rivet::TabArea*   mToolsTabArea;
    QWidget*            mToolsWrapper;
    QStackedWidget*     mStack;
};


} // nWidgets
} // nEditor

#endif // USE_RIVET
