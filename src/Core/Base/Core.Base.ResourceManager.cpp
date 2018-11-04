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
cResourceManager::GetTexture( const nStdFileSystem::path & iFileName )
{
    auto finder = mTextures.find( iFileName.string() );

    stTexture& result = mTextures[ iFileName.string() ];

    if( !result.mTexture )
    {
        result.mTexture = new sf::Texture();
        bool loaded = result.mTexture->loadFromFile( iFileName.string() );
        if( !loaded )
            printf( "Failed loading image %s \n", iFileName.string().c_str() );
    }

    ++( result.mCounter );
    return  result.mTexture;
}


void
cResourceManager::InvalidateTexture( const nStdFileSystem::path & iFileName )
{
    mTextures.erase( iFileName.string() );
}


} // namespace nBase
} // namespace nCore

