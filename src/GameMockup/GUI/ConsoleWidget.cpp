#include "GameMockup/GUI/ConsoleWidget.h"
#include "Math/Utils.h"


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
#define DEFAULT_LINE_HEIGHT 14
#define DEFAULT_FONT_COLOR  sf::Color( 220, 220, 220, 255 )

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cConsoleWidget::~cConsoleWidget()
{
}


cConsoleWidget::cConsoleWidget() :
    mKeyProcessMap(),
    mCollapsed( false ),
    mConsoleRectangle(),
    mSize(),
    mPosition(),
    mBackgroundColor(),
    mFont(),
    mInputText(),
    mOutputTextLines()
{
    mKeyProcessMap[ sf::Keyboard::BackSpace ]   =  &cConsoleWidget::ProcessBackspacePressed;
    mKeyProcessMap[ sf::Keyboard::Return ]      =  &cConsoleWidget::ProcessReturnPressed;

    mFont.loadFromFile( DEFAULT_FONT );
    mInputText.setFont( mFont );
    mInputText.setCharacterSize( DEFAULT_FONT_SIZE );
    mInputText.setFillColor( DEFAULT_FONT_COLOR );
    mInputText.setString( "Input" );

    SetSize(            DEFAULT_SIZE        , true );
    SetPosition(        DEFAULT_POSITION    , true );
    SetBackgroundColor( DEFAULT_COLOR       , true );
    UpdateGeometryAndStyle();
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------ Geometry and Style Getters / Setters
// -------------------------------------------------------------------------------------


void
cConsoleWidget::SetSize( const  sf::Vector2f&  iSize, bool iNoUpdate )
{
    float w = iSize.x;
    float h = iSize.y;
    mSize = sf::Vector2f( w, h );
    UpdateGeometryAndStyle( iNoUpdate );
}


void
cConsoleWidget::SetPosition(  const  sf::Vector2f&  iPosition, bool iNoUpdate )
{
    float x = iPosition.x;
    float y = iPosition.y;
    mPosition = sf::Vector2f( x, y );
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


int
cConsoleWidget::NVisibleRows()  const
{
    return  int( mSize.y ) / DEFAULT_LINE_HEIGHT;
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

    int  nOutputTextLines = NVisibleRows() -1; // -1 because 1 line is reserved for input text.
    mOutputTextLines.resize( nOutputTextLines );
    for( int i = 0; i < nOutputTextLines; ++i )
    {
        mOutputTextLines[i].setFont( mFont );
        mOutputTextLines[i].setCharacterSize( DEFAULT_FONT_SIZE );
        mOutputTextLines[i].setFillColor( DEFAULT_FONT_COLOR );
        mOutputTextLines[i].setString( ">: Output" );
        float x = 0;
        float y = float( i * DEFAULT_LINE_HEIGHT );
        sf::Vector2f  outputLinePosition = sf::Vector2f( x, y );
        mOutputTextLines[i].setPosition( outputLinePosition );
    }
    
    float x = 0;
    float y = float( nOutputTextLines * DEFAULT_LINE_HEIGHT );
    sf::Vector2f  inputLinePosition = sf::Vector2f( x, y );
    mInputText.setPosition( inputLinePosition );
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
    int  nOutputTextLines = NVisibleRows() -1; // -1 because 1 line is reserved for input text.
    for( int i = 0; i < nOutputTextLines; ++i )
    {
        iRenderTarget->draw( mOutputTextLines[i] );
    }
    iRenderTarget->draw( mInputText );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cConsoleWidget::TextEntered( const sf::Event& iEvent )
{
    auto  unicode = iEvent.text.unicode;

    // Handle ASCII characters only
    if ( unicode > 0X0020 && unicode < 0X007E )
    {
        std::string str = mInputText.getString();
        char charCode = static_cast<char>( unicode );
        str += charCode;
        mInputText.setString( str );
    }
}


void
cConsoleWidget::KeyPressed( const sf::Event& iEvent )
{
    auto key = iEvent.key.code;
    // If Key Exists in mKeyProcessMap
    if( ! ( mKeyProcessMap.find( key ) == mKeyProcessMap.end() ) )
    {
        (this->*mKeyProcessMap[ key ])();
    }
}


void
cConsoleWidget::KeyReleased( const sf::Event& iEvent )
{
    auto key = iEvent.key.code;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cConsoleWidget::ProcessBackspacePressed()
{
    std::string str = mInputText.getString();

    if( str.length() )
    {
        str.pop_back();
    }

    mInputText.setString( str );
}


void
cConsoleWidget::ProcessReturnPressed()
{

}


} // namespace  nGUI

