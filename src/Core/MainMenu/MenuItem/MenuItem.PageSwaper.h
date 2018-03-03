#pragma once

#include "MainMenu/MenuItem/MenuItem.h"

class cItemPageSwaper :
    public cMenuItem
{
public:
    typedef  cMenuItem  tSuperClass;

public:
    cItemPageSwaper( cMainMenu* iMasterMenu, const std::string& iText, const sf::RectangleShape& iBox, int iPage );

public:
    virtual  void ClickAction() override;

private:
    int mPageToSwapTo;
};

