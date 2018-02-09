#pragma once
   
#include "MainMenu/MenuItem/MenuItem.h"

class cItemCallback :
    public cMenuItem
{
public:
    typedef  cMenuItem  tSuperClass;

public:
    cItemCallback( cMainMenu* iMasterMenu, const std::string& iText, const sf::RectangleShape& iBox, void (*iFunction)() );

public:
    virtual  void ClickAction() override; 

private:
    void (*mFunction)();
};

