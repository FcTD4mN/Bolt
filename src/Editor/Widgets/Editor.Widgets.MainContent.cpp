#include "Editor.Widgets.MainContent.h"

#ifdef USE_RIVET

#include "Editor.Widgets.Editors.ProjectEditor.h"
#include "Editor.Widgets.MainTools.h"


#include <RivetDockingCallbackLibrary>


#include <QSplitter>


namespace nEditor {
namespace nWidgets {


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cMainContent::~cMainContent()
{
    Destroy();
}


cMainContent::cMainContent( QWidget*  parent ) :
    tSuperClass( parent ),
    mControlBar( NULL ),
    mNavBar( NULL ),
    mScreensTabArea( NULL ),
    mProjectTreeEditor( NULL ),
    mSplitterHorizontal( NULL ),
    mSplitterVertical( NULL ),
    mTools( NULL )
{
    Init();
    Build();
    Compose();
}

//--------------------------------------------------------------------------------------
//------------------------------------------------------------------ Accessible Children


cMainContent::cAccessibleChildren
cMainContent::AccessibleChildren()  const
{
    return  cAccessibleChildren{ mControlBar, mNavBar, mScreensTabArea, mProjectTreeEditor };
}


//--------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------- Event


void
cMainContent::resizeEvent( QResizeEvent* event )
{
    tSuperClass::resizeEvent( event );
    Compose();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------ GUI utilities


void
cMainContent::Init()
{
    mControlBar = new QWidget( this );
    mNavBar = new QWidget( this );

    mScreensTabArea = new ::Rivet::TabArea( mNavBar );

    mProjectTreeEditor = new cProjectEditor( NULL );

    mSplitterHorizontal = new QSplitter( this );
    mSplitterVertical = new QSplitter( Qt::Vertical, NULL);

    mPlaceholderA = new QWidget( NULL );

    mTools = new cMainTools( NULL );
}


void
cMainContent::Build()
{
    mControlBar->setObjectName( "ControlBar" );
    mNavBar->setObjectName( "NavBar" );
    mScreensTabArea->setObjectName( "TabBar" );
    mProjectTreeEditor ->setObjectName( "ProjectTreeEditor" );

    //TMP:DEBUG
    //move to qss
    mControlBar->setStyleSheet( "background: rgb( 40, 40, 40 ); border: 1px solid rgb( 20, 20, 20 );" );
    mNavBar->setStyleSheet( "background: rgb( 40, 40, 40 ); border: 1px solid rgb( 20, 20, 20 );" );
    //
    mPlaceholderA->setStyleSheet( "background: rgb( 200, 200, 200); border: 1px solid rgb( 80, 80, 80 );" );

    mScreensTabArea->SetOverlap( 20 );
    mScreensTabArea->SetTabsClosable( false );
    mScreensTabArea->SetOnTabDroppedOutCB( ::Rivet::OnTabDroppedOutCB_RevertBack );
    mScreensTabArea->SetTag( "screens" );

    for( int i = 0; i < 3; ++i )
    {
        auto t = new ::Rivet::Tab();
        t->SetColor( QColor( 60, 60, 60 ) );
        t->SetFadeColor( QColor( 30, 30, 30 ) );
        mScreensTabArea->ManualAddNewTab( t );
    }

    mTools->setMinimumHeight( 30 );
    mProjectTreeEditor->setMinimumWidth( 200 );

    QList< int > sh = { 200, 800 };
    mSplitterHorizontal->setHandleWidth( 8 );
    mSplitterVertical->setHandleWidth( 8 );
    mSplitterHorizontal->addWidget( mProjectTreeEditor );
    mSplitterHorizontal->addWidget( mSplitterVertical );

    mSplitterVertical->addWidget( mPlaceholderA );
    mSplitterVertical->addWidget( mTools );
    mSplitterVertical->setMinimumWidth( 400 );
    mSplitterVertical->setCollapsible(0,false);
    mSplitterVertical->setCollapsible(1,false);

    mSplitterHorizontal->setSizes( sh );
    mSplitterHorizontal->setCollapsible(0,false);
    mSplitterHorizontal->setCollapsible(1,false);
}


void
cMainContent::Compose()
{
    mControlBar->setGeometry( 0, 0, width(), 30 );
    mNavBar->setGeometry( 0, 30, width(), 30 );

    mScreensTabArea->resize( mNavBar->size() );

    mSplitterHorizontal->setGeometry( 0, 60, width(), height() - 60 );
}


void
cMainContent::Destroy()
{
    delete  mControlBar;
    delete  mScreensTabArea;
    delete  mNavBar;
    delete  mProjectTreeEditor;
    delete  mSplitterHorizontal;
    delete  mSplitterVertical;
    delete  mTools;
}


} // nWidgets
} // nEditor

#endif // USE_RIVET
