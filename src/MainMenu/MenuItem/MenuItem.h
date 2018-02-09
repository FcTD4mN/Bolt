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

public:
    // Access/Gets
    const sf::Text& Text() const;
    void Text( const std::string& iText ); 

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

