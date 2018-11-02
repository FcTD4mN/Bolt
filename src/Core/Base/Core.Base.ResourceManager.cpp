#include "Core.Base.ResourceManager.h"


#include "Core.Base.Drawable.h"


#include <iostream>


namespace nCore {
namespace nBase {


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
        bool loaded = result.mTexture->loadFromFile( iFileName );
        if( !loaded )
            printf( "Failed loading image %s \n", iFileName.c_str() );
    }

    ++(result.mCounter);
    return  result.mTexture;
}


sf::Texture*
cResourceManager::GetTexture( const nStdFileSystem::path & iFileName )
{
    return  GetTexture( iFileName.string() );
}


void
cResourceManager::InvalidateTexture( const nStdFileSystem::path & iFileName )
{
    mTextures.erase( iFileName.string() );
}


} // namespace nBase
} // namespace nCore

