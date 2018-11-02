#include "Editor.Widgets.MainCaption.h"

#ifdef USE_RIVET

#include <Editor.Widgets.MainCaptionMenuBar.h>


#include <QLabel>


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------- Default values defines


#define  DEFAULT_TITLE "Bolt Editor"


namespace nEditor {
namespace nWidgets {


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cMainCaption::~cMainCaption()
{
    tSelf::Destroy();
}


cMainCaption::cMainCaption( QWidget*  parent ) :
    tSuperClass( parent ),
    mTitle( NULL ),
    mMenuBar( NULL )
{
    tSelf::Init();
    tSelf::Build();
    tSelf::Compose();
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------- HitTest override


bool
cMainCaption::HitEmptySpace( long iX, long iY )
{
    QPoint local( iX, iY );
    bool result = true;

    QList< QWidget* > list = this->findChildren< QWidget* >();

    // If a direct child contains our mouse coordinates, we refute.
    for each( QWidget* w in list ) {
        QRect g = w->geometry();
        if( g.contains( local ) && w->parent() == this )
        {
            if( w == mTitle ) continue;

            result = false;
        }
    }

    return  result;
}


//--------------------------------------------------------------------------------------
//--------------------------------------------------------- Restricted Member access API


cMainCaptionMenuBar*
cMainCaption::MenuBar()  const
{
    return  mMenuBar;
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------ GUI utilities


void
cMainCaption::Init()
{
    mTitle = new QLabel( this );
    mMenuBar = new cMainCaptionMenuBar( this );
}


void
cMainCaption::Build()
{
    mTitle->setText( DEFAULT_TITLE );
    mTitle->resize( mTitle->minimumSizeHint() );

    mTitle->setObjectName( "Title" );
    mMenuBar->setObjectName( "MenuBar" );
    //DEBUG:TMP
    //move to qss
    mTitle->setStyleSheet( "color:white; background:transparent;" );
    mMenuBar->setStyleSheet( "QMenuBar { background:transparent; }" );
}


void
cMainCaption::Compose()
{
    tSuperClass::Compose(); // Important !

    mTitle->resize( mTitle->sizeHint() );
    int title_padding = this->height() - mTitle->height();
    int title_padding2 = title_padding / 2;
    mTitle->move( title_padding2, title_padding2 );

    mMenuBar->resize( mMenuBar->sizeHint() );
    int menubar_padding = this->height() - mMenuBar->height();
    int menubar_padding2 = menubar_padding / 2;
    int menubar_x = mTitle->geometry().right() + menubar_padding;
    mMenuBar->move( menubar_x, menubar_padding2 );
}


void
cMainCaption::Destroy()
{
    delete  mTitle;
    mTitle = 0;

    delete  mMenuBar;
    mMenuBar = 0;
}


} // nWidgets
} // nEditor

#endif // USE_RIVET
