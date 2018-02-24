#include "GameMockup/GUI/ConsoleWidget.h"


#include "Math/Utils.h"
#include "Base/Clipboard.h"


namespace  nGUI
{

// -------------------------------------------------------------------------------------
// ---------------------------------------------------------------------- Default Values
// -------------------------------------------------------------------------------------


#define DEFAULT_SIZE                        sf::Vector2f( 600.f, 200.f )
#define DEFAULT_COLOR                       sf::Color( 220, 220, 220, 255 )
#define DEFAULT_FONT                        "resources/Fonts/SourceCodePro-Regular.ttf"
#define DEFAULT_FONT_SIZE                   12
#define DEFAULT_LINE_HEIGHT                 14
#define DEFAULT_FONT_COLOR                  sf::Color( 20, 20, 20, 255 )
#define DEFAULT_CURSOR_COLOR                DEFAULT_FONT_COLOR
#define DEFAULT_CURSOR_SIZE                 sf::Vector2f( 2.f, float( DEFAULT_LINE_HEIGHT ) )
#define DEFAULT_CURSOR_TOGGLE_TIME_MS       200
#define DEFAULT_TAB_WHITESPACE              4
#define DEFAULT_SELECTION_BG_COLOR          sf::Color( 255, 255, 0, 255 )
#define DEFAULT_SELECTION_FG_COLOR          sf::Color( 255, 255, 0, 85 )


#define KEY_EXISTS( iMap, iKey )            ( ! ( iMap.find( iKey ) == iMap.end() ) )

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cConsoleWidget::~cConsoleWidget()
{
}


cConsoleWidget::cConsoleWidget() :
    mKeyPressedProcessMap(),
    mCTRLKeyPressedProcessMap(),
    mShiftKeyPressedProcessMap(),
    mCollapsed( false ),
    mCursorToggled( false ),
    mCursorToggleTimeMs( DEFAULT_CURSOR_TOGGLE_TIME_MS ),
    mCursorTimerElapsedTimeMs( 0 ),
    mCursorIndex( 0 ),
    mSelectionStartIndex( 0 ),
    mCharWidth( 0 ),
    mSelectionOccuring( false ),
    mConsoleRectangle(),
    mCursorRectangle(),
    mSelectionBGRectangle(),
    mSelectionFGRectangle(),
    mSize(),
    mPosition(),
    mBackgroundColor(),
    mFont(),
    mInputText(),
    mOutputTextLines()
{
    // Single Key Press
    mKeyPressedProcessMap[ sf::Keyboard::BackSpace ]        =  &cConsoleWidget::ProcessBackspacePressed;
    mKeyPressedProcessMap[ sf::Keyboard::Tab ]              =  &cConsoleWidget::ProcessTabPressed;
    mKeyPressedProcessMap[ sf::Keyboard::Return ]           =  &cConsoleWidget::ProcessReturnPressed;
    mKeyPressedProcessMap[ sf::Keyboard::Escape ]           =  &cConsoleWidget::ProcessEscapePressed;
    mKeyPressedProcessMap[ sf::Keyboard::Left ]             =  &cConsoleWidget::ProcessLeftPressed;
    mKeyPressedProcessMap[ sf::Keyboard::Right ]            =  &cConsoleWidget::ProcessRightPressed;
    mKeyPressedProcessMap[ sf::Keyboard::Home ]             =  &cConsoleWidget::ProcessHomePressed;
    mKeyPressedProcessMap[ sf::Keyboard::End ]              =  &cConsoleWidget::ProcessEndPressed;
    mKeyPressedProcessMap[ sf::Keyboard::Delete ]           =  &cConsoleWidget::ProcessDeletePressed;

    // CTRL + Key Press
    mCTRLKeyPressedProcessMap[ sf::Keyboard::V ]            =  &cConsoleWidget::ProcessCTRLVPressed;
    mCTRLKeyPressedProcessMap[ sf::Keyboard::BackSpace ]    =  &cConsoleWidget::ProcessCTRLBackspacePressed;
    mCTRLKeyPressedProcessMap[ sf::Keyboard::Left ]         =  &cConsoleWidget::ProcessCTRLLeftPressed;
    mCTRLKeyPressedProcessMap[ sf::Keyboard::Right ]        =  &cConsoleWidget::ProcessCTRLRightPressed;

    // Shift + Key Press
    mShiftKeyPressedProcessMap[ sf::Keyboard::Tab ]         =  &cConsoleWidget::ProcessShiftTabPressed;
    mShiftKeyPressedProcessMap[ sf::Keyboard::Left ]        =  &cConsoleWidget::ProcessShiftLeftPressed;
    mShiftKeyPressedProcessMap[ sf::Keyboard::Right ]       =  &cConsoleWidget::ProcessShiftRightPressed;

    mCursorRectangle.setSize(       DEFAULT_CURSOR_SIZE );
    mCursorRectangle.setPosition(   sf::Vector2f() );
    mCursorRectangle.setFillColor(  DEFAULT_CURSOR_COLOR );

    mSelectionBGRectangle.setFillColor(  DEFAULT_SELECTION_BG_COLOR );
    mSelectionFGRectangle.setFillColor(  DEFAULT_SELECTION_FG_COLOR );

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
        sampleText.setString( ">>" );
        sf::Vector2f pos = sampleText.findCharacterPos( 1 );
        mCharWidth = int( pos.x );
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
cConsoleWidget::SelectionFirstIndex()
{
    return  mCursorIndex <= mSelectionStartIndex ? mCursorIndex : mSelectionStartIndex;
}


int
cConsoleWidget::SelectionLastIndex()
{
    return  mCursorIndex <= mSelectionStartIndex ? mSelectionStartIndex : mCursorIndex;
    
}


void
cConsoleWidget::UpdateSelectionGeometry()
{
    sf::Vector2f  inputTextPosition = mInputText.getPosition();
    float  y = inputTextPosition.y;
    float x1 = float( SelectionFirstIndex() * mCharWidth );
    float x2 = float( SelectionLastIndex() * mCharWidth );
    float dx = x2 - x1;

    sf::Vector2f  selectionPosition = sf::Vector2f( x1, y );
    sf::Vector2f  selectionSize     = sf::Vector2f( dx, DEFAULT_LINE_HEIGHT );
    mSelectionBGRectangle.setPosition( selectionPosition );
    mSelectionFGRectangle.setPosition( selectionPosition );
    mSelectionBGRectangle.setSize( selectionSize );
    mSelectionFGRectangle.setSize( selectionSize );
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
cConsoleWidget::MoveCursorPosition( int iDelta )
{
    mCursorIndex = int( int( mCursorIndex ) + iDelta );
    mCursorRectangle.move( float( iDelta * mCharWidth ), 0.f );
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

    iRenderTarget->draw( mSelectionBGRectangle );
    iRenderTarget->draw( mInputText );

    if( mCursorToggled )
    {
        iRenderTarget->draw( mCursorRectangle );
    }
    iRenderTarget->draw( mSelectionFGRectangle );
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cConsoleWidget::TextEntered( const sf::Event& iEvent )
{
    // Handle ASCII characters only
    auto  unicode = iEvent.text.unicode;
    bool  unicodeInput = unicode > 0X0020 && unicode < 0X007E || unicode == 32;

    if( !unicodeInput )
        return;

    std::string str = mInputText.getString();
    char charCode = static_cast<char>( unicode );
    std::string charStr;
    charStr.push_back( charCode );
    str.insert( mCursorIndex, charStr );
    mInputText.setString( str );
    IncrementCursorPosition();
}


void
cConsoleWidget::KeyPressed( const sf::Event& iEvent )
{
    auto key = iEvent.key;
    auto code = key.code;

    if( code == sf::Keyboard::LShift || code == sf::Keyboard::RShift )
    {
        mSelectionStartIndex = mCursorIndex;
        mSelectionOccuring = true;
    }

    if( key.alt )           // Alt Modifier
    {
        // Nothing ATM


    }
    else if( key.control )  // Control Modifier
    {
        if( KEY_EXISTS( mCTRLKeyPressedProcessMap, code ) )
        {
            (this->*mCTRLKeyPressedProcessMap[ code ])();
        }


    }
    else if( key.shift )    // Shift Modifier
    {
        if( KEY_EXISTS( mShiftKeyPressedProcessMap, code ) )
        {
            (this->*mShiftKeyPressedProcessMap[ code ])();
        }


    }
    else if( key.system )   // System Modifier
    {
        // Nothing ATM


    }
    else                    // No Modifier
    {
        if( KEY_EXISTS( mKeyPressedProcessMap, code ) )
        {
            (this->*mKeyPressedProcessMap[ code ])();
        }


    }
}


void
cConsoleWidget::KeyReleased( const sf::Event& iEvent )
{
    auto key = iEvent.key;
    auto code = key.code;
    // Nothing ATM
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------- Event Processing
// -------------------------------------------------------------------------------------


void
cConsoleWidget::ProcessBackspacePressed()
{
    std::string str = mInputText.getString();

    if( str.length() && mCursorIndex > 0 )
    {
        str.erase( mCursorIndex-1, 1 );
        mInputText.setString( str );
        DecrementCursorPosition();
    }
}


void
cConsoleWidget::ProcessTabPressed()
{
    // Append tab str text content to input content
    int nTabToWhiteSpace = DEFAULT_TAB_WHITESPACE;
    std::string tabStr = "";
    for( int i = 0; i < nTabToWhiteSpace; ++i )
    {
        tabStr += " ";
    }

    std::string inputStr = mInputText.getString();
    std::string resultStr = inputStr;
    resultStr.insert( mCursorIndex, tabStr );
    mInputText.setString( resultStr );
    MoveCursorPosition( int( tabStr.length() ) );
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
cConsoleWidget::ProcessHomePressed()
{
    ResetCursorPosition();
}


void
cConsoleWidget::ProcessEndPressed()
{
    MatchCursorPosition();
}


void
cConsoleWidget::ProcessDeletePressed()
{
    std::string str = mInputText.getString();

    if( str.length() && mCursorIndex < str.length() )
    {
        str.erase( mCursorIndex, 1 );
        mInputText.setString( str );
    }
}


void
cConsoleWidget::ProcessCTRLVPressed()
{
    // Append clipboard text content to input content
    std::string clipboardStr = GetClipboardText();
    std::string inputStr = mInputText.getString();
    std::string resultStr = inputStr + clipboardStr;
    mInputText.setString( resultStr );
    MoveCursorPosition( int( clipboardStr.length() ) );
}

void
cConsoleWidget::ProcessCTRLBackspacePressed()
{
    ClearInput();
}


void
cConsoleWidget::ProcessCTRLLeftPressed()
{
    std::string inputStr = mInputText.getString();
    int length = int( inputStr.length() );
    int delta = 0;
    bool firstCharOccurenceFound = false;

    for( int i = mCursorIndex; i >= 0; i-- )
    {
        int currentLookupIndex = i - 1;
        // Out of range safety
        if( currentLookupIndex < 0 )
            break;

        char currentChar = inputStr[ currentLookupIndex ]; // -1 because the last char of a string is a \0
        if( currentChar == char( 32 ) ) // char( 32 ) is a whitespace " "
        {
            if( firstCharOccurenceFound )
            {
                break;
            }

            delta--;
        }
        else
        {
            firstCharOccurenceFound = true;
            delta--;
        }
    }

    MoveCursorPosition( delta );
}


void
cConsoleWidget::ProcessCTRLRightPressed()
{
    std::string inputStr = mInputText.getString();
    int length = int( inputStr.length() );
    int delta = 0;
    bool firstWhitespaceOccurenceFound = false;

    for( int i = mCursorIndex; i < length; i++ )
    {
        int currentLookupIndex = i;
        // Out of range safety
        if( currentLookupIndex < 0 )
            break;

        char currentChar = inputStr[ currentLookupIndex ]; // -1 because the last char of a string is a \0
        if( currentChar == char( 32 ) ) // char( 32 ) is a whitespace " "
        {
            firstWhitespaceOccurenceFound = true;
            delta++;
        }
        else
        {
            if( firstWhitespaceOccurenceFound )
            {
                break;
            }
            else
            {
                delta++;
            }
        }
    }

    MoveCursorPosition( delta );
}


void
cConsoleWidget::ProcessShiftTabPressed()
{
    // Append tab str text content to input content
    int nTabToWhiteSpace = DEFAULT_TAB_WHITESPACE;
    std::string inputStr = mInputText.getString();
    int toErase = 0;

    for( int i = 0; i < nTabToWhiteSpace; ++i )
    {
        int currentLookupIndex = mCursorIndex - 1 - i;
        // Out of range safety
        if( currentLookupIndex < 0 )
            break;

        char currentChar = inputStr[ currentLookupIndex ]; // -1 because the last char of a string is a \0

        if( currentChar == char( 32 ) ) // char( 32 ) is a whitespace " "
        {
            toErase++;
        }
        else
        {
            break;
        }
    }

    std::string  resultStr = inputStr;
    resultStr.erase( mCursorIndex - toErase, toErase );
    mInputText.setString( resultStr );
    MoveCursorPosition( -toErase );
}


void 
cConsoleWidget::ProcessShiftLeftPressed()
{
    ProcessLeftPressed();
    UpdateSelectionGeometry();
}


void
cConsoleWidget::ProcessShiftRightPressed()
{
    ProcessRightPressed();
    UpdateSelectionGeometry();
}


} // namespace  nGUI