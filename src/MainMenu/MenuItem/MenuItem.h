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
    cMenuItem( cMainMenu* iMasterMenu, const std::string& iText, const cRectangle& iBox );

public:
    // Access/Gets
    const sf::Text& Text() const;
    void Text( const std::string& iText );

    const cRectangle& Rectangle() const;
    void Rectangle( const cRectangle& iRectangle );

public:
    virtual  void ClickAction() = 0;

protected:
    sf::Text mText;
    cRectangle mRectangle;
    cMainMenu* mMasterMenu;
};

