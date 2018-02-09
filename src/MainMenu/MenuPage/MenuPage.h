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
    void  SetFormat( eFormat iFormat );

public:
    virtual  void Draw() override;

protected:
    cMainMenu*                  mMasterMenu;
    std::vector< cMenuItem* >   mItems;
    eFormat                     mFormat;
};

