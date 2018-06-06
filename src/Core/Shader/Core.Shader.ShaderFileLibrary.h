#pragma once


#include "SFML/Graphics.hpp"
#include <string>
#include <filesystem>


namespace nShaders {


class cShaderFileLibrary
{
public:
    struct stFileShaderPair
    {
        sf::Shader*             mShader;
        std::filesystem::path   mFilePath;
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

