#include "QSFMLCanvas.h"

#include <QtCore/QModelIndex>

class cEditorApplication;

class MyCanvas :
    public QSFMLCanvas
{
public:
    typedef QSFMLCanvas tSuperClass;

public:
    MyCanvas( QWidget* Parent, const QPoint& Position, const QSize& Size );
    MyCanvas( QWidget* Parent );

public:
    void SetEditorApp( cEditorApplication* iEditorApp );

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
    cEditorApplication* mEditorApp;
    QModelIndex         mCurrentPrototypeEntitySelected;
};

