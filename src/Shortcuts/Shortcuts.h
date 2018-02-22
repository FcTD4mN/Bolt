#pragma once

#include <unordered_map>
#include <SFML/Window.hpp>

class cShortcuts
{
public:
    // Construction/Destruction
    virtual  ~cShortcuts();
    cShortcuts();

public:
    // Init/Finalize
    void Initialize();
    void Finalize();

public:
    // Shortcut access
    sf::Keyboard::Key GetKeyForAction( const std::string& iAction );
    const std::string& GetActionForKey( sf::Keyboard::Key iKey );

public:
    std::unordered_map < sf::Keyboard::Key, std::string > mShortcuts;
};


