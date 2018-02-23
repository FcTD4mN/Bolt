#include "GameMockup/GUI/ConsoleWidget.h"


#include "Math/Utils.h"
#include "Base/Clipboard.h"


namespace  nGUI
{

// -------------------------------------------------------------------------------------
// ---------------------------------------------------------------------- Default Values
// -------------------------------------------------------------------------------------


#define DEFAULT_SIZE                        sf::Vector2f( 600.f, 200.f )
#define DEFAULT_COLOR                       sf::Color( 20, 20, 20, 255 )
#define DEFAULT_FONT                        "resources/Fonts/SourceCodePro-Regular.ttf"
#define DEFAULT_FONT_SIZE                   12
#define DEFAULT_LINE_HEIGHT                 14
#define DEFAULT_FONT_COLOR                  sf::Color( 220, 220, 220, 255 )
#define DEFAULT_CURSOR_COLOR                DEFAULT_FONT_COLOR
#define DEFAULT_CURSOR_SIZE                 sf::Vector2f( 2.f, float( DEFAULT_LINE_HEIGHT ) )
#define DEFAULT_CURSOR_TOGGLE_TIME_MS       200


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cConsoleWidget::~cConsoleWidget()
{
}


cConsoleWidget::cConsoleWidget() :
    mKeyPressedProcessMap(),
    mCTRLKeyPressedProcessMap(),
    mCollapsed( false ),
    mCursorToggled( false ),
    mCursorToggleTimeMs( DEFAULT_CURSOR_TOGGLE_TIME_MS ),
    mCursorTimerElapsedTimeMs( 0 ),
    mCursorIndex( 0 ),
    mCharWidth( 0 ),
    mConsoleRectangle(),
    mCursorRectangle(),
    mSize(),
    mPosition(),
    mBackgroundColor(),
    mFont(),
    mInputText(),
    mOutputTextLines()
{
    // Single Key Press
    mKeyPressedProcessMap[ sf::Keyboard::BackSpace ]        =  &cConsoleWidget::ProcessBackspacePressed;
    mKeyPressedProcessMap[ sf::Keyboard::Return ]           =  &cConsoleWidget::ProcessReturnPressed;
    mKeyPressedProcessMap[ sf::Keyboard::Escape ]           =  &cConsoleWidget::ProcessEscapePressed;
    mKeyPressedProcessMap[ sf::Keyboard::Left ]             =  &cConsoleWidget::ProcessLeftPressed;
    mKeyPressedProcessMap[ sf::Keyboard::Right ]            =  &cConsoleWidget::ProcessRightPressed;

    // CTRL + Key Press
    mCTRLKeyPressedProcessMap[ sf::Keyboard::V ]            =  &cConsoleWidget::ProcessCTRLVPressed;
    mCTRLKeyPressedProcessMap[ sf::Keyboard::BackSpace ]    =  &cConsoleWidget::ProcessCTRLBackspacePressed;

    mCursorRectangle.setSize(       DEFAULT_CURSOR_SIZE );
    mCursorRectangle.setPosition(   sf::Vector2f() );
    mCursorRectangle.setFillColor(  DEFAULT_CURSOR_COLOR );

    mFont.loadFromFile( DEFAULT_FONT );
    mInputText.setFont( mFont );
    mInputText.setCharacterSize( DEFAULT_FONT_SIZE );
    mInputText.setFillColor( DEFAULT_FONT_COLOR );
    mInputText.setString( "Input" );

    // The next three functions have the optional NoUpdate Boolean parameter set to true,
    // in order the to avoid calling UpdateGeometryAndStyle too often.
    SetSize(            DEFAULT_SIZE        , true );
    SetPosition(        sf::Vector2f()      , true );
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


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------- Internal Text Geometry
// -------------------------------------------------------------------------------------


void
cConsoleWidget::UpdateGeometryAndStyle( bool  iNoUpdate )
{
    if( iNoUpdate )
        return;

    {
        sf::Text  sampleText;
        sampleText.setFont( mFont );
        sampleText.setCharacterSize( DEFAULT_FONT_SIZE );
        sampleText.setString( "oo" );
        sf::Vector2f pos = sampleText.findCharacterPos( 1 );
        mCharWidth = unsigned int( pos.x );
    }

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

    float cursorX = 0;
    float cursorY = y;
    mCursorRectangle.setPosition( cursorX, cursorY );
    MatchCursorPosition();
}


int
cConsoleWidget::NVisibleRows()  const
{
    return  int( mSize.y ) / DEFAULT_LINE_HEIGHT;
}


void
cConsoleWidget::IncrementCursorPosition()
{
    std::string str = mInputText.getString();
    int length = int( str.length() );

    if( mCursorIndex >= length )
    {
        mCursorIndex = length;
        UpdateCursorPosition();
        return;
    }

    ++mCursorIndex;
    mCursorRectangle.move( float( mCharWidth ), 0.f );
}


void 
cConsoleWidget::DecrementCursorPosition()
{
    if( mCursorIndex <= 0 )
    {
        mCursorIndex = 0;
        UpdateCursorPosition();
        return;
    }

    --mCursorIndex;
    mCursorRectangle.move( -float( mCharWidth ), 0.f );
}


void
cConsoleWidget::ResetCursorPosition()
{
    mCursorIndex = 0;
    sf::Vector2f  cursorPosition = mCursorRectangle.getPosition();
    mCursorRectangle.setPosition( 0.f, cursorPosition.y );
}


void
cConsoleWidget::UpdateCursorPosition()
{
    sf::Vector2f  cursorPosition = mCursorRectangle.getPosition();
    mCursorRectangle.setPosition( float( mCursorIndex * mCharWidth ), cursorPosition.y );
}


void
cConsoleWidget::MatchCursorPosition()
{
    std::string str = mInputText.getString();
    mCursorIndex = int( str.length() );
    UpdateCursorPosition();
}

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Public Text Manipulation
// -------------------------------------------------------------------------------------


void
cConsoleWidget::ClearInput()
{
    // Clear input content
    mInputText.setString("");
    ResetCursorPosition();
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cConsoleWidget::Update( unsigned int iDeltaTime )
{
    mCursorTimerElapsedTimeMs += iDeltaTime;
    if( mCursorTimerElapsedTimeMs > mCursorToggleTimeMs )
    {
        mCursorTimerElapsedTimeMs = 0;
        mCursorToggled = !mCursorToggled;
    }
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

    if( mCursorToggled )
    {
        iRenderTarget->draw( mCursorRectangle );
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cConsoleWidget::TextEntered( const sf::Event& iEvent )
{
    auto  unicode = iEvent.text.unicode;

    // Handle ASCII characters only
    if ( unicode > 0X0020 && unicode < 0X007E || unicode == 32 ) // unicode == 32 for whitespace
    {
        std::string str = mInputText.getString();
        char charCode = static_cast<char>( unicode );
        str += charCode;
        mInputText.setString( str );
        IncrementCursorPosition();
    }
}


void
cConsoleWidget::KeyPressed( const sf::Event& iEvent )
{
    auto key = iEvent.key;
    auto code = key.code;

    if( key.alt )           // Alt Modifier
    {
        // Nothing ATM
    }
    else if( key.control )  // Control Modifier
    {
        // If Key Exists in mKeyProcessMap
        if( ! ( mCTRLKeyPressedProcessMap.find( code ) == mCTRLKeyPressedProcessMap.end() ) )
        {
            (this->*mCTRLKeyPressedProcessMap[ code ])();
        }
    }
    else if( key.shift )    // Shift Modifier
    {
        // Nothing ATM
    }
    else if( key.system )   // System Modifier
    {
        // Nothing ATM
    }
    else                    // No Modifier
    {
        // If Key Exists in mKeyProcessMap
        if( ! ( mKeyPressedProcessMap.find( code ) == mKeyPressedProcessMap.end() ) )
        {
            (this->*mKeyPressedProcessMap[ code ])();
        }
    }
}


void
cConsoleWidget::KeyReleased( const sf::Event& iEvent )
{
    auto key = iEvent.key.code;
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------- Event Processing
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
    DecrementCursorPosition();
}


void
cConsoleWidget::ProcessReturnPressed()
{
    std::string inputStr = mInputText.getString();

    // Shift output rows content upwards
    for( int i = 0; i < NVisibleRows() -2; ++i )
    {
        std::string currentOutputStr = mOutputTextLines[i + 1 ].getString();
        mOutputTextLines[i].setString( currentOutputStr );
    }

    // Set last output row content with input content
    mOutputTextLines.back().setString( inputStr );

    ClearInput();
}


void
cConsoleWidget::ProcessEscapePressed()
{
    ClearInput();
}


void
cConsoleWidget::ProcessLeftPressed()
{
    DecrementCursorPosition();
}
void
cConsoleWidget::ProcessRightPressed()
{
    IncrementCursorPosition();
}


void
cConsoleWidget::ProcessCTRLVPressed()
{
    // Append clipboard text content to input content
    std::string clipboardStr = GetClipboardText();
    std::string inputStr = mInputText.getString();
    std::string resultStr = inputStr + clipboardStr;
    mInputText.setString( resultStr );
}

void
cConsoleWidget::ProcessCTRLBackspacePressed()
{
    ClearInput();
}


} // namespace  nGUI

