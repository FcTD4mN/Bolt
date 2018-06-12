#include "Core.Project.Project.h"


#include "Core.ECS.Utilities.ComponentRegistry.h"
#include "Core.ECS.Utilities.EntityParser.h"
#include "Core.ECS.Utilities.SystemRegistry.h"
#include "Core.Application.GlobalAccess.h"

#include "Core.Screen.Screen.h"



namespace nProject {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cProject::~cProject()
{
    for( auto screen : mScreenStack )
        delete  screen;
}



cProject::cProject( const std::string& iProjectName, const std::string& iProjectFolder ) :
    mProjectName( iProjectName ),
    mProjectFolder( iProjectFolder ),
    mResolutionWidth( 1024 ),
    mResolutionHeight( 768 ),
    mLimitFramerate ( 144 )
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cProject::Initialize()
{
    ::nECS::cComponentRegistry::Instance()->Initialize( mProjectFolder );
    ::nECS::cEntityParser::Instance()->Initialize( mProjectFolder );
    ::nECS::cSystemRegistry::Instance()->Initialize( mProjectFolder );
    ::nGlobal::cGlobalProperties::Instance()->SetProjectFolder( mProjectFolder );
    ::nGlobal::cGlobalProperties::Instance()->SetProjectSize( sf::Vector2f( float( mResolutionWidth ), float( mResolutionHeight ) ) );
}


void
cProject::Finalize()
{
    for( auto screen : mScreenStack )
        screen->Finalize();

    ::nECS::cComponentRegistry::Instance()->Finalize();
    ::nECS::cEntityParser::Instance()->Finalize();
    ::nECS::cSystemRegistry::Instance()->Finalize();
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Screen
// -------------------------------------------------------------------------------------


void
cProject::PushScreen( ::nScreen::cScreen * iScreen )
{
    mScreenStack.push_back( iScreen );
    iScreen->Initialize();
}


void
cProject::PopScreen()
{
    ::nScreen::cScreen* currentScreen = mScreenStack.back();
    currentScreen->Finalize();
    mScreenStack.pop_back();
}


::nScreen::cScreen*
cProject::CurrentScreen()
{
    return  mScreenStack.back();
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
cProject::SaveXML()
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* projectNode = doc.NewElement( "project" );
    projectNode->SetAttribute( "name", mProjectName.c_str() );

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

    for( auto screen : mScreenStack )
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
    std::string outputFileName = mProjectFolder + "/" + mProjectName + ".proj";
    tinyxml2::XMLError error = doc.SaveFile( outputFileName.c_str() );
    if( error )
    {
        printf("Heh, couldn't save ...\n" );
    }
}


void
cProject::LoadXML( const std::string& iProjectFile ) //CHECK : No param here ?
{
    for( auto screen : mScreenStack )
        delete  screen;

    mScreenStack.clear();

    tinyxml2::XMLDocument doc;
    std::string path = mProjectFolder + "/" + iProjectFile; //CHECK: use mProjectName ?
    tinyxml2::XMLError error = doc.LoadFile( path.c_str() );
    if( !error )
        printf( "Cool\n" );
    else
        printf( "Error\n" );

    // PROJECT ITSELF
    tinyxml2::XMLElement* root = doc.FirstChildElement( "project" );
    mProjectName = root->Attribute( "name" );

    // CONFIG
    tinyxml2::XMLElement* config = root->FirstChildElement( "config" );

    tinyxml2::XMLElement* resolution = config->FirstChildElement( "resolution" );
    mResolutionWidth = resolution->IntAttribute( "width" );
    mResolutionHeight = resolution->IntAttribute( "height" );

    ::nGlobal::cGlobalProperties::Instance()->SetProjectSize( sf::Vector2f( float( mResolutionWidth ), float( mResolutionHeight ) ) );

    tinyxml2::XMLElement* limitFR = config->FirstChildElement( "limitframerate" );
    mLimitFramerate = limitFR->IntAttribute( "value" );

    // SCREENS
    tinyxml2::XMLElement* screens = root->FirstChildElement( "screens" );
    for( tinyxml2::XMLElement* screenNode = screens->FirstChildElement( "screen" ); screenNode; screenNode = screenNode->NextSiblingElement() )
    {
        nScreen::cScreen* screen = new  ::nScreen::cScreen( screenNode->Attribute( "name" ) );
        if( screen )
        {
            std::string screenFilePath = mProjectFolder + "/Screens/" + screenNode->Attribute( "file" );
            screen->LoadXML( screenFilePath );
            PushScreen( screen );
        }
    }
}


} //nApplication

