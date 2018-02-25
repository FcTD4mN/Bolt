#pragma once

#include "SFML/Graphics.hpp"

namespace  nGUI
{


class cConsoleWidget
{

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

private:
    // Internal Logic Initialization
    void    BuildEventProcessMaps();

private:
    // Internal Text Geometry
    void    UpdateGeometryAndStyle( bool  iNoUpdate = false );
    int     SelectionFirstIndex();
    int     SelectionLastIndex();
    void    UpdateSelectionGeometry();
    int     DeltaToNextWord();
    int     DeltaToPrevWord();
    void    BreakSelection();
    void    ClearSelection();

    int     NVisibleRows()  const;
    void    IncrementCursorPosition();
    void    DecrementCursorPosition();
    void    MoveCursorPosition( int iDelta );
    void    ResetCursorPosition();
    void    UpdateCursorPosition();
    void    MatchCursorPosition();
    void    MoveSelectionRange( int iDelta );

private:
    // Public Text Manipulation
    void    ClearInput();

public:
    // Update/Draw
    void  Update( unsigned int iDeltaTime );
    void  Draw( sf::RenderTarget* iRenderTarget );

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
    std::map< sf::Keyboard::Key, tVoidMemberFunctionPointer >  mKeyPressedProcessMap;
    std::map< sf::Keyboard::Key, tVoidMemberFunctionPointer >  mCTRLKeyPressedProcessMap;
    std::map< sf::Keyboard::Key, tVoidMemberFunctionPointer >  mShiftKeyPressedProcessMap;
    std::map< sf::Keyboard::Key, tVoidMemberFunctionPointer >  mCTRLShiftKeyPressedProcessMap;

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
};


} // namespace  nGUI

