#include "TestCanvas.h"

#include "Application/EditorApplication.h"

#include "ECS/Utilities/EntityParser.h"
#include "ECS/Core/World.h"

#include <QtGui/QInputEvent>

MyCanvas::MyCanvas( QWidget* Parent, const QPoint& Position, const QSize& Size ) :
    QSFMLCanvas( Parent, Position, Size )
{
}


MyCanvas::MyCanvas( QWidget* Parent ) :
    QSFMLCanvas( Parent )
{
}


void
MyCanvas::SetEditorApp( cEditorApplication * iEditorApp )
{
    mEditorApp = iEditorApp;
}


void
MyCanvas::OnInit()
{
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
    mRenderWindow->clear( sf::Color( 200, 200, 200 ) );
    mEditorApp->Draw( mRenderWindow );
    mRenderWindow->display();
}


//===========================================================================================================
//=========================================================================================== Event Overrides
//===========================================================================================================


void
MyCanvas::mouseReleaseEvent( QMouseEvent* iEvent )
{
    tSuperClass::mouseReleaseEvent( iEvent );
}


void
MyCanvas::mouseDoubleClickEvent( QMouseEvent * iEvent )
{
    cEntityParser* ep = cEntityParser::Instance();

    std::string name = mCurrentPrototypeEntitySelected.data( Qt::DisplayRole ).toString().toStdString();
    mEditorApp->World()->AddEntity( ep->CreateEntityFromPrototypeMap( name.c_str() ) );

    printf( "Added : %s\n", name.c_str() );

    tSuperClass::mouseDoubleClickEvent( iEvent );
}


void
MyCanvas::CurrentPrototypeChanged( const QModelIndex& iIndex )
{
    mCurrentPrototypeEntitySelected = iIndex;
}
