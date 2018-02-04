#pragma once
   
#include "MainMenu/MenuItem/MenuItem.h"

class cItemPageSwaper :
    public cMenuItem
{
public:
    typedef cMenuItem tSuperClass;

public:
    cItemPageSwaper( const std::string& iText, const cRectangle& iBox, int iPage );

public:
    virtual  void ClickAction();
    virtual  void Draw() const; 

private:
    int mPageToSwapTo;
};

