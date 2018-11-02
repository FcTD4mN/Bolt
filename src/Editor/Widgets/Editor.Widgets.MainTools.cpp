#include "Editor.Widgets.MainTools.h"

#ifdef USE_RIVET

#include <RivetDockingCallbackLibrary>
#include <RivetMonacoWidget>


#include <QStackedWidget>


namespace nEditor {
namespace nWidgets {


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cMainTools::~cMainTools()
{
    Destroy();
}


cMainTools::cMainTools( QWidget*  parent ) :
    tSuperClass( parent ),
    mToolsTabArea( NULL ),
    mToolsWrapper( NULL ),
    mStack( NULL )
{
    Init();
    Build();
    Compose();
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Event


void
cMainTools::resizeEvent( QResizeEvent* event )
{
    tSuperClass::resizeEvent( event );
    Compose();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------ GUI utilities


void
cMainTools::Init()
{
    mToolsWrapper = new QWidget( this );
    mToolsTabArea = new ::Rivet::TabArea( mToolsWrapper );
    mStack = new QStackedWidget( this );
}


void
cMainTools::Build()
{
    mToolsWrapper->setObjectName( "Wrap" );
    mToolsTabArea->setObjectName( "ToolsTabArea" );
    mStack->setObjectName( "Stack" );

    //TMP:DEBUG
    //move to qss
    mStack->setStyleSheet( "background: rgb( 40, 40, 40 ); border: 1px solid rgb( 20, 20, 20 );" );
    mToolsWrapper->setStyleSheet( "background: rgb( 40, 40, 40 ); border: 1px solid rgb( 20, 20, 20 );" );

    mToolsTabArea->SetOverlap( 10 );
    mToolsTabArea->SetTabsClosable( false );
    mToolsTabArea->SetTabsShapeStyle( ::Rivet::Tab::eShapeStyle::kLine );
    mToolsTabArea->SetOnTabDroppedOutCB( ::Rivet::OnTabDroppedOutCB_RevertBack );
    mToolsTabArea->SetLinkedStack( mStack );
    mToolsTabArea->SetTag( "tools" );

    ::Rivet::SetMonacoPrefix( "/resources/Editor" );
    for( int i = 0; i < 2; ++i )
    {
        auto t = new ::Rivet::Tab();
        auto w = new ::Rivet::MonacoWidget();
        t->SetColor( QColor( 60, 60, 60 ) );
        t->SetFadeColor( QColor( 30, 30, 30 ) );
        t->SetLinkWidget( w );
        mToolsTabArea->ManualAddNewTab( t );
    }
}


void
cMainTools::Compose()
{
    mToolsWrapper->setGeometry( 0, 0, width(), 30 );
    mToolsTabArea->resize( mToolsWrapper->size() );
    mStack->setGeometry( 0, 30, width(), height() - 30 );
}


void
cMainTools::Destroy()
{
    delete  mToolsTabArea;
    delete  mToolsWrapper;
    delete  mStack;
}


} // nWidgets
} // nEditor

#endif // USE_RIVET
