#pragma once

#include "MainMenu/MenuItem/MenuItem.h"

class cMainMenu;

class cItemCallback :
    public cMenuItem
{
public:
    typedef  cMenuItem  tSuperClass;

public:
    cItemCallback( cMainMenu* iMasterMenu, const std::string& iText, const sf::RectangleShape& iBox, void (*iFunction)( cMainMenu* iMenu ) );

public:
    virtual  void ClickAction() override;

private:
    void (*mFunction)( cMainMenu* iMenu );
};

