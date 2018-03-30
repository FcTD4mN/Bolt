#include "QSFMLCanvas.h"

#include "Application/EditorApplication.h"

class MyCanvas :
    public QSFMLCanvas
{
public:

    MyCanvas( QWidget* Parent, const QPoint& Position, const QSize& Size ) :
        QSFMLCanvas( Parent, Position, Size )
    {
    }

private:
    virtual void OnInit()
    {
        mEditorApp = cEditorApplication::App();
        mEditorApp->Initialize();
    }

    virtual void OnUpdate()
    {
        // We don't want the world to update actually in the editor
        //mEditorApp->Update( 0 );
    }

    virtual void paintEvent( QPaintEvent* )
    {
        mRenderWindow->clear();
        mEditorApp->Draw( mRenderWindow );
        mRenderWindow->display();
    }

private:
    cEditorApplication* mEditorApp;
};

