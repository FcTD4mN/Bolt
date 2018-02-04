#pragma once

#include <string>
#include "SFML/Graphics.hpp"
#include "Math/Rectangle.h"
#include "Base/Drawable.h"

class cMenuItem :
    public cDrawable
{
public:
    cMenuItem( const std::string& iText, const cRectangle& iBox );

public:
    // Access/Gets
    const sf::Text& Text() const;
    void Text( const std::string& iText );

    const cRectangle& Rectangle() const;
    void Rectangle( const cRectangle& iRectangle );

public:
    virtual  void ClickAction() = 0;

private:
    sf::Text mText;
    cRectangle mRectangle;
};

