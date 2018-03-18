#include "GUI/ConsoleWidget.h"


#include "Math/Utils.h"
#include "Base/Clipboard.h"

#define  CHECK_COLLAPSED if( mCollapsed ) return;


namespace  nGUI
{

// -------------------------------------------------------------------------------------
// ---------------------------------------------------------------------- Default Values
// -------------------------------------------------------------------------------------


#define DEFAULT_SIZE                        sf::Vector2f( 600.f, 200.f )
#define DEFAULT_COLOR                       sf::Color( 220, 220, 220, 255 )
#define DEFAULT_FONT                        "resources/Shared/Fonts/SourceCodePro-Regular.ttf"
#define DEFAULT_FONT_SIZE                   12
#define DEFAULT_LINE_HEIGHT                 14
#define DEFAULT_FONT_COLOR                  sf::Color( 20, 20, 20, 255 )
#define DEFAULT_CURSOR_COLOR                DEFAULT_FONT_COLOR
#define DEFAULT_CURSOR_SIZE                 sf::Vector2f( 2.f, float( DEFAULT_LINE_HEIGHT ) )
#define DEFAULT_CURSOR_TOGGLE_TIME_MS       200
#define DEFAULT_TAB_WHITESPACE              4
#define DEFAULT_SELECTION_BG_COLOR          sf::Color( 255, 255, 0, 255 )
#define DEFAULT_SELECTION_FG_COLOR          sf::Color( 255, 255, 0, 85 )
#define DEFAULT_PRINT_CACHE_SIZE            10


#define KEY_EXISTS( iMap, iKey )            ( ! ( iMap.find( iKey ) == iMap.end() ) )

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cConsoleWidget::~cConsoleWidget()
{
}


cConsoleWidget::cConsoleWidget() :
    mModifierMap(),
    mKeyPressedProcessMap(),
    mCTRLKeyPressedProcessMap(),
    mShiftKeyPressedProcessMap(),
    mCTRLShiftKeyPressedProcessMap(),
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
    mOutputTextLines(),
    mMiniGame( false ),
    mMiniGameTimerElapsedTime( 0.0 ),
    mMiniGameShipCursorIndex( 0 ),
    mMiniGameHighscore( 0 ),
    mPrintCache(),
    mPrintCacheIndex( 0 )
{
    BuildEventProcessMaps();
    BuildRegisteredFunctions();

    mCursorRectangle.setSize(       DEFAULT_CURSOR_SIZE );
    mCursorRectangle.setFillColor(  DEFAULT_CURSOR_COLOR );

    mSelectionBGRectangle.setFillColor(  DEFAULT_SELECTION_BG_COLOR );
    mSelectionFGRectangle.setFillColor(  DEFAULT_SELECTION_FG_COLOR );

    mFont.loadFromFile( DEFAULT_FONT );
    mInputText.setFont( mFont );
    mInputText.setCharacterSize( DEFAULT_FONT_SIZE );
    mInputText.setFillColor( DEFAULT_FONT_COLOR );

    // The next three functions have the optional NoUpdate Boolean parameter set to true,
    // in order the to avoid calling UpdateGeometryAndStyle too often.
    SetSize(            DEFAULT_SIZE        , true );
    SetPosition(        sf::Vector2f()      , true );
    SetBackgroundColor( DEFAULT_COLOR       , true );
    UpdateGeometryAndStyle();

    ::nBoltScript::Env()->ProcessRawString( "output:SFML" );

    mPrintCache.resize( DEFAULT_PRINT_CACHE_SIZE );
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


void
cConsoleWidget::ToggleVisibility()
{
    mCollapsed = !mCollapsed;
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------- Internal Logic Initialization
// -------------------------------------------------------------------------------------


void
cConsoleWidget::BuildEventProcessMaps()
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
    mKeyPressedProcessMap[ sf::Keyboard::Up ]               =  &cConsoleWidget::ProcessUpPressed;
    mKeyPressedProcessMap[ sf::Keyboard::Down ]             =  &cConsoleWidget::ProcessDownPressed;

    // CTRL + Key Press
    mCTRLKeyPressedProcessMap[ sf::Keyboard::A ]            =  &cConsoleWidget::ProcessCTRLAPressed;
    mCTRLKeyPressedProcessMap[ sf::Keyboard::C ]            =  &cConsoleWidget::ProcessCTRLCPressed;
    mCTRLKeyPressedProcessMap[ sf::Keyboard::X ]            =  &cConsoleWidget::ProcessCTRLXPressed;
    mCTRLKeyPressedProcessMap[ sf::Keyboard::V ]            =  &cConsoleWidget::ProcessCTRLVPressed;
    mCTRLKeyPressedProcessMap[ sf::Keyboard::BackSpace ]    =  &cConsoleWidget::ProcessCTRLBackspacePressed;
    mCTRLKeyPressedProcessMap[ sf::Keyboard::Left ]         =  &cConsoleWidget::ProcessCTRLLeftPressed;
    mCTRLKeyPressedProcessMap[ sf::Keyboard::Right ]        =  &cConsoleWidget::ProcessCTRLRightPressed;

    // Shift + Key Press
    mShiftKeyPressedProcessMap[ sf::Keyboard::Tab ]         =  &cConsoleWidget::ProcessShiftTabPressed;
    mShiftKeyPressedProcessMap[ sf::Keyboard::Left ]        =  &cConsoleWidget::ProcessShiftLeftPressed;
    mShiftKeyPressedProcessMap[ sf::Keyboard::Right ]       =  &cConsoleWidget::ProcessShiftRightPressed;
    mShiftKeyPressedProcessMap[ sf::Keyboard::Home ]        =  &cConsoleWidget::ProcessShiftHomePressed;
    mShiftKeyPressedProcessMap[ sf::Keyboard::End ]         =  &cConsoleWidget::ProcessShiftEndPressed;

    // CTRL + Shift + Key Press
    mCTRLShiftKeyPressedProcessMap[ sf::Keyboard::Left ]    =  &cConsoleWidget::ProcessCtrlShiftLeftPressed;
    mCTRLShiftKeyPressedProcessMap[ sf::Keyboard::Right ]   =  &cConsoleWidget::ProcessCtrlShiftRightPressed;
    mCTRLShiftKeyPressedProcessMap[ sf::Keyboard::Home ]    =  &cConsoleWidget::ProcessCtrlShiftHomePressed;
    mCTRLShiftKeyPressedProcessMap[ sf::Keyboard::End ]     =  &cConsoleWidget::ProcessCtrlShiftEndPressed;

    mModifierMap[ eModifierState::kNone ]           = &mKeyPressedProcessMap;
    mModifierMap[ eModifierState::kControl]         = &mCTRLKeyPressedProcessMap;
    mModifierMap[ eModifierState::kShift ]          = &mShiftKeyPressedProcessMap;
    mModifierMap[ eModifierState::kControlShift]    = &mCTRLShiftKeyPressedProcessMap;
}


void
cConsoleWidget::BuildRegisteredFunctions()
{
    ::nBoltScript::Env()->RegisterFunction( "output:SFML",  [=](void) { HookOutput(); } );
    ::nBoltScript::Env()->RegisterFunction( "cls",          [=](void) { Clear(); } );
    ::nBoltScript::Env()->RegisterFunction( "help",         [=](void) { Print( "Not Available" ); } );
    ::nBoltScript::Env()->RegisterFunction( "minigame",     [=](void) { StartMiniGame(); } );
}

// -------------------------------------------------------------------------------------
// ----------------------------------------------- Internal Text Geometry & Manipulation
// -------------------------------------------------------------------------------------


void
cConsoleWidget::UpdateGeometryAndStyle( bool  iNoUpdate )
{
    if( iNoUpdate )
        return;

    {
        // Computing Char width using functions provided by SFML
        sf::Text  sampleText;
        sampleText.setFont( mFont );
        sampleText.setCharacterSize( DEFAULT_FONT_SIZE );
        sampleText.setString( ">>" );
        sf::Vector2f pos = sampleText.findCharacterPos( 1 );
        mCharWidth = int( pos.x );
    }

    // Setting atual console rectangle geometry.
    mConsoleRectangle.setSize(      mSize );
    mConsoleRectangle.setPosition(  mPosition );
    mConsoleRectangle.setFillColor( mBackgroundColor );

    int  nOutputTextLines = NVisibleRows() -1; // -1 because 1 line is reserved for input text.
    int oldSize = int( mOutputTextLines.size() );
    std::vector< std::string > linesBackup( oldSize );
    for( int i = 0; i < oldSize; ++i )
    {
        linesBackup.push_back( mOutputTextLines[i].getString() );
    }

    mOutputTextLines.clear();
    mOutputTextLines.reserve( nOutputTextLines+1 );
    mOutputTextLines.resize( nOutputTextLines );

    for( int i = 0; i < nOutputTextLines; ++i )
    {
        mOutputTextLines[i].setFont( mFont );
        mOutputTextLines[i].setCharacterSize( DEFAULT_FONT_SIZE );
        mOutputTextLines[i].setFillColor( DEFAULT_FONT_COLOR );
        float x = 0;
        float y = float( i * DEFAULT_LINE_HEIGHT );
        sf::Vector2f  outputLinePosition = sf::Vector2f( x, y );
        mOutputTextLines[i].setPosition( mPosition + outputLinePosition );
    }

    int currentBackupIndex = nOutputTextLines-1;
    while( linesBackup.size() )
    {
        if( currentBackupIndex < 0 )
            break;

        mOutputTextLines[currentBackupIndex].setString( linesBackup.back() );
        linesBackup.pop_back();
        --currentBackupIndex;
    }

    float x = 0;
    float y = float( nOutputTextLines * DEFAULT_LINE_HEIGHT );
    sf::Vector2f  inputLinePosition = sf::Vector2f( x, y );
    mInputText.setPosition( mPosition + inputLinePosition );

    float cursorX = 0;
    float cursorY = y;
    sf::Vector2f  cursorPosition = sf::Vector2f( cursorX, cursorY );

    mCursorRectangle.setPosition( mPosition + cursorPosition );
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
cConsoleWidget::DeltaToNextWord()
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

    return  delta;
}


int
cConsoleWidget::DeltaToPrevWord()
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

    return  delta;
}


void
cConsoleWidget::StartSelection()
{
    mSelectionStartIndex = mCursorIndex;
    mSelectionOccuring = true;
}


void
cConsoleWidget::BreakSelection()
{
    mSelectionOccuring = false;
}


void
cConsoleWidget::ClearSelection()
{
    std::string str = mInputText.getString();

    int selectionFirstIndex = SelectionFirstIndex();
    int selectionLastIndex = SelectionLastIndex();
    int delta = selectionLastIndex - selectionFirstIndex;
    str.erase( selectionFirstIndex, delta );
    mInputText.setString( str );
    mCursorIndex = selectionFirstIndex;
    UpdateCursorPosition();
    BreakSelection();
}


std::string
cConsoleWidget::SelectionString()
{
    std::string  inputString = mInputText.getString();
    int selectionFirstIndex = SelectionFirstIndex();
    int selectionLastIndex = SelectionLastIndex();
    int delta = selectionLastIndex - selectionFirstIndex;
    std::string  str = inputString.substr( selectionFirstIndex, delta );
    return  str;
}


std::string
cConsoleWidget::TabulationString()
{
    // Build str text ( N whitespaces )
    int nTabToWhiteSpace = DEFAULT_TAB_WHITESPACE;
    std::string tabStr = "";
    for( int i = 0; i < nTabToWhiteSpace; ++i )
    {
        tabStr += " ";
    }

    return  tabStr;
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
    mCursorIndex += iDelta;
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


void
cConsoleWidget::MoveSelectionRange( int iDelta )
{
    MoveCursorPosition( iDelta );
    mSelectionStartIndex += iDelta;
    UpdateSelectionGeometry();
}


void
cConsoleWidget::ClearInput()
{
    // Clear input content
    mInputText.setString("");
    ResetCursorPosition();
    BreakSelection();
}


void
cConsoleWidget::PushPrintCache()
{
    for( int i = int( mPrintCache.size() )-1; i > 0; --i )
    {
        mPrintCache[ i ] = mPrintCache[ i-1 ];
    }
    mPrintCache[0] = mInputText.getString();
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------- Public Output Interface
// -------------------------------------------------------------------------------------


void
cConsoleWidget::HookOutput()
{
    std::function< void( const  std::string& )> f = [=]( const  std::string& iStr ) {
        this->Print( iStr );
    };

    ::nBoltScript::Env()->Print( ">>: Output switching to SFML Console \r\n");
    ::nBoltScript::Env()->SetOutputRedirectionFunction( f );
    ::nBoltScript::Env()->Print( ">>: Output switched to SFML Console \r\n");
}


void
cConsoleWidget::Clear()
{
    for( int i = 0; i < NVisibleRows() -1; ++i )
    {
        mOutputTextLines[ i ].setString( "" );
    }
    ClearInput();
}


void
cConsoleWidget::Print( const  std::string&  iStr )
{
    // Shift output rows content upwards
    for( int i = 0; i < NVisibleRows() -2; ++i )
    {
        std::string currentOutputStr = mOutputTextLines[i + 1 ].getString();
        mOutputTextLines[i].setString( currentOutputStr );
    }

    mOutputTextLines.back().setString( iStr );
}


void
cConsoleWidget::ProcessInput()
{
    ::nBoltScript::Env()->ProcessRawString( mInputText.getString() );
}

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------- Update/Draw
// -------------------------------------------------------------------------------------


void
cConsoleWidget::Update( unsigned int iDeltaTime )
{
    CHECK_COLLAPSED
    mCursorTimerElapsedTimeMs += iDeltaTime;
    if( mCursorTimerElapsedTimeMs > mCursorToggleTimeMs )
    {
        mCursorTimerElapsedTimeMs = 0;
        mCursorToggled = !mCursorToggled;
    }

    UpdateMiniGame( iDeltaTime );
}


void
cConsoleWidget::Draw( sf::RenderTarget* iRenderTarget )
{
    CHECK_COLLAPSED
    iRenderTarget->draw( mConsoleRectangle );
    int  nOutputTextLines = NVisibleRows() -1; // -1 because 1 line is reserved for input text.
    for( int i = 0; i < nOutputTextLines; ++i )
    {
        iRenderTarget->draw( mOutputTextLines[i] );
    }

    if( mSelectionOccuring )
        iRenderTarget->draw( mSelectionBGRectangle );

    iRenderTarget->draw( mInputText );

    if( mCursorToggled )
        iRenderTarget->draw( mCursorRectangle );

    if( mSelectionOccuring )
        iRenderTarget->draw( mSelectionFGRectangle );
}

// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------- MiniGame
// -------------------------------------------------------------------------------------


void
cConsoleWidget::StartMiniGame()
{
    Clear();
    mMiniGame = true;
    mMiniGameTimerElapsedTime = 0;
    int nChars = int( mSize.x ) / mCharWidth;
    int center = nChars/2;
    mMiniGameShipCursorIndex = center;
    mMiniGameHighscore = 0;

    for( int i = 0; i < NVisibleRows() -1; ++i )
    {
        std::string str = mOutputTextLines[ i ].getString();

        for( int j = 0; j < nChars; ++j )
        {
            str.push_back( ' ' );
        }
        mOutputTextLines[ i ].setString( str );
    }

    ClearInput();
}


void
cConsoleWidget::EndMiniGame()
{
    mMiniGame = false;
}


void
cConsoleWidget::UpdateMiniGame( unsigned int iDeltaTime )
{
    if( mMiniGame )
    {
        ++mMiniGameHighscore;

        double incrementSpeed = 1.2;
        double incrementalPeriod = double( 400 - mMiniGameTimerElapsedTime * incrementSpeed );
        double minPeriod = 120.0;
        double period = incrementalPeriod >= minPeriod ? incrementalPeriod : minPeriod;
        mMiniGameTimerElapsedTime += double( iDeltaTime ) / period;
        int nChars = int( mSize.x ) / mCharWidth;
        std::string str;
        for( int i = 0; i < nChars; ++i )
        {
            str.push_back( ' ' );
        }

        int center = nChars/2;
        int amplitudeMin = 5;
        int amplitude = center - amplitudeMin;
        int index = int( ( sin( mMiniGameTimerElapsedTime ) / 2.0 + 0.5 ) * amplitude ) +1;
        int realIndex = center - index;
        for( int i=0; i < realIndex; ++i )
            str[i] = '*';

        for( int i=realIndex + amplitude; i < nChars; ++i )
            str[i] = '*';

        // Shift output rows content downwards
        for( int i = NVisibleRows()-2; i > 0; --i )
        {
            std::string currentOutputStr = mOutputTextLines[ i-1 ].getString();
            mOutputTextLines[i].setString( currentOutputStr );
        }

        if( mOutputTextLines.back().getString()[ mMiniGameShipCursorIndex ] == '*' )
        {
            EndMiniGame();
            Print( "LOSER !" );
            Print( "Score: " + std::to_string( mMiniGameHighscore) + " meters" );
            return;
        }


        mOutputTextLines[0].setString( str );

        char ship = 'A';
        std::string shipStr = mOutputTextLines.back().getString();
        shipStr[ mMiniGameShipCursorIndex ] = ship;
        mOutputTextLines.back().setString( shipStr );
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cConsoleWidget::TextEntered( const sf::Event& iEvent )
{
    CHECK_COLLAPSED
    // Handle ASCII characters only
    auto  unicode = iEvent.text.unicode;
    bool  unicodeInput = unicode > 0X0020 && unicode < 0X007E || unicode == 32;

    if( !unicodeInput )
        return;

    if( mSelectionOccuring )
        ClearSelection();

    std::string str = mInputText.getString();
    char charCode = static_cast<char>( unicode );
    std::string charStr;
    charStr.push_back( charCode );
    str.insert( mCursorIndex, charStr );
    mInputText.setString( str );
    IncrementCursorPosition();

    BreakSelection();
}


void
cConsoleWidget::KeyPressed( const sf::Event& iEvent )
{
    auto key = iEvent.key;
    auto code = key.code;

    eModifierState modifierState = eModifierState::kNone;
    modifierState = static_cast< eModifierState >(  ( int( key.alt )        << 0 ) |
                                                    ( int( key.control)     << 1 ) |
                                                    ( int( key.shift )      << 2 ) |
                                                    ( int( key.system )     << 3 ) );

    if( code == sf::Keyboard::Tab && modifierState == kControl )
    {
        ToggleVisibility();
    }

    CHECK_COLLAPSED


    if( ( code == sf::Keyboard::LShift || code == sf::Keyboard::RShift ) && !mSelectionOccuring )
    {
        StartSelection();
        UpdateSelectionGeometry();
    }

    if( KEY_EXISTS( mModifierMap, modifierState ) )
    {
        if( KEY_EXISTS( ( *mModifierMap[ modifierState ] ), code ) )
        {
            (this->*( *mModifierMap[ modifierState ] )[ code ])();
        }
    }

    if( code == sf::Keyboard::Left )
    {
        mMiniGameShipCursorIndex = mMiniGameShipCursorIndex > 0 ? mMiniGameShipCursorIndex-1 : 0;
    }

    if( code == sf::Keyboard::Right )
    {
        std::string str = mOutputTextLines.back().getString();
        int length = int( str.length() ) - 1;
        mMiniGameShipCursorIndex = mMiniGameShipCursorIndex < length ? mMiniGameShipCursorIndex+1 : length;
    }
}


void
cConsoleWidget::KeyReleased( const sf::Event& iEvent )
{
    CHECK_COLLAPSED
    // Nothing ATM
}


// -------------------------------------------------------------------------------------
// -------------------------------------------------------------------- Event Processing
// -------------------------------------------------------------------------------------


void
cConsoleWidget::ProcessBackspacePressed()
{
    if( mSelectionOccuring )
    {
        ClearSelection();
    }
    else
    {
        std::string str = mInputText.getString();

        if( str.length() && mCursorIndex > 0 )
        {
            str.erase( mCursorIndex-1, 1 );
            mInputText.setString( str );
            DecrementCursorPosition();
        }

        BreakSelection();
    }
}


void
cConsoleWidget::ProcessTabPressed()
{
    if( mSelectionOccuring )
        ClearSelection();

    // Inset tab str text ( N whitespaces ) content to input content
    std::string tabStr = TabulationString();

    std::string str = mInputText.getString();
    str.insert( mCursorIndex, tabStr );
    mInputText.setString( str );
    MoveCursorPosition( int( tabStr.length() ) );
    BreakSelection();
}


void
cConsoleWidget::ProcessReturnPressed()
{
    EndMiniGame();
    PushPrintCache();
    ProcessInput();
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
    BreakSelection();
}
void
cConsoleWidget::ProcessRightPressed()
{
    IncrementCursorPosition();
    BreakSelection();
}


void
cConsoleWidget::ProcessHomePressed()
{
    ResetCursorPosition();
    BreakSelection();
}


void
cConsoleWidget::ProcessEndPressed()
{
    MatchCursorPosition();
    BreakSelection();
}


void
cConsoleWidget::ProcessDeletePressed()
{
    if( mSelectionOccuring )
    {
        ClearSelection();
    }
    else
    {
        std::string str = mInputText.getString();
        if( str.length() && mCursorIndex < str.length() )
        {
            str.erase( mCursorIndex, 1 );
            mInputText.setString( str );
        }

        BreakSelection();
    }
}


void
cConsoleWidget::ProcessUpPressed()
{
    std::string cacheStr = mPrintCache[ mPrintCacheIndex ];
    mInputText.setString( cacheStr );
    int max = int( cacheStr.size() )-1;
    mPrintCacheIndex += mPrintCacheIndex < max ? 1 : 0;
    MatchCursorPosition();
}


void
cConsoleWidget::ProcessDownPressed()
{
    std::string cacheStr = mPrintCache[ mPrintCacheIndex ];
    mInputText.setString( cacheStr );
    mPrintCacheIndex -= 0 > 0 ? 1 : 0;
    MatchCursorPosition();
}


void
cConsoleWidget::ProcessCTRLAPressed()
{
    ResetCursorPosition();
    StartSelection();
    MatchCursorPosition();
    UpdateSelectionGeometry();
}


void
cConsoleWidget::ProcessCTRLCPressed()
{
    if( !mSelectionOccuring )
        return;

    std::string  str = SelectionString();
    SetClipboardText( str );
}


void
cConsoleWidget::ProcessCTRLXPressed()
{
    if( !mSelectionOccuring )
        return;

    ProcessCTRLCPressed();
    ClearSelection();
}


void
cConsoleWidget::ProcessCTRLVPressed()
{
    if( mSelectionOccuring )
        ClearSelection();

    // Append clipboard text content to input content
    std::string clipboardStr = GetClipboardText();
    int end = int( clipboardStr.find( char( '\r\n' ) ) );
    clipboardStr = clipboardStr.substr( 0, end );

    std::string inputStr = mInputText.getString();
    std::string resultStr = inputStr;
    resultStr.insert( mCursorIndex, clipboardStr );
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
    MoveCursorPosition( DeltaToPrevWord() );
    BreakSelection();
}


void
cConsoleWidget::ProcessCTRLRightPressed()
{
    MoveCursorPosition( DeltaToNextWord() );
    BreakSelection();
}


void
cConsoleWidget::ProcessShiftTabPressed()
{
    if( mSelectionOccuring )
        ClearSelection();

    // Append tab str text content to input content
    int nTabToWhiteSpace = DEFAULT_TAB_WHITESPACE;
    std::string inputStr = mInputText.getString();
    int toErase =   0;

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
    BreakSelection();
}


void
cConsoleWidget::ProcessShiftLeftPressed()
{
    DecrementCursorPosition();
    UpdateSelectionGeometry();
}


void
cConsoleWidget::ProcessShiftRightPressed()
{
    IncrementCursorPosition();
    UpdateSelectionGeometry();
}


void
cConsoleWidget::ProcessShiftHomePressed()
{
    ResetCursorPosition();
    UpdateSelectionGeometry();
}


void
cConsoleWidget::ProcessShiftEndPressed()
{
    MatchCursorPosition();
    UpdateSelectionGeometry();
}


void
cConsoleWidget::ProcessCtrlShiftLeftPressed()
{
    MoveCursorPosition( DeltaToPrevWord() );
    UpdateSelectionGeometry();
}


void
cConsoleWidget::ProcessCtrlShiftRightPressed()
{
    MoveCursorPosition( DeltaToNextWord() );
    UpdateSelectionGeometry();
}


void
cConsoleWidget::ProcessCtrlShiftHomePressed()
{
    ResetCursorPosition();
    UpdateSelectionGeometry();
}


void
cConsoleWidget::ProcessCtrlShiftEndPressed()
{
    MatchCursorPosition();
    UpdateSelectionGeometry();
}

} // namespace  nGUI