#pragma once

#include "SFML/Graphics.hpp"

namespace  nGUI
{


class cConsoleWidget
{

public:
    ~cConsoleWidget();
    cConsoleWidget();
    cConsoleWidget( const  cConsoleWidget& ) = delete; // Not Allowed

public:
    void  SetSize( const  sf::Vector2f&  iSize, bool  iNoUpdate = false );
    void  SetPosition(  const  sf::Vector2f&  iPosition, bool  iNoUpdate = false );
    void  SetBackgroundColor(  const  sf::Color&  iColor, bool  iNoUpdate = false );

    const  sf::Vector2f&  GetSize()  const;
    const  sf::Vector2f&  SetPosition()  const;
    const  sf::Color&     SetBackgroundColor()  const;

    int  NVisibleRows()  const;

private:
    void  UpdateGeometryAndStyle( bool  iNoUpdate = false );

public:
    void  Update();
    void  Draw( sf::RenderTarget* iRenderTarget );

public:
    void  TextEntered( const sf::Event& iEvent );
    void  KeyPressed( const sf::Event& iEvent );
    void  KeyReleased( const sf::Event& iEvent );

private:
    void  ProcessBackspacePressed();
    void  ProcessReturnPressed();
    void  ProcessEscapePressed();

private:
    typedef void ( cConsoleWidget::*tVoidMemberFunctionPointer )();
    std::map< sf::Keyboard::Key, tVoidMemberFunctionPointer >  mKeyProcessMap;

    bool                mCollapsed;
    sf::RectangleShape  mConsoleRectangle;
    sf::Vector2f        mSize;
    sf::Vector2f        mPosition;
    sf::Color           mBackgroundColor;

    sf::Font                 mFont;
    sf::Text                 mInputText;
    std::vector< sf::Text >  mOutputTextLines;
};


} // namespace  nGUI

