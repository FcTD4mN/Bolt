#include "Editor.BoltQtWidgets.QSFMLCanvas.h"

#include <QtCore/QModelIndex>

namespace nApplication { class cEditorApplication; }


class MyCanvas :
    public QSFMLCanvas
{
public:
    typedef QSFMLCanvas tSuperClass;

public:
    MyCanvas( QWidget* Parent, const QPoint& Position, const QSize& Size );
    MyCanvas( QWidget* Parent );

public:
    void SetEditorApp( ::nApplication::cEditorApplication* iEditorApp );

private:
    virtual void OnInit();
    virtual void OnUpdate();
    virtual void paintEvent( QPaintEvent* );

public:
    // Event overrides
    virtual void mouseReleaseEvent( QMouseEvent *iEvent ) override;
    virtual void mouseDoubleClickEvent( QMouseEvent *iEvent ) override;

public slots:
    void CurrentPrototypeChanged( const QModelIndex& iIndex );

private:
    ::nApplication::cEditorApplication* mEditorApp;
    QModelIndex                         mCurrentPrototypeEntitySelected;
};


