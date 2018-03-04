#include "MainMenu/MenuItem/MenuItem.h"


#include "Application/Application.h"

#include <SFML/Graphics.hpp>


#define ITEM_COLOR sf::Color( 255, 0, 0 )
#define ITEM_FONT "resources/Shared/Fonts/arial.ttf"
#define ITEM_CHARACTER_SIZE 24

cMenuItem::cMenuItem( cMainMenu* iMasterMenu, const std::string& iText, const sf::RectangleShape& iBox ) :
    mText(),
    mFont(),
    mRectangle( iBox ),
    mMasterMenu( iMasterMenu )
{
    Init( iText );
}

cMenuItem::cMenuItem( cMainMenu * iMasterMenu, const std::string & iText, float iX, float iY, float iW, float iH ) :
    mText(),
    mFont(),
    mRectangle( sf::RectangleShape( sf::Vector2f( iX, iY ) ) ),
    mMasterMenu( iMasterMenu )
{
    mRectangle.setSize( sf::Vector2f( iW, iH ) );
    Init( iText );
}

void
cMenuItem::Init( const std::string & iText )
{
    if( mFont.loadFromFile( ITEM_FONT ) )
    {
        mText.setString( iText );
        mText.setFont( mFont );
        mText.setCharacterSize( ITEM_CHARACTER_SIZE );
        mText.setFillColor( ITEM_COLOR );

        sf::Vector2f center( mRectangle.getPosition().x - mText.getGlobalBounds().width / 2 + mRectangle.getSize().x / 2,
                             mRectangle.getPosition().y - mText.getGlobalBounds().height / 2 + mRectangle.getSize().y / 2 );
        mText.setPosition( center );
    }
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


const sf::RectangleShape&
cMenuItem::Rectangle() const
{
    return  mRectangle;
}

void
cMenuItem::Position( const sf::Vector2f & iPosition )
{
    mRectangle.setPosition( iPosition );
    sf::Vector2f center( mRectangle.getPosition().x - mText.getGlobalBounds().width / 2 + mRectangle.getSize().x / 2,
                                                                     mRectangle.getPosition().y - mText.getGlobalBounds().height / 2 + mRectangle.getSize().y / 2 );
    mText.setPosition( center );
}


void
cMenuItem::Size( const sf::Vector2f & iSize )
{
    mRectangle.setSize( iSize );
}


void
cMenuItem::Size( float iW, float iH )
{
    mRectangle.setSize( sf::Vector2f( iW, iH ) );
}


void
cMenuItem::Draw( sf::RenderTarget* iRenderTarget )
{
    iRenderTarget->draw( mRectangle );
    iRenderTarget->draw( mText );
}


bool
cMenuItem::ContainsCoordinates( float iX, float iY ) const
{
    return  mRectangle.getGlobalBounds().contains( iX, iY );
}


