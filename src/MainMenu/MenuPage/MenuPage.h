#pragma once

#include <vector> 
#include "Base/Drawable.h"

class cMainMenu;
class cMenuItem;

class cMenuPage :
    public cDrawable
{
public:
    cMenuPage( cMainMenu* iMasterMenu ); 

public:
    void AddItem( cMenuItem* iItem );

public:
    virtual  void Draw() override;

protected:
    cMainMenu* mMasterMenu;
    std::vector< cMenuItem* > mItems;
};

