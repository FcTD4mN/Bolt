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

private:
    void  UpdateGeometryAndStyle( bool  iNoUpdate = false );

private:
    void  Initialize();
    void  Finalize();

public:
    void  Update();
    void  Draw( sf::RenderTarget* iRenderTarget );

public:
    void  KeyPressed( const sf::Event& iEvent );
    void  KeyReleased( const sf::Event& iEvent );

private:
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

