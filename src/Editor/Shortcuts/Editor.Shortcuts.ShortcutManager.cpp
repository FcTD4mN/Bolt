#include "Editor.Shortcuts.ShortcutManager.h"


namespace  nEditor::nShortcuts {


cShortcutManager::~cShortcutManager()
{
    Finalize();
}


cShortcutManager::cShortcutManager()
{
    Initialize();
}


// -------------------------------------------------------------------------------------
// --------------------------------------------------------------------------- Singleton
// -------------------------------------------------------------------------------------


cShortcutManager*
cShortcutManager::Instance()
{
    static  cShortcutManager* sgShortcutManager = 0;
    if( !sgShortcutManager )
        sgShortcutManager = new cShortcutManager();

    return  sgShortcutManager;
}


// -------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------- Building
// -------------------------------------------------------------------------------------


void
cShortcutManager::Initialize()
{
    // PROJECT
    _RegisterKeySequence( "ProjectNew", QKeySequence::New );
    _RegisterKeySequence( "ProjectOpen", QKeySequence::Open );
    _RegisterKeySequence( "ProjectSave", QKeySequence::Save );
    _RegisterKeySequence( "ProjectSaveAs", QKeySequence::SaveAs );

    // VIEW
    _RegisterKeySequence( "GridToggle", QKeySequence( Qt::Key_G ) );
    _RegisterKeySequence( "GridSnapToggle", QKeySequence( Qt::CTRL + Qt::Key_G ) );

    // ANIMATION
    _RegisterKeySequence( "AnimationNextFrame", QKeySequence( Qt::Key_Right ) );
    _RegisterKeySequence( "AnimationPreviousFrame", QKeySequence( Qt::Key_Left ) );
    _RegisterKeySequence( "AnimationPlay", QKeySequence( Qt::Key_Space ) );
    _RegisterKeySequence( "AnimationImageCopy", QKeySequence::Copy );
    _RegisterKeySequence( "AnimationImagePaste", QKeySequence::Paste );
}


void
cShortcutManager::Finalize()
{
    for( auto shortcut : mShortcutMap )
        delete  shortcut;

    mShortcutMap.clear();
    mKeySequenceMap.clear();
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------- Shortcut management
// -------------------------------------------------------------------------------------


QKeySequence
cShortcutManager::KeyByActionName( const QString& iActionName ) const
{
    return  mKeySequenceMap[ iActionName ];
}


QString
cShortcutManager::ActionNameByKey( const QKeySequence & iKey ) const
{
    for( auto it = mKeySequenceMap.begin(); it != mKeySequenceMap.end(); ++it )
        if( it.value() == iKey )
            return  it.key();

    return  "_None_";
}


void
cShortcutManager::ChangeKeyForAction( const QString & iActionName, const QKeySequence & iNewKey )
{
    mKeySequenceMap[ iActionName ] = iNewKey;
    mShortcutMap[ iActionName ]->setKey( iNewKey );
}


QShortcut*
cShortcutManager::ShortcutByActionName( const QString & iActionName ) const
{
    return  mShortcutMap[ iActionName ];
}


QShortcut*
cShortcutManager::RegisterShortcut( const QString & iActionName, QWidget * iParent )
{
    auto existingSC = mShortcutMap[ iActionName ];
    if( existingSC )
        return  existingSC;

    auto newShortcut = new  QShortcut( KEYSEQUENCE( iActionName ), iParent );
    mShortcutMap.insert( iActionName, newShortcut );
    return  newShortcut;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- __PRIVATE__
// -------------------------------------------------------------------------------------


void
cShortcutManager::_RegisterKeySequence( const QString & iActionName, const QKeySequence & iActionKey )
{
    mKeySequenceMap.insert( iActionName, iActionKey );
}



} // namespace  nEditor::nShortcuts

