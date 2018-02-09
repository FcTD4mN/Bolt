#include "MainMenu/MenuPage/MenuPage.h"


#include "MainMenu/MenuItem/MenuItem.h"


cMenuPage::cMenuPage( cMainMenu* iMasterMenu ) : 
    mMasterMenu( iMasterMenu )
{ 
}


void 
cMenuPage::AddItem( cMenuItem* iItem )
{
    mItems.push_back( iItem );
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
cMenuPage::Draw()
{
    for( int i = 0; i < mItems.size() ; ++i )
    {
        mItems[ i ]->Draw();
    }
}


