#include "Editor.BoltQtWidgets.TestCanvas.h"

#include "Editor.Application.EditorApplication.h"

#include "Core.ECS.Utilities.EntityParser.h"
#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Core.World.h"

#include "Core.ECS.Component.Position.h"

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
MyCanvas::SetEditorApp( ::nApplication::cEditorApplication * iEditorApp )
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
    ::nECS::cEntityParser* ep = ::nECS::cEntityParser::Instance();

    std::string name = mCurrentPrototypeEntitySelected.data( Qt::DisplayRole ).toString().toStdString();
    ::nECS::cEntity* theEnti = ep->CreateEntityFromPrototypeMap( name.c_str() );
    auto position = dynamic_cast< ::nECS::cPosition* >( theEnti->GetComponentByName( "position" ) );
    if( position )
    {
        position->X( iEvent->localPos().x() );
        position->Y( iEvent->localPos().y() );
    }
    mEditorApp->World()->AddEntity( theEnti );

    printf( "Added : %s\n", name.c_str() );

    tSuperClass::mouseDoubleClickEvent( iEvent );
}


void
MyCanvas::CurrentPrototypeChanged( const QModelIndex& iIndex )
{
    mCurrentPrototypeEntitySelected = iIndex;
}

