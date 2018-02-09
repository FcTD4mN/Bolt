#pragma once

#include "Base/Drawable.h"
#include "Base/GeneralEnums.h"

#include <vector> 

class cMainMenu;
class cMenuItem;

class cMenuPage :
    public cDrawable
{
public:
    cMenuPage( cMainMenu* iMasterMenu ); 

public:
    void  AddItem( cMenuItem* iItem );
    void  MouseClick( float iX, float iY );
    void  Format( eFormat iFormat );
    void  Spacing( float iSpacing );

public:
    virtual  void Draw() override;

protected:
    cMainMenu*                  mMasterMenu;
    std::vector< cMenuItem* >   mItems;
    eFormat                     mFormat;
    float                       mSpacing;
};

