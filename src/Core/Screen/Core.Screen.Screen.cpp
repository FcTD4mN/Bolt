#include "Core.Screen.Screen.h"


#include "Core.Application.GlobalAccess.h"

#include "Core.ECS.Core.World.h"
#include "Core.ECS.Core.System.h"

#include "Core.Mapping.PhysicEntityGrid.h"

#include "Core.Render.LayerEngine.h"



// DEBUG STUFF
#include "Core.ECS.Core.Entity.h"
#include "Core.ECS.Component.Position.h"
#include "Core.ECS.Component.Size.h"
#include "Core.ECS.Component.Color.h"
#include "Core.ECS.Component.SimplePhysic.h"


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
	mZoomFactor( 1.0F )
{
}


cScreen::cScreen( const std::string & iName ) :
    mName( iName ),
    mWorld( 0 ),
	mZoomFactor( 1.0F )
{
}


void
cScreen::Initialize()
{
	if ( !mWorld )
        mWorld = new ::nECS::cWorld();
}


void
cScreen::Finalize()
{
    if( mWorld )
    {
        delete  mWorld;
        mWorld = 0;
    }
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Draw / Update
// -------------------------------------------------------------------------------------


void
cScreen::Draw( sf::RenderTarget* iRenderTarget )
{
    mWorld->Draw( iRenderTarget );
}


void
cScreen::Update( unsigned int iDeltaTime )
{
    mWorld->Update( iDeltaTime );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Layers
// -------------------------------------------------------------------------------------


void
cScreen::PutEntityInLayer( ::nECS::cEntity * iEntity, int iLayerIndex )
{
    mWorld->PutEntityInLayer( iEntity, iLayerIndex );
}


void
cScreen::SetUseLayerEngine( bool iValue )
{
    mWorld->SetUseLayerEngine( iValue );
}


void
cScreen::LayersEnumerator( std::function< void( ::nRender::cLayer* ) > iFunction )
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


const nFileSystem::path &
cScreen::FilePath() const
{
    return  mFilePath;
}


void
cScreen::FilePath( const nFileSystem::path & iFilePath )
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
	auto mainWindow = ::nGlobal::cGlobalProperties::Instance()->GetTheMainWindow();
	mainWindow->setView( mView );

	mWorld->LayerEngine()->SetLayersView( mView );
}


void
cScreen::ApplyScreenView()
{
	auto mainWindow = ::nGlobal::cGlobalProperties::Instance()->GetTheMainWindow();
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
	mZoomFactor *= iAmount;
	mView.zoom( iAmount );
	auto mainWindow = ::nGlobal::cGlobalProperties::Instance()->GetTheMainWindow();
	mainWindow->setView( mView );

	mWorld->LayerEngine()->ApplyZoomToLayers( iAmount );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ EDITOR
// -------------------------------------------------------------------------------------


::nECS::cWorld*
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
cScreen::SaveXML()
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* screenNode = doc.NewElement( "screen" );

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
    tinyxml2::XMLError error = doc.SaveFile( mFilePath.string().c_str() );
    if( error )
        printf( "Heh, couldn't save ...\n" );
}


void
cScreen::LoadXML( const std::string& iFilePath )
{
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLError error = doc.LoadFile( iFilePath.c_str() );
    if( !error )
        printf( "Cool\n" );
    else
        printf( "Error : %s\n", doc.ErrorIDToName( error ) );

    tinyxml2::XMLElement* root = doc.FirstChildElement( "screen" );
    tinyxml2::XMLElement* world = root->FirstChildElement( "world" );
    if( mWorld )
    {
        delete  mWorld;
        mWorld = 0;
    }

    mWorld = new ::nECS::cWorld();
    mWorld->LoadXML( world );

	// View setup
	float viewCenterX	= root->FloatAttribute( "viewCenterX" );
	float viewCenterY	= root->FloatAttribute( "viewCenterY" );
	float viewWidth		= root->FloatAttribute( "viewWidth" );
	float viewHeight	= root->FloatAttribute( "viewHeight" );
	float viewZoom		= root->FloatAttribute( "viewZoom" );

	mView.setSize( viewWidth, viewHeight );
	mView.setCenter( viewCenterX, viewCenterY );
	mView.zoom( viewZoom );

	auto mainWindow = ::nGlobal::cGlobalProperties::Instance()->GetTheMainWindow();
	if( mainWindow )
		mainWindow->setView( mView );

	mWorld->LayerEngine()->SetLayersView( mView );
	mWorld->LayerEngine()->ApplyZoomToLayers( viewZoom );

    mFilePath.clear();
    mFilePath = iFilePath;

	//int swall = 60;
	////int swall = 10;
	////int swall = 5;
	//for( int i = 0; i < swall; ++i )
	//{
	//	for( int j = 0; j < swall; ++j )
	//	{
	//		::nECS::cEntity* wall = new ::nECS::cEntity();
	//		wall->AddComponent( new ::nECS::cPosition( float( i ) * 800.0F / float( swall ), float( j ) * 600.0F / float( swall ) ) );
	//		wall->AddComponent( new ::nECS::cSize( 5.0f, 5.0f ) );
	//		wall->AddComponent( new ::nECS::cColor( 20, 180, 20 ) );

	//		auto physics = new ::nECS::cSimplePhysic( 5.0F, 5.0F, ::nECS::cSimplePhysic::kDynamic );
	//		physics->mVelocity.x = 1.0F;
	//		wall->AddComponent( physics );
	//		wall->AddTag( "wall" );
	//		mWorld->AddEntity( wall );
	//		mWorld->PutEntityInLayer( wall, 0 );
	//	}
	//}
}


} // namespace nScreen

