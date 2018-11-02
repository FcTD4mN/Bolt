#pragma once

#include <QKeySequence>
#include <QMap>
#include <QShortcut>


// Gets the shortcut related to action name
// OR
// Registers a shortcut that you have to create in the app, because it needs a valid parent widget to exist (qasserted)
// So basically, you don't bother whatsoever about how/when/why creating a shortcut, just get it through this, and connect your stuff
#define  SHORTCUT( iName ) ::nEditor::nShortcuts::cShortcutManager::Instance()->RegisterShortcut( iName, this )

// Quick access to keysequences( the key sequance of an action)
#define  KEYSEQUENCE( iName )  ::nEditor::nShortcuts::cShortcutManager::Instance()->KeyByActionName( iName )


namespace  nEditor::nShortcuts {


class  cShortcutManager
{
private:
    ~cShortcutManager();
    cShortcutManager();

public:
    static  cShortcutManager*  Instance();

public:
    // Building
    void  Initialize();
    void  Finalize();

public:
    // Shortcut management
    QKeySequence    KeyByActionName( const QString& iActionName )  const;
    QString         ActionNameByKey( const QKeySequence& iKey )  const;
    void            ChangeKeyForAction( const QString& iActionName, const QKeySequence& iNewKey );

    QShortcut*      ShortcutByActionName( const QString& iActionName )  const;
    QShortcut*      RegisterShortcut( const QString& iActionName, QWidget* iParent );

private:
    // __PRIVATE__
    void            _RegisterKeySequence( const QString& iActionName, const QKeySequence& iActionKey );

private:
    // We need to separate theses, because Shortcuts come in as they are created by widgets, so they might not be all there/created when user opens shortcut editor
    // KeySequence map holds every single shortcut key sequence there is, so user can see em all and edit them all at any time
    QMap< QString, QShortcut* >     mShortcutMap;
    QMap< QString, QKeySequence >   mKeySequenceMap;
};


} // namespace  nEditor::nShortcuts






