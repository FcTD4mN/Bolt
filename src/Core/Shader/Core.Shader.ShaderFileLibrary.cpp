#include "Core.Shader.ShaderFileLibrary.h"


#include "Core.Application.GlobalAccess.h"

#include <filesystem>

namespace nShaders {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction
//----------------------------------------------------------------------------------------------


cShaderFileLibrary::~cShaderFileLibrary()
{
}


cShaderFileLibrary::cShaderFileLibrary()
{
}

cShaderFileLibrary *
cShaderFileLibrary::Instance()
{
    static  cShaderFileLibrary* sgShaderFileLibrary = 0;
    if( !sgShaderFileLibrary )
        sgShaderFileLibrary = new cShaderFileLibrary();

    return  sgShaderFileLibrary;
}


void
cShaderFileLibrary::AddShaderFile( const std::string & iFile, sf::Shader::Type iShaderType )
{
    stFileShaderPair newEntry;
    newEntry.mFilePath = iFile;
    newEntry.mShader = new  sf::Shader();
    if( newEntry.mShader->loadFromFile( iFile, iShaderType ) )
    {
        mShaderLibrary.push_back( newEntry );
    }
}


sf::Shader*
cShaderFileLibrary::GetShaderFromFile( const std::string & iFile )
{
    for( auto shader : mShaderLibrary )
    {
        auto test = shader.mFilePath.filename().string();
        if( shader.mFilePath.filename().string() == iFile )
            return  shader.mShader;
    }

    return  0;
}


void
cShaderFileLibrary::ParseDir( const std::string& iFolder )
{
    std::filesystem::directory_iterator di( iFolder );

    for( auto file : di )
    {
        if( file.path().extension() == ".frag" )
            AddShaderFile( file.path().string(), sf::Shader::Fragment );
        else if( file.path().extension() == ".vert" )
            AddShaderFile( file.path().string(), sf::Shader::Vertex);
    }
}


} // namespace nShader

