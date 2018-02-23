#include "Base/Drawable.h"
#include "ResourceManager.h"

#include <iostream>

cResourceManager::~cResourceManager()
{
    for( auto it = mTextures.begin(); it != mTextures.end(); ++it )
    {
        delete  it->second.mTexture;
    }
}


cResourceManager::cResourceManager()
{
}


cResourceManager*
cResourceManager::Instance()
{
    static cResourceManager* gResourceManager;

    if( !gResourceManager )
        gResourceManager = new cResourceManager();

    return  gResourceManager;
}


sf::Texture*
cResourceManager::GetTexture( const std::string& iFileName )
{
    auto finder = mTextures.find( iFileName );

    stTexture& result = mTextures[ iFileName ];

    if( !result.mTexture )
    {
        result.mTexture = new sf::Texture();
        result.mTexture->loadFromFile( iFileName );
    }

    ++(result.mCounter);
    return  result.mTexture;
}