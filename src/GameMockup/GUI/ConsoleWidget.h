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
    // Internal Text Geometry
    void    UpdateGeometryAndStyle( bool  iNoUpdate = false );

    int     NVisibleRows()  const;
    void    IncrementCursorPosition();
    void    DecrementCursorPosition();
    void    ResetCursorPosition();

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
    void  ProcessReturnPressed();
    void  ProcessEscapePressed();
    void  ProcessLeftPressed();
    void  ProcessRightPressed();

    void  ProcessCTRLVPressed();
    void  ProcessCTRLBackspacePressed();


private:
    // Data Members
    typedef void ( cConsoleWidget::*tVoidMemberFunctionPointer )();
    std::map< sf::Keyboard::Key, tVoidMemberFunctionPointer >  mKeyPressedProcessMap;
    std::map< sf::Keyboard::Key, tVoidMemberFunctionPointer >  mCTRLKeyPressedProcessMap;

    bool                mCollapsed;
    bool                mCursorToggled;
    unsigned  int       mCursorToggleTimeMs;
    unsigned  int       mCursorTimerElapsedTimeMs;
    unsigned  int       mCursorPosition;
    unsigned  int       mCharWidth;
    sf::RectangleShape  mConsoleRectangle;
    sf::RectangleShape  mCursorRectangle;
    sf::Vector2f        mSize;
    sf::Vector2f        mPosition;
    sf::Color           mBackgroundColor;

    sf::Font                 mFont;
    sf::Text                 mInputText;
    std::vector< sf::Text >  mOutputTextLines;
};


} // namespace  nGUI

