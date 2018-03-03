#pragma once

#include <SFML/Graphics.hpp>

class cDrawable
{
public:
    cDrawable();

public:
    virtual  void Draw( sf::RenderTarget* iRenderTarget ) = 0;
};

