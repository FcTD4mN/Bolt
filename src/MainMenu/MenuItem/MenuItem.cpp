#include "MainMenu/MenuItem/MenuItem.h"

cMenuItem::cMenuItem( const std::string& iText, const cRectangle& iBox ) :
    mText(),
    mRectangle( iBox )
{
    mText.setString( iText );
    mText.setFont( sf::Font() );
}


// ===============================================Access/Gets
const sf::Text& 
cMenuItem::Text() const
{
    return  mText;
}


void 
cMenuItem::Text( const std::string& iText )
{
    mText.setString( iText );
}



const cRectangle& 
cMenuItem::Rectangle() const
{
    return  mRectangle;
}


void 
cMenuItem::Rectangle( const cRectangle& iRectangle )
{
    mRectangle = iRectangle;
}

