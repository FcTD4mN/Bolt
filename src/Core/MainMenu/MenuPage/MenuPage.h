#pragma once

#include "Base/Drawable.h"
#include "Base/GeneralEnums.h"

#include "SFML/Graphics.hpp"
#include <vector>

class cMainMenu;
class cMenuItem;

class cMenuPage :
    public cDrawable
{
public:
    cMenuPage( cMainMenu* iMasterMenu );
    void  Init();

public:
    void  AddItem( cMenuItem* iItem );

public:
    // Setup
    void  Format( eFormat iFormat );
    void  Spacing( float iSpacing );
    void  Rectangle( const sf::Rect< float >& iRectangle );
    void  Position( float iX, float iY );
    void  Size( float iW, float iH );

public:
    // Computing stuff
    void  ComputeItemPositions();

public:
    // Events
    void  MouseClick( int iX, int iY );

public:
    virtual  void Draw( sf::RenderTarget* iRenderTarget ) override;

protected:
    cMainMenu*                  mMasterMenu;
    std::vector< cMenuItem* >   mItems;
    eFormat                     mFormat;
    float                       mSpacing;
    sf::Rect< float >           mPageBounding;
};

