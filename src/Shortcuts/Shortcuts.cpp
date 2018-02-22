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
    mShortcuts.insert( std::make_pair( "moveup", sf::Keyboard::Key::Up ) );
    mShortcuts.insert( std::make_pair( "movedown", sf::Keyboard::Key::Down ) );
    mShortcuts.insert( std::make_pair( "moveleft", sf::Keyboard::Key::Left ) );
    mShortcuts.insert( std::make_pair( "moveright", sf::Keyboard::Key::Right ) );
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
