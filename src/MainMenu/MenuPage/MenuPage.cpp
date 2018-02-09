#include "MainMenu/MenuPage/MenuPage.h"


#include "Application/Application.h" 
#include "MainMenu/MenuItem/MenuItem.h"


cMenuPage::cMenuPage( cMainMenu* iMasterMenu ) : 
    mMasterMenu( iMasterMenu ),
    mFormat( kCenter ),
    mSpacing( 5 )
{ 
}


void 
cMenuPage::AddItem( cMenuItem* iItem )
{
    mItems.push_back( iItem );

    sf::Vector2u windowSize = cApplication::App()->Window()->getSize();

    float totalHeight = 0.0F; 
    for( int i = 0; i < mItems.size(); ++i )
    {
        totalHeight += mItems[ i ]->Rectangle().getSize().y + mSpacing; 
    }

    float y = windowSize.y / 2 - totalHeight/2;

    for( int i = 0; i < mItems.size(); ++i )
    { 
        sf::Vector2f itemSize = mItems[ i ]->Rectangle().getSize();
        mItems[ i ]->Position( sf::Vector2f(  windowSize.x / 2 - itemSize.x / 2, y ) ); 

        y += itemSize.y + mSpacing;
    }
}


void 
cMenuPage::MouseClick( float iX, float iY )
{
    for( int i = 0; i < mItems.size(); ++i )
    {
        if( mItems[ i ]->ContainsCoordinates( iX, iY ) )
        {
            mItems[ i ]->ClickAction();
            return;
        }
    }
}


void 
cMenuPage::Format( eFormat iFormat )
{
    mFormat = iFormat;
}


void 
cMenuPage::Spacing( float iSpacing )
{
    mSpacing = iSpacing;
}


void 
cMenuPage::Draw()
{
    for( int i = 0; i < mItems.size() ; ++i )
    {
        mItems[ i ]->Draw();
    }
}


