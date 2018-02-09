#pragma once

#include <string>
#include "SFML/Graphics.hpp"
#include "Math/Rectangle.h"
#include "Base/Drawable.h"

class cMainMenu;

class cMenuItem :
    public cDrawable
{
public:
    cMenuItem( cMainMenu* iMasterMenu, const std::string& iText, const sf::RectangleShape& iBox );
    cMenuItem( cMainMenu* iMasterMenu, const std::string& iText, float iX, float iY, float iW, float iH );

    void Init( const std::string& iText );

public:
    // Access/Gets
    const sf::Text& Text() const;
    void Text( const std::string& iText ); 

    const sf::RectangleShape& Rectangle() const;
    void Position( const sf::Vector2f&  iPosition );

public:
    virtual  void ClickAction() = 0;
    virtual  void Draw() override;
    bool ContainsCoordinates( float iX, float iY ) const;

protected:
    sf::Text            mText;
    sf::Font            mFont; 
    sf::RectangleShape  mRectangle;
    cMainMenu*          mMasterMenu;
};

