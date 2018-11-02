#pragma once


#include "Core.ECS.Core.Component.h"


#include "SFML/Graphics.hpp"
#include <string>

#include "Core.Base.FileSystem.h"


namespace nCore {
namespace nShader {


class cShader2D :
    public ::nCore::nECS::nCore::cComponentGeneric
{
public:
    typedef  ::nCore::nECS::nCore::cComponentGeneric  tSuperClass;

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
    const nStdFileSystem::path& GetPathToProgram() const;

private:
    nStdFileSystem::path    mPathToProgram;
    sf::Shader*             mTheShader;
};


} // namespace nShader
} // namespace nCore

