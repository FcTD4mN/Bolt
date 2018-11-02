#include "Core.Project.Project.h"


#include "Core.Application.GlobalAccess.h"
#include "Core.Base.Utilities.h"
#include "Core.Registries.ComponentRegistry.h"
#include "Core.Registries.EntityRegistry.h"
#include "Core.Registries.SystemRegistry.h"
#include "Core.Screen.Screen.h"
#include "Core.Shortcuts.Shortcuts.h"


namespace nCore {
namespace nProject {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cProject::~cProject()
{
    for( auto screen : mScreens )
        delete  screen;
}



cProject::cProject( const std::string& iProjectName, const std::string& iProjectFolder ) :
    mProjectName( iProjectName ),
    mProjectFilePath( "" ),
    mCurrentScreenIndex( 0 ),
    mResolutionWidth( 1024 ),
    mResolutionHeight( 768 ),
    mLimitFramerate ( 144 )
{
    if( iProjectName != "" && iProjectName != "_UnnamedProject" ) // Maybe go triple variable : mProjectName  /  mProjectDirectory  /  mProjectFileName, to allow maximum freedom in file/projectnamning OR just always use the projectfile as projectName
        mProjectFilePath = iProjectFolder + "/" + iProjectName + ".proj";
    else
        mProjectFilePath = iProjectFolder + "/"; // Meaning the directory path without the stem, which is going to be check further away
}



cProject::cProject( const nStdFileSystem::path &iProjectFilePath ) :
    mProjectName( iProjectFilePath.stem().string() ),
    mProjectFilePath( iProjectFilePath ),
    mCurrentScreenIndex( 0 ),
    mResolutionWidth( 1024 ),
    mResolutionHeight( 768 ),
    mLimitFramerate( 144 )
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cProject::Initialize()
{
    // ============= Global Props =============
    ::nCore::nApplication::cGlobalAccess::Instance()->ProjectFolder( ProjectDirectory().string() );
    ::nCore::nApplication::cGlobalAccess::Instance()->ProjectSize( sf::Vector2f( float( mResolutionWidth ), float( mResolutionHeight ) ) );

    // ============= ECS Registries =============
    ::nCore::nRegistries::cComponentRegistry::Instance()->Initialize();
    ::nCore::nRegistries::cEntityRegistry::Instance()->Initialize();
    ::nCore::nRegistries::cSystemRegistry::Instance()->Initialize();

    // ============= SHORTCUTS =============
    ::nCore::nShortcuts::cShortcuts::Instance()->Initialize();
}


void
cProject::Finalize()
{
    for( auto screen : mScreens )
        screen->Finalize();

    ::nCore::nRegistries::cComponentRegistry::Instance()->Finalize();
    ::nCore::nRegistries::cEntityRegistry::Instance()->Finalize();
    ::nCore::nRegistries::cSystemRegistry::Instance()->Finalize();
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Screen
// -------------------------------------------------------------------------------------


void
cProject::AddScreen( ::nScreen::cScreen * iScreen )
{
    // First remove the screen if already in, and add the new one.
    // Doing this allows for screen replacement
    RemoveScreen( iScreen->Name() );
    mScreens.push_back( iScreen );
}


void
cProject::SetCurrentScreen( const std::string & iScreenName )
{
    // Don't unload a screen in the editor, as it needs them to be loaded for project Tree
    // To remove this : we need a way to access all the content of everything without loading it
    // PLUS : if i select an entity from another screen, that is not currently edited, if i edit it, it needs to exist -> be loaded
#ifndef EDITOR
    auto currentScreen = CurrentScreen();
    if( currentScreen )
        currentScreen->Unload();
#endif // !EDITOR

    for( int i = 0; i < mScreens.size(); ++i )
    {
        auto screen = mScreens[ i ];
        if( screen->Name() == iScreenName )
        {
            mCurrentScreenIndex = i;

            // I'm not liking that, but editor already has everything loaded and initialized, plus it
            // won't like any code generated thing as it's a core thing. Do we want maint.py to be executed in the editor ? ATM python crashes.
#ifndef EDITOR
            if( !screen->Initialized() )
                screen->Initialize();

            if( !screen->Loaded() )
                screen->LoadXML();

            if( !screen->AdditionalBuildCompleted() )
                screen->AdditionnalBuildScreen();
#endif // !EDITOR

        }
    }
}


void
cProject::LoadScreen( const std::string & iScreenName )
{
    auto screen = GetScreenByName( iScreenName );
    if( screen )
        screen->LoadXML();
}


void
cProject::RemoveScreen( const std::string& iScreenName )
{
    auto screen = GetScreenByName( iScreenName );
    if( screen )
    {
        screen->Finalize();
        ::nCore::nBase::EraseElementFromVector( &mScreens, screen );
    }
}


::nScreen::cScreen*
cProject::CurrentScreen()
{
    if( mScreens.size() == 0 )
        return  0;

    return  mScreens[ mCurrentScreenIndex ];
}


::nScreen::cScreen*
cProject::GetScreenByName( const std::string & iScreenName )
{
    for( int i = 0 ; i < mScreens.size(); ++i )
    {
        auto screen = mScreens[ i ];
        if( screen->Name() == iScreenName )
            return  screen;
    }

    return  0;
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------- Access/Get
// -------------------------------------------------------------------------------------


int
cProject::ResolutionWidth() const
{
    return  mResolutionWidth;
}


int
cProject::ResolutionHeight() const
{
    return  mResolutionHeight;
}


int
cProject::LimitFramerate() const
{
    return  mLimitFramerate;
}


void
cProject::SetResolution( int iWidth, int iHeight )
{
    mResolutionWidth = iWidth;
    mResolutionHeight = iHeight;
}


void
cProject::SetLimitFramerate( int iFramerate )
{
    mLimitFramerate = iFramerate;
}


const std::string&
cProject::Name() const
{
    return  mProjectName;
}


void
cProject::Name( const std::string & iNewName )
{
    mProjectName = iNewName;
}


nStdFileSystem::path
cProject::ProjectDirectory() const
{
    return  mProjectFilePath.parent_path();
}


const nStdFileSystem::path&
cProject::ProjectFilePath() const
{
    return  mProjectFilePath;
}


void
cProject::ProjectFilePath( const nStdFileSystem::path& iNewFileName )
{
    mProjectFilePath = iNewFileName;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ EDITOR
// -------------------------------------------------------------------------------------


int
cProject::ScreenCount()
{
    return  int(mScreens.size());
}


::nScreen::cScreen *
cProject::ScreenAtIndex( int iIndex )
{
    if( iIndex < 0 || iIndex > mScreens.size() )
        return  0;

    auto it = mScreens.begin();
    for( int i = 0; i < iIndex; ++i )
        ++it;

    return  *it;
}


void
cProject::RemoveScreenAtIndex( int iIndex )
{
    if( iIndex < 0 || iIndex > mScreens.size() )
        return;

    auto it = mScreens.begin();
    for( int i = 0; i < iIndex; ++i )
        ++it;

    (*it)->Finalize();
    delete  (*it);
    mScreens.erase( it );
}


int
cProject::CurrentScreenIndex() const
{
    return  mCurrentScreenIndex;
}


void
cProject::MakeProjectDirectories() const
{
    if( nStdFileSystem::exists( ProjectDirectory() ) )
    {
        nStdFileSystem::path newDirToCreate = ProjectDirectory().string() + "/";
        nStdFileSystem::create_directory( ProjectDirectory().string() + "/Assets" );
        nStdFileSystem::create_directory( ProjectDirectory().string() + "/Assets/Entities" );
        nStdFileSystem::create_directory( ProjectDirectory().string() + "/Assets/Components" );
        nStdFileSystem::create_directory( ProjectDirectory().string() + "/Assets/Shaders" );
        nStdFileSystem::create_directory( ProjectDirectory().string() + "/Assets/Systems" );
        nStdFileSystem::create_directory( ProjectDirectory().string() + "/Screens" );
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------

// Useful ?
//void
//cProject::Update( unsigned int iDeltaTime )
//{
//}
//
//
//void
// cProject::Draw( sf::RenderTarget* iRenderTarget )
//{
//}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------------- Access/Get
// -------------------------------------------------------------------------------------


void
cProject::SaveXML() const
{
    if( ProjectFilePath().extension() != ".proj" )
    {
        printf( "The project has no associated .proj file\n" );
        return;
    }

    if( !nStdFileSystem::exists( ProjectDirectory() ) )
        MakeProjectDirectories();

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* projectNode = doc.NewElement( "project" );
    projectNode->SetAttribute( "name", mProjectName.c_str() );
    projectNode->SetAttribute( "currentscreen", mCurrentScreenIndex );

    // CONFIG
    tinyxml2::XMLElement* configNode = doc.NewElement( "config" );

    tinyxml2::XMLElement* resolutionNode = doc.NewElement( "resolution" );
    resolutionNode->SetAttribute( "width", mResolutionWidth );
    resolutionNode->SetAttribute( "height", mResolutionHeight );

    tinyxml2::XMLElement* limiteFRNode = doc.NewElement( "limitframerate" );
    limiteFRNode->SetAttribute( "value", mLimitFramerate );

    configNode->LinkEndChild( resolutionNode );
    configNode->LinkEndChild( limiteFRNode );
    projectNode->LinkEndChild( configNode );

    // SCREENS
    tinyxml2::XMLElement* screens = doc.NewElement( "screens" );

    for( auto screen : mScreens )
    {
        tinyxml2::XMLElement* screenNode = doc.NewElement( "screen" );
        screenNode->SetAttribute( "name", screen->Name().c_str() );
        screenNode->SetAttribute( "file", screen->FilePath().filename().string().c_str() );

        screens->LinkEndChild( screenNode );

        screen->SaveXML(); // Hopefully this won't be problematic as we'll open to write another file while still not being done with this one
    }

    projectNode->LinkEndChild( screens );

    // Final connection
    doc.InsertFirstChild( projectNode );

    // Save into file
    tinyxml2::XMLError error = doc.SaveFile( ProjectFilePath().string().c_str() );
    if( error )
        printf("Heh, couldn't save ...\n" );
}


void
cProject::LoadXML()
{
    for( auto screen : mScreens )
        delete  screen;

    mScreens.clear();

    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.LoadFile( mProjectFilePath.string().c_str() );
    if( !error )
        printf( "Cool\n" );
    else
        printf( "Error\n" );

    // PROJECT ITSELF
    tinyxml2::XMLElement* root = doc.FirstChildElement( "project" );
    mProjectName = root->Attribute( "name" );
    mCurrentScreenIndex = root->IntAttribute( "currentscreen" );

    // CONFIG
    tinyxml2::XMLElement* config = root->FirstChildElement( "config" );

    tinyxml2::XMLElement* resolution = config->FirstChildElement( "resolution" );
    mResolutionWidth = resolution->IntAttribute( "width" );
    mResolutionHeight = resolution->IntAttribute( "height" );

    ::nCore::nApplication::cGlobalAccess::Instance()->ProjectSize( sf::Vector2f( float( mResolutionWidth ), float( mResolutionHeight ) ) );

    tinyxml2::XMLElement* limitFR = config->FirstChildElement( "limitframerate" );
    mLimitFramerate = limitFR->IntAttribute( "value" );

    // SCREENS
    tinyxml2::XMLElement* screens = root->FirstChildElement( "screens" );
    for( tinyxml2::XMLElement* screenNode = screens->FirstChildElement( "screen" ); screenNode; screenNode = screenNode->NextSiblingElement() )
    {
        nScreen::cScreen* screen = new  ::nScreen::cScreen( screenNode->Attribute( "name" ) );
        if( screen )
        {
            std::string screenFilePath = ProjectDirectory().string() + "/Screens/" + screenNode->Attribute( "file" );
            screen->FilePath( screenFilePath );
            AddScreen( screen );

            // Editor loads them as soon as they get in the project, to be able to access all entities and stuff for the Project Tree
#ifdef EDITOR
            screen->Initialize();
            screen->LoadXML();
#endif
        }
    }
}


} // nProject
} // nCore

