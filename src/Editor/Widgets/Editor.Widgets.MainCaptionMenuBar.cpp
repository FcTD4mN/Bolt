#include "Editor.Widgets.MainCaptionMenuBar.h"


#include <QAction>
#include <QMenu>


namespace nEditor {
namespace nWidgets {


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


cMainCaptionMenuBar::~cMainCaptionMenuBar()
{
    tSelf::Destroy();
}


cMainCaptionMenuBar::cMainCaptionMenuBar( QWidget*  parent ) :
    tSuperClass( parent )
{
    tSelf::Init();
    tSelf::Build();
    tSelf::Compose();
}


//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------ GUI utilities


void
cMainCaptionMenuBar::Init()
{
    //& means we can use keyboard typing to access member in menubar
    // this is very convenient.

    mMenuFile = new QMenu( "&File" );
        mActionNew = new QAction( "&New" );
        mActionOpen = new QAction( "&Open" );
        mActionSave = new QAction( "&Save" );
        mActionSaveAs = new QAction( "&SaveAs" );
        mActionExit = new QAction( "&Exit" );
    mMenuEdit = new QMenu( "&Edit" );
    mMenuView = new QMenu( "&View" );
    mMenuAbout = new QMenu( "&About" );

    mActionNew->setShortcut( QKeySequence::New );
    mActionOpen->setShortcut( QKeySequence::Open );
    mActionSave->setShortcut( QKeySequence::Save );
    mActionSaveAs->setShortcut( QKeySequence::SaveAs );
    mActionExit->setShortcut( QKeySequence::Quit );
}


void
cMainCaptionMenuBar::Build()
{
    tSelf::addMenu( mMenuFile );
        mMenuFile->addAction( mActionNew );
        mMenuFile->addAction( mActionOpen );
        mMenuFile->addAction( mActionSave );
        mMenuFile->addAction( mActionSaveAs );
        mMenuFile->addAction( mActionExit );
    tSelf::addMenu( mMenuEdit );
    tSelf::addMenu( mMenuView );
    tSelf::addMenu( mMenuAbout );

}


void
cMainCaptionMenuBar::Compose()
{
}


void
cMainCaptionMenuBar::Destroy()
{
        delete mActionNew;
        delete mActionOpen;
        delete mActionSave;
        delete mActionSaveAs;
        delete mActionExit;
    delete  mMenuFile;
    delete  mMenuEdit;
    delete  mMenuView;
    delete  mMenuAbout;
}


} // nWidgets
} // nEditor

