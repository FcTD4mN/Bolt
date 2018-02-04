#pragma once
 
#include "SFML/Graphics.hpp"

class cApplication
{
public:
    cApplication();

public:
    static cApplication* App();

public:
    sf::RenderWindow* Window();

public:
    void Initialize();
    void Finalize();

private:
    sf::RenderWindow* mMainWindow;
};

