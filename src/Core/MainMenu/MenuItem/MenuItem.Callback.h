#pragma once

#include "MainMenu/MenuItem/MenuItem.h"

#include <functional>

class cMainMenu;

class cItemCallback :
    public cMenuItem
{
public:
    typedef  cMenuItem  tSuperClass;

public:
    cItemCallback( cMainMenu* iMasterMenu, const std::string& iText, const sf::RectangleShape& iBox, std::function< void() > iFunction );

public:
    virtual  void ClickAction() override;

private:
	std::function< void() > mFunction;
};

