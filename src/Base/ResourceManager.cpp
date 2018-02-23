#include "Base/Drawable.h"
#include "ResourceManager.h"


cResourceManager::~cResourceManager()
{
    for( auto it = mTextures.begin(); it != mTextures.end(); ++it )
    {
        delete  it->second;
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

    if( finder == mTextures.end() )
    {
        sf::Texture* texture = new sf::Texture();
        texture->loadFromFile( iFileName );
        mTextures.insert( std::make_pair( iFileName, texture ) );
    }

    return  mTextures[ iFileName ];
}
