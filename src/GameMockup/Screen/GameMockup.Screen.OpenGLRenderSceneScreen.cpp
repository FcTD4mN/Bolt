#include "GameMockup.Screen.OpenGLRenderSceneScreen.h"

#include "GameMockup.Application.GameApplication.h"


#include <GL/glew.h>
#include <gl/GLU.h>
#include <SFML/OpenGL.hpp>


#include <iostream>


namespace nScreen {


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
    ::nApplication::cGameApplication::App()->SetAppTitle( "OpenGL Render Scene" );
    auto window  = ::nApplication::cGameApplication::App()->Window();
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

    ::nApplication::cGameApplication::App()->Window()->setKeyRepeatEnabled( true );

    // Init OpenGL stuff
    sf::ContextSettings settings = window->getSettings();
    ::nBoltScript::Env()->Print( "depth bits:" + std::to_string( settings.depthBits ) + "\n" );
    ::nBoltScript::Env()->Print( "stencil bits:" + std::to_string( settings.stencilBits ) + "\n" );
    ::nBoltScript::Env()->Print( "antialiasing level:" + std::to_string( settings.antialiasingLevel ) + "\n" );
    ::nBoltScript::Env()->Print( "version:" + std::to_string( settings.majorVersion ) + "\n" );

    std::cout << glGetString(GL_VERSION) << std::endl;

    //window->setVerticalSyncEnabled(true);

    window->setActive();
    glewInit();

    glViewport(0, 0, window->getSize().x, window->getSize().y);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double ratio = double(window->getSize().x) / double(window->getSize().y);
    gluPerspective(50.f, ratio, 5.f, 1500.f);

    mShader = ::nShaders::cShader( "resources/Shared/Shaders/basicLight.vert", "resources/Shared/Shaders/basicLight.frag" );

    GLuint shaderProgramID = mShader.getProgramID();
    glUseProgram( shaderProgramID );

    int location = 0;
    location = glGetUniformLocation( shaderProgramID, "ambiantColor" );
    sf::Vector3f ambientColor = sf::Vector3f( 0.6f, 0.56f, 0.7f );
    glUniform3f(location, ambientColor.x, ambientColor.y, ambientColor.z );

    location = glGetUniformLocation( shaderProgramID, "ambiantIntensity" );
    float ambiantIntensity = 0.8f;
    glUniform1f(location, ambiantIntensity );

    location = glGetUniformLocation( shaderProgramID, "diffuseColor" );
    sf::Vector3f diffuseColor = sf::Vector3f( 0.95f, 0.9f, 0.5f );
    glUniform3f(location, diffuseColor.x, diffuseColor.y, diffuseColor.z );

    location = glGetUniformLocation( shaderProgramID, "diffuseDirection" );
    sf::Vector3f diffuseDirection = sf::Vector3f( 0.365148f, -0.912871f, -0.182574f );
    glUniform3f(location, diffuseDirection.x, diffuseDirection.y, diffuseDirection.z );

    location = glGetUniformLocation( shaderProgramID, "diffuseIntensity" );
    float diffuseIntensity = 1.0f;
    glUniform1f(location, diffuseIntensity );

    glUseProgram(0);

    std::function< void( void )> f = [=]( void ) {
        //mMap.PurgeAllChunks();
        //mMap.UpdateChunksVBOs();
    };

    std::function< void( void )> g = [=]( void ) {
        /*int st = 40;
        for( int i = 0; i < st; ++i )
        {
            for( int k = 0; k < st; ++k )
            {
                int x = i - 20;
                int y = 0;
                int z = k - 20;
                if( sqrt( x*x + z*z ) < 20.0 )
                    mMap.SafeSetMaterial( x, y, z, ( 89 ) + 1 );
            }
        }

        st = 10;
        for( int i = 0; i < st; ++i )
        {
            for( int k = 0; k < st; ++k )
            {
                int x = i - 5;
                int y = 10;
                int z = k - 5;
                mMap.SafeSetMaterial( x, y, z, ( 110 ) + 1 );
            }
        }

        st = 10;
        for( int i = 1; i < st; ++i )
        {
            mMap.SafeSetMaterial( -5, i, -5, ( 110 ) + 1 );
            mMap.SafeSetMaterial( -5, i, +4, ( 110 ) + 1 );
            mMap.SafeSetMaterial( +4, i, -5, ( 110 ) + 1 );
            mMap.SafeSetMaterial( +4, i, +4, ( 110 ) + 1 );
        }*/

        /////////////////////////////////////////////////////////////////////////////////////////////

        /*
        int ray = 7;
        int diam = ray *2;
        int n = 25;
        int nshift = - n / 2;
        int shift = - diam / 2;
        int padding = diam;

        for( int i = 0; i < n; ++i )
        {
                for( int k = 0; k < n; ++k )
                {
                    float xbase = ( i + nshift ) * padding;
                    float ybase = ( 20 );
                    float zbase = ( k + nshift ) * padding;

                    for( int l = 0; l < diam; ++l )
                    {
                        for( int m = 0; m < diam; ++m )
                        {
                            for( int o = 0; o < diam; ++o )
                            {
                                float x = ( l + shift );
                                float y = ( m + shift );
                                float z = ( o + shift );
                                float lenght = sqrt( x*x + y*y + z*z );
                                if( lenght < float( ray ) )
                                    mMap.SafeSetMaterial( xbase + x, ybase + y, zbase + z, 14 );

                            }
                        }
                    }

                }
        }
        */

        ////////////////////////////////////////////////////////////////
        /*
        int sak = 16;
        for( int i = 0; i < sak; ++i )
        {
            for( int j = 0; j < sak; ++j )
            {
                for( int k = 0; k < sak; ++k )
                {
                    mMap2.Set( i, j, k, 12 );

                }
            }
        }
        */

        mMap2.Set( 0, 0, 0, 1 );

    };

    ::nBoltScript::Env()->RegisterFunction( "clearMap", f );
    ::nBoltScript::Env()->RegisterFunction( "genTest", g );

    ::nBoltScript::Env()->ProcessRawString( "genTest" );
    /*
    sf::Vector3f Vertices[6];
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
    auto window = ::nApplication::cGameApplication::App()->Window();
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    int a = 0;
    glTranslatef( 0.f, 0.f, -400.f );
    //glRotatef( mClock.getElapsedTime().asSeconds() * 50.f, 0.f, 0.f, -1.f );
    glRotatef( 45.f, 1.f, 0.f, 0.f );
    glRotatef( mClock.getElapsedTime().asSeconds() * 20.f, 0.f, 1.f, 0.f );

    //GLuint shaderProgramID = mShader.getProgramID();
    //glUseProgram( shaderProgramID );

    //mMap.RenderVBOs( shaderProgramID );

    mMap2.RenderOctDebug();

    //glUseProgram(0);

    /*
    glEnableVertexAttribArray(0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
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


} // namespace nScreen

