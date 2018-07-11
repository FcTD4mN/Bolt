#pragma once


#include "SFML/Graphics.hpp"
#include <string>
#ifdef WINDOWS
#include <filesystem>
namespace nFileSystem = std::filesystem;
#else
#include <experimental/filesystem>
namespace nFileSystem = std::experimental::filesystem;
#endif


namespace nShaders {


class cShaderFileLibrary
{
public:
    struct stFileShaderPair
    {
        sf::Shader*         mShader;
        nFileSystem::path   mFilePath;
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

