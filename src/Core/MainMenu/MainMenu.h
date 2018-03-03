#pragma once

#include <vector>
#include "Base/Drawable.h"

class cMenuPage;

class cMainMenu :
    public cDrawable
{
public:
    cMainMenu();

public:
    void  AddPage( cMenuPage* iPage );
    void  CurrentPage( int iPage );
    void  MouseClick( int iX, int iY );

public:
    virtual  void Draw( sf::RenderTarget* iRenderTarget ) override;

protected:
    std::vector< cMenuPage* > mPages;
    int mCurrentPage;
};

