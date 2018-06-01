#include "Core.Project.Project.h"

#include "Core.Screen.Screen.h"

namespace nProject {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


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
}


void
cProject::Finalize()
{
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
cProject::SaveXML( tinyxml2::XMLElement * iNode, tinyxml2::XMLDocument * iDocument )
{
}


void
cProject::LoadXML()
{
    tinyxml2::XMLDocument doc;
    std::string path = mProjectFolder + "/projectConfig.ini";
    tinyxml2::XMLError error = doc.LoadFile( path.c_str() );
    if( !error )
        printf( "Cool\n" );
    else
        printf( "Error\n" );

    tinyxml2::XMLElement* root = doc.FirstChildElement( "config" );

    tinyxml2::XMLElement* resolution = root->FirstChildElement( "resolution" );
    mResolutionWidth = resolution->IntAttribute( "width" );
    mResolutionHeight = resolution->IntAttribute( "height" );

    tinyxml2::XMLElement* limitFR = root->FirstChildElement( "limitframerate" );
    mLimitFramerate = limitFR->IntAttribute( "value" );
}


} //nApplication

