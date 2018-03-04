 #include "Shortcuts.h"

#include <fstream>
#include <sstream>

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
    LoadXML();
}


void
cShortcuts::Finalize()
{
    SaveXML();
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


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Input/Output
// -------------------------------------------------------------------------------------


void
cShortcuts::SaveXML()
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* elm = doc.NewElement( "shortcuts" );

    for( auto v : mShortcuts )
    {
        tinyxml2::XMLElement* entry = doc.NewElement( "entry" );

        entry->SetAttribute( "key", v.first );
        entry->SetAttribute( "action", v.second.c_str() );

         elm->LinkEndChild( entry );
    }

    doc.InsertFirstChild( elm );

    tinyxml2::XMLError error = doc.SaveFile( "shortcuts.xml" );
}


void
cShortcuts::LoadXML()
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.LoadFile( "shortcuts.xml" );

    for( tinyxml2::XMLElement* entry = doc.FirstChildElement( "shortcuts" )->FirstChildElement( "entry"); entry; entry = entry->NextSiblingElement() )
    {
        mShortcuts[ sf::Keyboard::Key( entry->Int64Attribute( "key" ) ) ] = entry->Attribute( "action" );
    }
}
