#pragma once

#ifdef USE_RIVET

#include <QWidget>
#include <RivetTabArea>


namespace nEditor { namespace nWidgets { class cMainTools; } }


class QSplitter;
class cProjectEditor;


namespace nEditor {
namespace nWidgets {


class cMainContent :
    public QWidget
{
    Q_OBJECT

    typedef QWidget tSuperClass;

public:
    // This is probably a bad idea in terms of organisation but we try if it fits
    struct cAccessibleChildren
    {
        QWidget*            mControlBar;
        QWidget*            mNavBar;
        ::Rivet::TabArea*   mScreensTabArea;
        cProjectEditor*     mProjectTreeEditor;
    };

public:
    // Construction / Destruction
    virtual  ~cMainContent();
    cMainContent( QWidget*  parent = NULL );

public:
    // Accessible Children
    cAccessibleChildren  AccessibleChildren()  const;

protected:
    // Event
    virtual  void  resizeEvent( QResizeEvent*   event )     override;

private:
    // GUI utilities
    void  Init();
    void  Build();
    void  Compose();
    void  Destroy();

private:
    // Data;
    QWidget* mControlBar;
    QWidget* mNavBar;
    ::Rivet::TabArea* mScreensTabArea;

    cProjectEditor* mProjectTreeEditor;

    QSplitter* mSplitterHorizontal;
    QSplitter* mSplitterVertical;

    QWidget* mPlaceholderA;
    cMainTools* mTools;
};


} // nWidgets
} // nEditor

#endif // USE_RIVET
