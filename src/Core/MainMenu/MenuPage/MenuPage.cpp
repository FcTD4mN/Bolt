#include "MainMenu/MenuPage/MenuPage.h"


#include "MainMenu/MenuItem/MenuItem.h"


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cMenuPage::cMenuPage( cMainMenu* iMasterMenu ) :
    mMasterMenu( iMasterMenu ),
    mFormat( kCenter ),
    mSpacing( 5 ),
    mPageBounding()
{
    Init();
}


void
cMenuPage::Init()
{
    mPageBounding.left = 0;
    mPageBounding.top = 0;
    mPageBounding.width = 10;
    mPageBounding.height = 10;
}


// -------------------------------------------------------------------------------------
// --------------------------------------------------------------------- Item management
// -------------------------------------------------------------------------------------


void
cMenuPage::AddItem( cMenuItem* iItem )
{
    mItems.push_back( iItem );

    ComputeItemPositions();
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------- Setup
// -------------------------------------------------------------------------------------


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
cMenuPage::Rectangle( const sf::Rect< float >& iRectangle )
{
    mPageBounding = iRectangle;
}


void
cMenuPage::Position( float iX, float iY )
{
    mPageBounding.left = iX;
    mPageBounding.top = iY;
    ComputeItemPositions();
}


void
cMenuPage::Size( float iW, float iH )
{
    mPageBounding.width  = iW;
    mPageBounding.height = iH;
    ComputeItemPositions();
}


// -------------------------------------------------------------------------------------
// --------------------------------------------------------------------- Computing stuff
// -------------------------------------------------------------------------------------


void
cMenuPage::ComputeItemPositions()
{
    float totalHeight = 0.0F;
    for( int i = 0; i < mItems.size(); ++i )
    {
        totalHeight += mItems[ i ]->Rectangle().getSize().y + mSpacing;
    }

    float y = mPageBounding.top + mPageBounding.height / 2 - totalHeight / 2;

    for( int i = 0; i < mItems.size(); ++i )
    {
        cMenuItem* item = mItems[ i ];
        sf::Vector2f itemSize = item->Rectangle().getSize();

        if( itemSize.x > mPageBounding.width - mSpacing )
            item->Size( mPageBounding.width - mSpacing, itemSize.y );

        item->Position( sf::Vector2f( mPageBounding.left + mPageBounding.width / 2 - item->Rectangle().getSize().x / 2, y ) );


        y += itemSize.y + mSpacing;
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------- Drawable override
// -------------------------------------------------------------------------------------


void
cMenuPage::Draw( sf::RenderTarget* iRenderTarget )
{
    for( int i = 0; i < mItems.size() ; ++i )
    {
        mItems[ i ]->Draw( iRenderTarget );
    }
}


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ Events
// -------------------------------------------------------------------------------------


void
cMenuPage::MouseClick( int iX, int iY )
{
    for( int i = 0; i < mItems.size(); ++i )
    {
        if( mItems[ i ]->ContainsCoordinates( float( iX ), float( iY ) ) )
        {
            mItems[ i ]->ClickAction();
            return;
        }
    }
}


