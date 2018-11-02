#include "Core.Application.Application.h"


#include "Core.Application.GlobalAccess.h"

#include "Core.Base.FileSystem.h"
#include "Core.Base.Thread.ThreadProcessor.h"
#include "Core.Screen.ScreenNoProject.h"
#include "Core.Screen.Screen.h"
#include "Core.Project.Project.h"


namespace nCore {
namespace nApplication {


static  cApplication*  sgInstance = 0;


cApplication*
cApplication::App()
{
    return  sgInstance;
}

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cApplication::cApplication() :
    mMainWindow( 0 ),
    mProject( 0 ),
    mScreenNameToLoad( "" ),
    mLoadScreenASAP( false )
{
    sgInstance = this;
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Getter/Setter
// -------------------------------------------------------------------------------------


sf::RenderWindow*
cApplication::Window()
{
    return  mMainWindow;
}


void
cApplication::SetAppTitle( const  std::string&  iTitle )
{
    mMainWindow->setTitle( iTitle );
}


void
cApplication::SetAppDefaultResolution( int iW, int iH )
{
    mMainWindow->setSize( sf::Vector2u( iW, iH ) );
}


::nCore::nProject::cProject*
cApplication::Project()
{
    return  mProject;
}


void
cApplication::NewProject( const  std::string&  iProjectFile )
{
    if( mProject )
    {
        mProject->Finalize();
        delete  mProject;
    }

    nStdFileSystem::path projectPath = iProjectFile;

    mProject = new ::nCore::nProject::cProject( projectPath.stem().string(), projectPath.parent_path().string() );
    mProject->Initialize();

    if( mMainWindow )
    {
        mMainWindow->setFramerateLimit( mProject->LimitFramerate() );
        mMainWindow->setSize( sf::Vector2u( mProject->ResolutionWidth(), mProject->ResolutionHeight() ) );

        auto view = mMainWindow->getDefaultView();
        view.reset( sf::FloatRect( 0.0F, 0.0F, float(mProject->ResolutionWidth()), float(mProject->ResolutionHeight()) ) );
        mMainWindow->setView( view );
    }
}


bool
cApplication::LoadProject( const  nStdFileSystem::path&  iProjectFile )
{
    if( mProject )
    {
        mProject->Finalize();
        delete  mProject;
    }

    if( !nStdFileSystem::exists( iProjectFile ) )
    {
        printf( "The project file doesn't exist\n" );
        printf( "TODO : Load splash default screen here\n" );
        return  false;
    }

    mProject = new ::nCore::nProject::cProject( iProjectFile );
    mProject->Initialize();
    mProject->LoadXML();

    if( mMainWindow )
    {
        mMainWindow->setFramerateLimit( mProject->LimitFramerate() );
        mMainWindow->setSize( sf::Vector2u( mProject->ResolutionWidth(), mProject->ResolutionHeight() ) );

        auto view = mMainWindow->getDefaultView();
        view.reset( sf::FloatRect( 0.0F, 0.0F, float(mProject->ResolutionWidth()), float(mProject->ResolutionHeight()) ) );
        mMainWindow->setView( view );
        mMainWindow->setTitle( mProject->Name() );
    }

    return  true;
}


void
cApplication::SetDefaultNoProjectScreen()
{
    mProject = new ::nCore::nProject::cProject( "none", "none" );
    mProject->Initialize();
    mProject->AddScreen( new ::nScreen::cScreenNoProject() );
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cApplication::Initialize()
{
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    mMainWindow = new  sf::RenderWindow( sf::VideoMode( 1024, 768 ), "NoProject", sf::Style::Default, settings );
    ::nCore::nApplication::cGlobalAccess::Instance()->TheMainWindow( mMainWindow );
    ::nCore::nBase::nThread::cThreadProcessor::Instance();
}


void
cApplication::Finalize()
{
    delete  mMainWindow;
    ::nCore::nApplication::cGlobalAccess::Instance()->TheMainWindow( 0 );

    ::nCore::nBase::nThread::cThreadProcessor* threadProc = ::nCore::nBase::nThread::cThreadProcessor::Instance();
    threadProc->Finalize();
    delete threadProc;
}


void
cApplication::BuildProject()
{
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cApplication::Update( unsigned int iDeltaTime )
{
    mProject->CurrentScreen()->Update( iDeltaTime );

    if( mLoadScreenASAP )
    {
        mProject->SetCurrentScreen( mScreenNameToLoad );
        mLoadScreenASAP = false;
    }
}


void
cApplication::Draw( sf::RenderTarget* iRenderTarget )
{
    mProject->CurrentScreen()->Draw( iRenderTarget );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Screen
// -------------------------------------------------------------------------------------


void
cApplication::ChangeScreenASAP( const  std::string&  iScreenName )
{
    mScreenNameToLoad = iScreenName;
    mLoadScreenASAP = true;
}


void
cApplication::PushScreen( ::nScreen::cScreen*  iScreen )
{
    mProject->AddScreen( iScreen );
}


void
cApplication::RemoveScreen( const  std::string&  iScreenName )
{
    mProject->RemoveScreen( iScreenName );
}


::nScreen::cScreen*
cApplication::CurrentScreen()
{
    return  mProject->CurrentScreen();
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cApplication::HandleEvents( sf::Event&  iEvent )
{
    switch( iEvent.type )
    {
        case sf::Event::Closed:
            mMainWindow->close();
            break;
        case sf::Event::Resized:
            Resized( iEvent );
            break;
        case sf::Event::LostFocus:
            LostFocus( iEvent );
            break;
        case sf::Event::GainedFocus:
            GainedFocus( iEvent );
            break;
        case sf::Event::TextEntered:
            TextEntered( iEvent );
            break;
        case sf::Event::KeyPressed:
            KeyPressed( iEvent );
            break;
        case sf::Event::KeyReleased:
            KeyReleased( iEvent );
            break;
        case sf::Event::MouseWheelMoved:
            MouseWheelMoved( iEvent );
            break;
        case sf::Event::MouseWheelScrolled:
            MouseWheelScrolled( iEvent );
            break;
        case sf::Event::MouseButtonPressed:
            MouseButtonPressed( iEvent );
            break;
        case sf::Event::MouseButtonReleased:
            MouseButtonReleased( iEvent );
            break;
        case sf::Event::MouseMoved:
            MouseMoved( iEvent );
            break;
        case sf::Event::MouseEntered:
            MouseEntered( iEvent );
            break;
        case sf::Event::MouseLeft:
            MouseLeft( iEvent );
            break;
        case sf::Event::JoystickButtonPressed:
            JoystickButtonPressed( iEvent );
            break;
        case sf::Event::JoystickButtonReleased:
            JoystickButtonReleased( iEvent );
            break;
        case sf::Event::JoystickMoved:
            JoystickMoved( iEvent );
            break;
        case sf::Event::JoystickConnected:
            JoystickConnected( iEvent );
            break;
        case sf::Event::JoystickDisconnected:
            JoystickDisconnected( iEvent );
            break;
        case sf::Event::TouchBegan:
            TouchBegan( iEvent );
            break;
        case sf::Event::TouchMoved:
            TouchMoved( iEvent );
            break;
        case sf::Event::TouchEnded:
            TouchEnded( iEvent );
            break;
        case sf::Event::SensorChanged:
            SensorChanged( iEvent );
            break;
        default:
            break;
    }
}


void
cApplication::Closed( const sf::Event& iEvent )
{
}


void
cApplication::Resized( const sf::Event& iEvent )
{
}


void
cApplication::LostFocus( const sf::Event& iEvent )
{
}


void
cApplication::GainedFocus( const sf::Event& iEvent )
{
}


void
cApplication::TextEntered( const sf::Event& iEvent )
{
    mProject->CurrentScreen()->TextEntered( iEvent );
}


void
cApplication::KeyPressed( const sf::Event& iEvent )
{
    mProject->CurrentScreen()->KeyPressed( iEvent );
}


void
cApplication::KeyReleased( const sf::Event& iEvent )
{
    mProject->CurrentScreen()->KeyReleased( iEvent );
}


void
cApplication::MouseWheelMoved( const sf::Event& iEvent )
{
    mProject->CurrentScreen()->MouseWheelMoved( iEvent );
}


void
cApplication::MouseWheelScrolled( const sf::Event& iEvent )
{
    mProject->CurrentScreen()->MouseWheelScrolled( iEvent );
}


void
cApplication::MouseButtonPressed( const sf::Event& iEvent )
{
    mProject->CurrentScreen()->MouseButtonPressed( iEvent );
}


void
cApplication::MouseButtonReleased( const sf::Event& iEvent )
{
    mProject->CurrentScreen()->MouseButtonReleased( iEvent );
}


void
cApplication::MouseMoved( const sf::Event& iEvent )
{
    mProject->CurrentScreen()->MouseMoved( iEvent );
}


void
cApplication::MouseEntered( const sf::Event& iEvent )
{
    mProject->CurrentScreen()->MouseEntered( iEvent );
}


void
cApplication::MouseLeft( const sf::Event& iEvent )
{
    mProject->CurrentScreen()->MouseLeft( iEvent );
}


void
cApplication::JoystickButtonPressed( const sf::Event& iEvent )
{
    mProject->CurrentScreen()->JoystickButtonPressed( iEvent );
}


void
cApplication::JoystickButtonReleased( const sf::Event& iEvent )
{
    mProject->CurrentScreen()->JoystickButtonReleased( iEvent );
}


void
cApplication::JoystickMoved( const sf::Event& iEvent )
{
    mProject->CurrentScreen()->JoystickMoved( iEvent );
}


void
cApplication::JoystickConnected( const sf::Event& iEvent )
{
    mProject->CurrentScreen()->JoystickConnected( iEvent );
}


void
cApplication::JoystickDisconnected( const sf::Event& iEvent )
{
    mProject->CurrentScreen()->JoystickDisconnected( iEvent );
}


void
cApplication::TouchBegan( const sf::Event& iEvent )
{
    mProject->CurrentScreen()->TouchBegan( iEvent );
}


void
cApplication::TouchMoved( const sf::Event& iEvent )
{
    mProject->CurrentScreen()->TouchMoved( iEvent );
}


void
cApplication::TouchEnded( const sf::Event& iEvent )
{
    mProject->CurrentScreen()->TouchEnded( iEvent );
}


void
cApplication::SensorChanged( const sf::Event& iEvent )
{
    mProject->CurrentScreen()->SensorChanged( iEvent );
}


} // nApplication
} // nCore

