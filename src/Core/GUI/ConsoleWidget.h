#pragma once

#include "SFML/Graphics.hpp"
#include "BoltScript/BoltScriptEnvironment.h"

namespace  nGUI
{


class cConsoleWidget
{

private:
enum  eModifierState
{
    kNone           = 0,        // 0000 // 0
    kAlt            = 1 << 0,   // 0001 // 1
    kControl        = 1 << 1,   // 0010 // 2
    kShift          = 1 << 2,   // 0100 // 4
    kSystem         = 1 << 3,   // 1000 // 8

    kControlShift   = kControl | kShift,
    //...
};

public:
    // Construction/Destruction
    ~cConsoleWidget();
    cConsoleWidget();
    cConsoleWidget( const  cConsoleWidget& ) = delete; // Not Allowed

public:
    // Geometry and Style Getters / Setters
    void  SetSize( const  sf::Vector2f&  iSize, bool  iNoUpdate = false );
    void  SetPosition(  const  sf::Vector2f&  iPosition, bool  iNoUpdate = false );
    void  SetBackgroundColor(  const  sf::Color&  iColor, bool  iNoUpdate = false );

    const  sf::Vector2f&  GetSize()  const;
    const  sf::Vector2f&  SetPosition()  const;
    const  sf::Color&     SetBackgroundColor()  const;

    void  ToggleVisibility();

private:
    // Internal Logic Initialization
    void    BuildEventProcessMaps();
    void    BuildRegisteredFunctions();

private:
    // Internal Text Geometry & Manipulation
    void    UpdateGeometryAndStyle( bool  iNoUpdate = false );
    int     SelectionFirstIndex();
    int     SelectionLastIndex();
    void    UpdateSelectionGeometry();
    int     DeltaToNextWord();
    int     DeltaToPrevWord();
    void    StartSelection();
    void    BreakSelection();
    void    ClearSelection();
    std::string  SelectionString();
    std::string  TabulationString();

    int     NVisibleRows()  const;
    void    IncrementCursorPosition();
    void    DecrementCursorPosition();
    void    MoveCursorPosition( int iDelta );
    void    ResetCursorPosition();
    void    UpdateCursorPosition();
    void    MatchCursorPosition();
    void    MoveSelectionRange( int iDelta );
    void    ClearInput();
    void    PushPrintCache();

public:
    // Public Output Interface
    void    HookOutput();
    void    Clear();
    void    Print( const  std::string&  iStr );
    void    ProcessInput();

public:
    // Update/Draw
    void  Update( unsigned int iDeltaTime );
    void  Draw( sf::RenderTarget* iRenderTarget );

public:
    // MiniGame
    void  StartMiniGame();
    void  EndMiniGame();
    void  UpdateMiniGame( unsigned int iDeltaTime );

public:
    // Events
    void  TextEntered( const sf::Event& iEvent );
    void  KeyPressed( const sf::Event& iEvent );
    void  KeyReleased( const sf::Event& iEvent );

private:
    // Event Processing
    void  ProcessBackspacePressed();
    void  ProcessTabPressed();
    void  ProcessReturnPressed();
    void  ProcessEscapePressed();
    void  ProcessLeftPressed();
    void  ProcessRightPressed();
    void  ProcessHomePressed();
    void  ProcessEndPressed();
    void  ProcessDeletePressed();
    void  ProcessUpPressed();
    void  ProcessDownPressed();

    void  ProcessCTRLAPressed();
    void  ProcessCTRLCPressed();
    void  ProcessCTRLXPressed();
    void  ProcessCTRLVPressed();
    void  ProcessCTRLBackspacePressed();
    void  ProcessCTRLLeftPressed();
    void  ProcessCTRLRightPressed();

    void  ProcessShiftTabPressed();
    void  ProcessShiftLeftPressed();
    void  ProcessShiftRightPressed();
    void  ProcessShiftHomePressed();
    void  ProcessShiftEndPressed();

    void  ProcessCtrlShiftLeftPressed();
    void  ProcessCtrlShiftRightPressed();
    void  ProcessCtrlShiftHomePressed();
    void  ProcessCtrlShiftEndPressed();


private:
    // Data Members
    typedef void ( cConsoleWidget::*tVoidMemberFunctionPointer )();
    typedef std::map< sf::Keyboard::Key, tVoidMemberFunctionPointer >  tProcessMap;
    std::map< eModifierState, tProcessMap* >  mModifierMap;
    tProcessMap  mKeyPressedProcessMap;
    tProcessMap  mCTRLKeyPressedProcessMap;
    tProcessMap  mShiftKeyPressedProcessMap;
    tProcessMap  mCTRLShiftKeyPressedProcessMap;

    bool                mCollapsed;
    bool                mCursorToggled;
    unsigned  int       mCursorToggleTimeMs;
    unsigned  int       mCursorTimerElapsedTimeMs;
    int                 mCursorIndex;
    int                 mSelectionStartIndex;
    int                 mCharWidth;
    bool                mSelectionOccuring;
    sf::RectangleShape  mConsoleRectangle;
    sf::RectangleShape  mCursorRectangle;
    sf::RectangleShape  mSelectionBGRectangle;
    sf::RectangleShape  mSelectionFGRectangle;
    sf::Vector2f        mSize;
    sf::Vector2f        mPosition;
    sf::Color           mBackgroundColor;

    sf::Font                 mFont;
    sf::Text                 mInputText;
    std::vector< sf::Text >  mOutputTextLines;

    bool                mMiniGame;
    double              mMiniGameTimerElapsedTime;
    int                 mMiniGameShipCursorIndex;
    int                 mMiniGameHighscore;

    std::vector< std::string >  mPrintCache;
    int                         mPrintCacheIndex;
};


} // namespace  nGUI

