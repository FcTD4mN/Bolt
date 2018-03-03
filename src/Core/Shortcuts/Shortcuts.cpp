 #include "Shortcuts.h"


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cShortcuts::~cShortcuts()
{
}


cShortcuts::cShortcuts()
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cShortcuts::Initialize()
{
    mShortcuts.insert( std::make_pair( sf::Keyboard::Key::Up, "moveup" ) );
    mShortcuts.insert( std::make_pair( sf::Keyboard::Key::Down, "movedown" ) );
    mShortcuts.insert( std::make_pair( sf::Keyboard::Key::Left, "moveleft" ) );
    mShortcuts.insert( std::make_pair( sf::Keyboard::Key::Right, "moveright" ) );
    mShortcuts.insert( std::make_pair( sf::Keyboard::Key::Space, "attack" ) );
}


void
cShortcuts::Finalize()
{
}


// -------------------------------------------------------------------------------------
// --------------------------------------------------------------------- Shortcut access
// -------------------------------------------------------------------------------------


sf::Keyboard::Key
cShortcuts::GetKeyForAction( const std::string & iAction )
{
    for( std::unordered_map< sf::Keyboard::Key, std::string >::const_iterator it = mShortcuts.begin(); it != mShortcuts.end(); ++it )
    {
        if( it->second == iAction )
            return it->first;
    }

    return  sf::Keyboard::Key::Unknown;
}


const std::string&
cShortcuts::GetActionForKey( sf::Keyboard::Key iKey )
{
    return  mShortcuts[ iKey ];
}
