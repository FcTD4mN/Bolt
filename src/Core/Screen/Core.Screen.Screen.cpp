#include "Core.Screen.Screen.h"


#include "Core.Application.GlobalAccess.h"

#include "Core.Base.Utilities.h"

#include "Core.ECS.Core.World.h"
#include "Core.ECS.Core.System.h"

#include "Core.Mapping.PhysicEntityGrid.h"

#include "Core.Render.LayerEngine.h"



#include "command.h"
#include "Core.Application.GlobalAccess.h"

/*
#ifdef WINDOWS
#include <cpython/Python.h>
#else
#include <Python.h>
#endif //WINDOWS
*/

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------

namespace nScreen {


cScreen::~cScreen()
{
    Finalize();
}


cScreen::cScreen() :
    mName( "Unnamed" ),
    mWorld( 0 ),
    mZoomFactor( 1.0F ),
    mLoaded( false )
{
}


cScreen::cScreen( const std::string & iName ) :
    mName( iName ),
    mWorld( 0 ),
    mZoomFactor( 1.0F ),
    mLoaded( false )
{
}


void
cScreen::Initialize()
{
    if ( !mWorld )
        mWorld = new ::nCore::nECS::nCore::cWorld();

    mInitialized = true;
}


void
cScreen::Finalize()
{
    if( mWorld )
    {
        delete  mWorld;
        mWorld = 0;
    }

    mLoaded = false;
    mInitialized = false;
    mAdditionalBuildComplete = false;
}


void
cScreen::Unload()
{
    Finalize();
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Draw / Update
// -------------------------------------------------------------------------------------


void
cScreen::AdditionnalBuildScreen()
{
    mAdditionalBuildComplete = true;

    //auto path = FilePath().string() + "/";
    auto name = PROJECTDIR + "/main.py";
    ::nCore::nPyBoltECSAPI::ParseFile( name );
}


void
cScreen::Draw( sf::RenderTarget* iRenderTarget )
{
    mWorld->Draw( iRenderTarget );
}


void
cScreen::Update( unsigned int iDeltaTime )
{
    mWorld->Update( iDeltaTime );
    //PyRun_SimpleString( "update()" );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Layers
// -------------------------------------------------------------------------------------


void
cScreen::PutEntityInLayer( ::nCore::nECS::nCore::cEntity * iEntity, int iLayerIndex )
{
    mWorld->AddEntityAndPutInLayer( iEntity, iLayerIndex );
}


void
cScreen::LayersEnumerator( std::function< void( ::nCore::nRender::cLayer* ) > iFunction )
{
    mWorld->LayersEnumerator( iFunction );
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------- Get/Set
// -------------------------------------------------------------------------------------


const std::string &
cScreen::Name() const
{
    return  mName;
}


void
cScreen::Name( const std::string & iName )
{
    mName = iName;
}


const nStdFileSystem::path&
cScreen::FilePath() const
{
    return  mFilePath;
}


void
cScreen::FilePath( const nStdFileSystem::path& iFilePath )
{
    mFilePath = iFilePath;
}


void
cScreen::FilePath( const std::string & iFilePath )
{
    mFilePath = iFilePath;
}


sf::View&
cScreen::View()
{
    return  mView;
}


void
cScreen::View( sf::View& iView )
{
    mView = iView;

    auto mainWindow = ::nCore::nApplication::cGlobalAccess::Instance()->TheMainWindow();
    if( !mainWindow )
        return;

    mainWindow->setView( mView );

    mWorld->LayerEngine()->LayersView( mView );
}


void
cScreen::ApplyScreenView()
{
    auto mainWindow = ::nCore::nApplication::cGlobalAccess::Instance()->TheMainWindow();
    mainWindow->setView( mView );
}


float
cScreen::ZoomFactor()
{
    return  mZoomFactor;
}


void
cScreen::ZoomBy( float iAmount )
{
    // If we want to limit the zoom, we need to check upon mView's size, as zoom() increases the view's size, so it's the only thing we can use to check such things
    mZoomFactor *= iAmount;
    mView.zoom( iAmount );
    auto mainWindow = ::nCore::nApplication::cGlobalAccess::Instance()->TheMainWindow();
    mainWindow->setView( mView );

    mWorld->LayerEngine()->ApplyZoomToLayers( iAmount );
}


bool
cScreen::Loaded() const
{
    return  mLoaded;
}


bool
cScreen::Initialized() const
{
    return  mInitialized;
}


bool
cScreen::AdditionalBuildCompleted() const
{
    return  mAdditionalBuildComplete;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ EDITOR
// -------------------------------------------------------------------------------------


::nCore::nECS::nCore::cWorld*
cScreen::World()
{
    return  mWorld;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cScreen::Resized( const sf::Event& iEvent )
{
    mWorld->Resized( iEvent );
}

void
cScreen::TextEntered( const sf::Event& iEvent )
{
    // Does nothing
}


void
cScreen::KeyPressed( const sf::Event& iEvent )
{
    mWorld->KeyPressed( iEvent );
}


void
cScreen::KeyReleased( const sf::Event& iEvent )
{
    mWorld->KeyReleased( iEvent );
}


void
cScreen::MouseWheelMoved( const sf::Event& iEvent )
{
    mWorld->MouseWheelMoved( iEvent );
}


void
cScreen::MouseWheelScrolled( const sf::Event& iEvent )
{
    mWorld->MouseWheelScrolled( iEvent );
}


void
cScreen::MouseButtonPressed( const sf::Event& iEvent )
{
    mWorld->MouseButtonPressed( iEvent );
}


void
cScreen::MouseButtonReleased( const sf::Event& iEvent )
{
    mWorld->MouseButtonReleased( iEvent );
}


void
cScreen::MouseMoved( const sf::Event& iEvent )
{
    mWorld->MouseMoved( iEvent );
}


void
cScreen::MouseEntered( const sf::Event& iEvent )
{
    mWorld->MouseEntered( iEvent );
}


void
cScreen::MouseLeft( const sf::Event& iEvent )
{
    mWorld->MouseLeft( iEvent );
}


void
cScreen::JoystickButtonPressed( const sf::Event& iEvent )
{
    mWorld->JoystickButtonPressed( iEvent );
}


void
cScreen::JoystickButtonReleased( const sf::Event& iEvent )
{
    mWorld->JoystickButtonReleased( iEvent );
}


void
cScreen::JoystickMoved( const sf::Event& iEvent )
{
    mWorld->JoystickMoved( iEvent );
}


void
cScreen::JoystickConnected( const sf::Event& iEvent )
{
    mWorld->JoystickConnected( iEvent );
}


void
cScreen::JoystickDisconnected( const sf::Event& iEvent )
{
    mWorld->JoystickDisconnected( iEvent );
}


void
cScreen::TouchBegan( const sf::Event& iEvent )
{
    mWorld->TouchBegan( iEvent );
}


void
cScreen::TouchMoved( const sf::Event& iEvent )
{
    mWorld->TouchMoved( iEvent );
}


void
cScreen::TouchEnded( const sf::Event& iEvent )
{
    mWorld->TouchEnded( iEvent );
}


void
cScreen::SensorChanged( const sf::Event& iEvent )
{
    mWorld->SensorChanged( iEvent );
}


void
cScreen::SaveXML() const
{
    if( mFilePath.empty() || !mInitialized ) // Don't save if it isn't initialized, it means the world hasn't been created -> nothing changed anyway
        return;

    ExportToFile( mFilePath );
}


void
cScreen::LoadXML()
{
    ImportFromFile( mFilePath );
    mLoaded = true;
}


void
cScreen::ExportToFile( const nStdFileSystem::path& iFilePath ) const
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* screenNode = doc.NewElement( "screen" );

    screenNode->SetAttribute( "name", mName.c_str() );

    screenNode->SetAttribute( "viewCenterX", mView.getCenter().x );
    screenNode->SetAttribute( "viewCenterY", mView.getCenter().y );
    screenNode->SetAttribute( "viewWidth", mView.getSize().x );
    screenNode->SetAttribute( "viewHeight", mView.getSize().y );
    screenNode->SetAttribute( "viewZoom", mZoomFactor );

    // WORLD
    tinyxml2::XMLElement* worldNode = doc.NewElement( "world" );
    mWorld->SaveXML( worldNode, &doc );

    screenNode->LinkEndChild( worldNode );

    // Final connection
    doc.InsertFirstChild( screenNode );

    // Save into file
    tinyxml2::XMLError error = doc.SaveFile( iFilePath.string().c_str() );
    if( error )
        printf( "Heh, couldn't save ...\n" );
}


void
cScreen::ImportFromFile( const nStdFileSystem::path& iFilePath )
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.LoadFile( iFilePath.string().c_str() );
    if( !error )
    {
        printf( "Cool\n" );
    }
    else
    {
        printf( "Error : %s\n", doc.ErrorIDToName( error ) );
        return; // Probably iFilePath isn't valid
    }

    tinyxml2::XMLElement* root = doc.FirstChildElement( "screen" );

    if( root->Attribute( "name" ) != NULL )
        mName = root->Attribute( "name" );

    tinyxml2::XMLElement* world = root->FirstChildElement( "world" );
    if( mWorld )
    {
        delete  mWorld;
        mWorld = 0;
    }

    mWorld = new ::nCore::nECS::nCore::cWorld();
    mWorld->LoadXML( world );

    // View setup
    // Why saving it like this ?
    // A screen should always fill the whole screen area.
    // Things like minimap, split screen etc, are not the screen view, but additionnal views that are set programmatically.
    // So let's say, until it's provent wrong, that we set the projectSize as default for SCREEN VIEWS.
    // We'll need a camera, that'll be positionned somewhere as the user wants

    //float viewWidth = root->FloatAttribute( "viewWidth" );
    //float viewHeight = root->FloatAttribute( "viewHeight" );
    //float viewCenterX = root->FloatAttribute( "viewCenterX" );
    //float viewCenterY = root->FloatAttribute( "viewCenterY" );
    //float viewZoom = root->FloatAttribute( "viewZoom" );
    //mView.setCenter( viewCenterX, viewCenterY );
    //mView.zoom( viewZoom );

    mView.setSize( ::nCore::nApplication::cGlobalAccess::Instance()->ProjectSize() );
    mView.setCenter( 0, 0 ); // This prevents keeping editor's position. As everytime we open editor, it'll put view at 0.0. <-- We'll need an editor's camera

    auto mainWindow = ::nCore::nApplication::cGlobalAccess::Instance()->TheMainWindow();
    if( mainWindow )
        mainWindow->setView( mView );

    mWorld->LayerEngine()->LayersView( mView );
    //mWorld->LayerEngine()->ApplyZoomToLayers( viewZoom );
}


} // namespace nScreen

