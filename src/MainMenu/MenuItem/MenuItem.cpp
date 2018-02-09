#include "MainMenu/MenuItem/MenuItem.h"


#include "Application/Application.h" 

#include <SFML/Graphics.hpp>


#define ITEM_COLOR sf::Color( 255, 0, 0 )
#define ITEM_FONT "resources/Fonts/arial.ttf"
#define ITEM_CHARACTER_SIZE 24

cMenuItem::cMenuItem( cMainMenu* iMasterMenu, const std::string& iText, const sf::RectangleShape& iBox ) :
    mText(),
    mFont(), 
    mRectangle( iBox ),
    mMasterMenu( iMasterMenu )
{  
    if( mFont.loadFromFile( ITEM_FONT ) )
    {
        mText.setString( iText );
        mText.setFont( mFont );
        mText.setCharacterSize( ITEM_CHARACTER_SIZE );
        mText.setFillColor( ITEM_COLOR );
        mText.setPosition( iBox.getPosition() );
    }
    mRectangle.setSize( sf::Vector2f( mText.getGlobalBounds().width, mText.getGlobalBounds().height ) );
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


void 
cMenuItem::Draw()
{
    cApplication::App()->Window()->draw( mRectangle );
    cApplication::App()->Window()->draw( mText );
}


bool 
cMenuItem::ContainsCoordinates( float iX, float iY ) const
{
    return  mRectangle.getGlobalBounds().contains( iX, iY );
}


