#pragma once


#include <SFML/Graphics.hpp>


#include <unordered_map>

#include "Core.Base.FileSystem.h"

namespace nCore {
namespace nBase {


// This structure allows to store a texture with a counter for how many time this texture was asked
// When hash map reaches a size too large, we will then be able to remove the least used texture from cache
namespace
{
    struct stTexture
    {
        stTexture() : mTexture( 0 ), mCounter( 0 ){ }
        sf::Texture*    mTexture;
        int             mCounter;
    };
}

class cResourceManager
{
public:
    ~cResourceManager();
    cResourceManager();

public:
    static  cResourceManager* Instance();

public:
    sf::Texture*    GetTexture( const std::string& iFileName );
    sf::Texture*    GetTexture( const nStdFileSystem::path& iFileName );
    void            InvalidateTexture( const nStdFileSystem::path& iFileName );

private:
    std::unordered_map< std::string, stTexture > mTextures;
};


} // namespace nBase
} // namespace nCore

