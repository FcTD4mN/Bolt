#include "MainMenu/MenuItem/MenuItem.h"

#define ITEM_COLOR sf::Color( 255, 0, 0 )
#define ITEM_FONT "resources/Fonts/arial.ttf"
#define ITEM_CHARACTER_SIZE 24

cMenuItem::cMenuItem( cMainMenu* iMasterMenu, const std::string& iText, const cRectangle& iBox ) :
    mRectangle( iBox ),
    mMasterMenu( iMasterMenu )
{
    //sf::Font font;
    //font.loadFromFile( ITEM_FONT );

    //mText.setString( iText );
    //mText.setFont( font );
    //mText.setCharacterSize( ITEM_CHARACTER_SIZE );
    //mText.setFillColor( ITEM_COLOR ); 
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

