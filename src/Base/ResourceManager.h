#pragma once

#include <SFML/Graphics.hpp>

#include <unordered_map>

class cResourceManager
{
public:
    ~cResourceManager();
    cResourceManager();

public:
    static  cResourceManager* Instance();

public:
    sf::Texture* GetTexture( const std::string& iFileName );

private:
    std::unordered_map< std::string, sf::Texture* > mTextures;
};

