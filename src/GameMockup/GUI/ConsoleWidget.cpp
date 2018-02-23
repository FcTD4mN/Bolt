#include "GameMockup/GUI/ConsoleWidget.h"


namespace  nGUI
{

// -------------------------------------------------------------------------------------
// ---------------------------------------------------------------------- Default Values
// -------------------------------------------------------------------------------------


#define DEFAULT_SIZE        sf::Vector2f( 600.f,   200.f )
#define DEFAULT_POSITION    sf::Vector2f( 0.f, 0.f )
#define DEFAULT_COLOR       sf::Color( 20, 20, 20, 255 )
#define DEFAULT_FONT        "resources/Fonts/SourceCodePro-Regular.ttf"
#define DEFAULT_FONT_SIZE   12
#define DEFAULT_FONT_COLOR  sf::Color( 220, 220, 220, 255 )

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cConsoleWidget::~cConsoleWidget()
{
}


cConsoleWidget::cConsoleWidget() :
    mCollapsed( false ),
    mConsoleRectangle(),
    mSize(),
    mPosition(),
    mBackgroundColor(),
    mFont(),
    mInputText(),
    mOutputTextLines()
{
    SetSize(            DEFAULT_SIZE        , true );
    SetPosition(        DEFAULT_POSITION    , true );
    SetBackgroundColor( DEFAULT_COLOR       , true );
    UpdateGeometryAndStyle();

    mFont.loadFromFile( DEFAULT_FONT );
    mInputText.setFont( mFont );
    mInputText.setCharacterSize( DEFAULT_FONT_SIZE );
    mInputText.setFillColor( DEFAULT_FONT_COLOR );
    mInputText.setString( "Input" );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------ Geometry and Style Getters / Setters
// -------------------------------------------------------------------------------------


void
cConsoleWidget::SetSize( const  sf::Vector2f&  iSize, bool iNoUpdate )
{
    mSize = iSize;
    UpdateGeometryAndStyle( iNoUpdate );
}


void
cConsoleWidget::SetPosition(  const  sf::Vector2f&  iPosition, bool iNoUpdate )
{
    mPosition = iPosition;
    UpdateGeometryAndStyle( iNoUpdate );
}


void
cConsoleWidget::SetBackgroundColor(  const  sf::Color&  iColor, bool iNoUpdate )
{
    mBackgroundColor = iColor;
    UpdateGeometryAndStyle( iNoUpdate );
}


const  sf::Vector2f&
cConsoleWidget::GetSize()  const
{
    return  mSize;
}


const  sf::Vector2f&
cConsoleWidget::SetPosition()  const
{
    return  mPosition;
}


const  sf::Color&
cConsoleWidget::SetBackgroundColor()  const
{
    return  mBackgroundColor;
}

// -------------------------------------------------------------------------------------
// ----------------------------------------------------------- Geometry and Style Update
// -------------------------------------------------------------------------------------


void
cConsoleWidget::UpdateGeometryAndStyle( bool  iNoUpdate )
{
    if( iNoUpdate )
        return;

    mConsoleRectangle.setSize(      mSize );
    mConsoleRectangle.setPosition(  mPosition );
    mConsoleRectangle.setFillColor( mBackgroundColor );

    mInputText.setPosition( mPosition );
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cConsoleWidget::Initialize()
{
}


void
cConsoleWidget::Finalize()
{
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cConsoleWidget::Update()
{
}


void
cConsoleWidget::Draw( sf::RenderTarget* iRenderTarget )
{
    iRenderTarget->draw( mConsoleRectangle );
    iRenderTarget->draw( mInputText );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cConsoleWidget::KeyPressed( const sf::Event& iEvent )
{
}


void
cConsoleWidget::KeyReleased( const sf::Event& iEvent )
{
}


} // namespace  nGUI

