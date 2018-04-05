#include "QSFMLCanvas.h"

class cEditorApplication;

class MyCanvas :
    public QSFMLCanvas
{
public:
    MyCanvas( QWidget* Parent, const QPoint& Position, const QSize& Size );
    MyCanvas( QWidget* Parent );

public:
    void SetEditorApp( cEditorApplication* iEditorApp );

private:
    virtual void OnInit();
    virtual void OnUpdate();
    virtual void paintEvent( QPaintEvent* );

private:
    cEditorApplication* mEditorApp;
};

