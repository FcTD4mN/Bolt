#pragma once

#include "Core.ECS.Core.Component.h"

#include "SFML/Graphics.hpp"
#include <string>
#include <filesystem>


namespace nShaders {


class cShader2D :
    public ::nECS::cComponentGeneric
{
public:
    typedef  ::nECS::cComponentGeneric  tSuperClass;

public:
    // Construction / Destruction
    ~cShader2D();
    cShader2D( const std::string& iPathToProgram, const std::string& iShaderName );

public:
    void  LoadShader();
    void  ApplyUniforms();

public:
    // Get/Set
    sf::Shader* GetSFShader();
    const std::filesystem::path& GetPathToProgram() const;

private:
    std::filesystem::path   mPathToProgram;
    sf::Shader*             mTheShader;
};


} // namespace nShader

