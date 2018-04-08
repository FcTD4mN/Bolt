#pragma once


#include <SFML/Graphics.hpp>


namespace nBase {


class cDrawable
{
public:
    cDrawable();

public:
    virtual  void Draw( sf::RenderTarget* iRenderTarget ) = 0;

};


} //nBase

