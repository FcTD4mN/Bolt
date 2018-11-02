#pragma once


#include "SFML/Graphics.hpp"
#include <string>


#include "Core.Base.FileSystem.h"


namespace nCore {
namespace nShader {


class cShaderFileLibrary
{
public:
    struct stFileShaderPair
    {
        sf::Shader*             mShader;
        nStdFileSystem::path    mFilePath;
    };

private:
    // Construction / Destruction
    ~cShaderFileLibrary();
    cShaderFileLibrary();

public:
    static cShaderFileLibrary * Instance();

public:
    // Library management
    void            AddShaderFile( const std::string& iFile, sf::Shader::Type iShaderType );
    sf::Shader*     GetShaderFromFile( const std::string& iFile );
    void            ParseDir( const std::string& iFolder );

private:
    std::vector< stFileShaderPair > mShaderLibrary;
};


} // namespace nShader
} // namespace nCore

