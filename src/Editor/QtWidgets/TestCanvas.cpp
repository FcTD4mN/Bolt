#include "TestCanvas.h"

#include "Application/EditorApplication.h"

MyCanvas::MyCanvas( QWidget* Parent, const QPoint& Position, const QSize& Size ) :
    QSFMLCanvas( Parent, Position, Size )
{
}


MyCanvas::MyCanvas( QWidget* Parent ) :
    QSFMLCanvas( Parent )
{
}


void
MyCanvas::OnInit()
{
    mEditorApp = cEditorApplication::App();
    mEditorApp->Initialize();
}

void
MyCanvas::OnUpdate()
{
    // We don't want the world to update actually in the editor
    //mEditorApp->Update( 0 );
}

void
MyCanvas::paintEvent( QPaintEvent* )
{
    mRenderWindow->clear();
    mEditorApp->Draw( mRenderWindow );
    mRenderWindow->display();
}

