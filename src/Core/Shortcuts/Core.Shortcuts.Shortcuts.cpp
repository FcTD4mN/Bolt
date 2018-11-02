 #include "Core.Shortcuts.Shortcuts.h"


#include "Core.Application.GlobalAccess.h"


#include "Core.Base.FileSystem.h"


namespace nCore {
namespace nShortcuts {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cShortcuts::~cShortcuts()
{
}


cShortcuts::cShortcuts()
{
}


cShortcuts*
cShortcuts::Instance()
{
    static cShortcuts* gShortcuts = 0;
    if( !gShortcuts )
        gShortcuts = new cShortcuts();

    return  gShortcuts;
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
	std::string filePath = ::nCore::nApplication::cGlobalAccess::Instance()->ProjectFolder() + "/shortcuts.xml";

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

    tinyxml2::XMLError error = doc.SaveFile( filePath.c_str() );
}


void
cShortcuts::LoadXML()
{
	std::string filePath = ::nCore::nApplication::cGlobalAccess::Instance()->ProjectFolder() + "/shortcuts.xml";

    if( nStdFileSystem::exists( filePath ) )
    {
        tinyxml2::XMLDocument doc;
        tinyxml2::XMLError error = doc.LoadFile( filePath.c_str() );

        for( tinyxml2::XMLElement* entry = doc.FirstChildElement( "shortcuts" )->FirstChildElement( "entry"); entry; entry = entry->NextSiblingElement() )
        {
            mShortcuts[ sf::Keyboard::Key( entry->Int64Attribute( "key" ) ) ] = entry->Attribute( "action" );
        }
    }
}


} // namespace nShortcuts
} // namespace nCore

