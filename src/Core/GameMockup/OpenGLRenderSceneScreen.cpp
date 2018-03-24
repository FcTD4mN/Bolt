#include <GL/glew.h>
#include <gl/GLU.h>
#include "SFML/OpenGL.hpp"


#include "GameMockup/OpenGLRenderSceneScreen.h"
#include "GameMockup/GameApplication.h"
#include "GameMockup/GameApplication.h"


#include <iostream>


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cOpenGLRenderSceneScreen::~cOpenGLRenderSceneScreen()
{
}


cOpenGLRenderSceneScreen::cOpenGLRenderSceneScreen() :
    mConsoleWidget( 0 )
{
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cOpenGLRenderSceneScreen::Initialize()
{
    cGameApplication::App()->SetAppTitle( "OpenGL Render Scene" );
    auto window  = cGameApplication::App()->Window();
    mConsoleWidget = new  ::nGUI::cConsoleWidget();
    sf::Vector2f  availableGeometry = sf::Vector2f( float( window->getSize().x ),
                                                    float( window->getSize().y ) );
    double posRatio     = 3./5.;
    double sizeRatio    = 2./5.;
    sf::Vector2f  size      = sf::Vector2f( availableGeometry.x, availableGeometry.y * float(sizeRatio) );
    sf::Vector2f  position  = sf::Vector2f( 0, availableGeometry.y * float(posRatio));
    mConsoleWidget->SetSize( size );
    mConsoleWidget->SetPosition( position );
    //mConsoleWidget->ToggleVisibility();

    cGameApplication::App()->Window()->setKeyRepeatEnabled( true );

    // Init OpenGL stuff
    sf::ContextSettings settings = window->getSettings();
    ::nBoltScript::Env()->Print( "depth bits:" + std::to_string( settings.depthBits ) + "\n" );
    ::nBoltScript::Env()->Print( "stencil bits:" + std::to_string( settings.stencilBits ) + "\n" );
    ::nBoltScript::Env()->Print( "antialiasing level:" + std::to_string( settings.antialiasingLevel ) + "\n" );
    ::nBoltScript::Env()->Print( "version:" + std::to_string( settings.majorVersion ) + "\n" );

    std::cout << glGetString(GL_VERSION) << std::endl;

    window->setVerticalSyncEnabled(true);

    window->setActive();
    glewInit();

    int st = 40;
    for( int i = 0; i < st; ++i )
    {
        for( int j = 0; j < st; ++j )
        {
            for( int k = 0; k < st; ++k )
            {
                int x = i - 20;
                int y = j - 20;
                int z = k - 20;
                if( sqrt( x*x + y*y + z*z ) < 20.0 )
                    mMap.SafeSetMaterial( x, y, z, ( rand()%254 ) + 1 );
            }
        }
    }

    for( int i = -10; i < 10; ++i )
    {
        for( int j = -10; j < 10; ++j )
        {
            for( int k = -10; k < 10; ++k )
            {
                mMap.SafeSetMaterial( i, j, k, 0 );
            }
        }
    }

    for( int i = -5; i < 5; ++i )
    {
        for( int j = 0; j < 30; ++j )
        {
            for( int k = -5; k < 5; ++k )
            {
                mMap.SafeSetMaterial( i, j, k, 0 );
            }
        }
    }

    mMap.UpdateChunksVBOs();

    glViewport(0, 0, window->getSize().x, window->getSize().y);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double ratio = double(window->getSize().x) / double(window->getSize().y);
    gluPerspective(50.f, ratio, 5.f, 500.f);

    mShader = cShader( "resources/Shared/Shaders/couleur3D.vert", "resources/Shared/Shaders/couleur3D.frag" );

    /*
    std::vector< sf::Vector3f > Vertices;
    Vertices.resize( NVERTICES );
    Vertices[0] = sf::Vector3f(-1.0f, -1.0f, 0.0f);
    Vertices[1] = sf::Vector3f(1.0f, -1.0f, 0.0f);
    Vertices[2] = sf::Vector3f(0.0f, 1.0f, 0.0f);
    Vertices[3] = sf::Vector3f(1.0f, -1.0f, 0.0f);
    Vertices[4] = sf::Vector3f(0.0f, 1.0f, 0.0f);
    Vertices[5] = sf::Vector3f(5.0f, 0.0f, 0.0f);
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), &Vertices[0].x, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    */
}


void
cOpenGLRenderSceneScreen::Finalize()
{
    if( mConsoleWidget )
    {
        delete  mConsoleWidget;
        mConsoleWidget = 0;
    }
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------- Main Running functions
// -------------------------------------------------------------------------------------


void
cOpenGLRenderSceneScreen::Draw( sf::RenderTarget* iRenderTarget )
{
    auto window = ::cGameApplication::App()->Window();
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef( 0.f, 0.f, -50.0f );
    glRotatef( mClock.getElapsedTime().asSeconds() * 50.f, 0.f, 0.f, -1.f );
    glRotatef( mClock.getElapsedTime().asSeconds() * 20.f, 0.f, 1.f, 0.f );
    glRotatef( mClock.getElapsedTime().asSeconds() * 80.f, 1.f, 0.f, 0.f );

    //glUseProgram(mShader.getProgramID());
    glPushMatrix();
    mMap.RenderVBOs();
    glPopMatrix();
    //glUseProgram(0);

    /*
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, NVERTICES);
    glDisableVertexAttribArray(0);
    */

    window->pushGLStates();

    mConsoleWidget->Draw( iRenderTarget );

    window->popGLStates();
}


void
cOpenGLRenderSceneScreen::Update( unsigned int iDeltaTime )
{
    mConsoleWidget->Update( iDeltaTime );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cOpenGLRenderSceneScreen::Resized( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::TextEntered( const sf::Event& iEvent )
{
    mConsoleWidget->TextEntered( iEvent );
}


void
cOpenGLRenderSceneScreen::KeyPressed( const sf::Event& iEvent )
{
    mConsoleWidget->KeyPressed( iEvent );
}


void
cOpenGLRenderSceneScreen::KeyReleased( const sf::Event& iEvent )
{
    mConsoleWidget->KeyReleased( iEvent );
}


void
cOpenGLRenderSceneScreen::MouseWheelMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::MouseWheelScrolled( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::MouseButtonPressed( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::MouseButtonReleased( const sf::Event& iEvent )
{
}


void
cOpenGLRenderSceneScreen::MouseMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::MouseEntered( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::MouseLeft( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::JoystickButtonPressed( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::JoystickButtonReleased( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::JoystickMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::JoystickConnected( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::JoystickDisconnected( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::TouchBegan( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::TouchMoved( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::TouchEnded( const sf::Event& iEvent )
{
    // Does nothing
}


void
cOpenGLRenderSceneScreen::SensorChanged( const sf::Event& iEvent )
{
    // Does nothing
}

