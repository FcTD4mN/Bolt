#include "Core.Shader.Shader2D.h"


#include <filesystem>
#include <assert.h>


namespace nShaders {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction
//----------------------------------------------------------------------------------------------


cShader2D::~cShader2D()
{
}


cShader2D::cShader2D( const std::string& iPathToProgram, const std::string& iShaderName ) :
    mPathToProgram( iPathToProgram ),
    mTheShader( 0 ),
    tSuperClass( iShaderName )
{
}


void
cShader2D::LoadShader()
{
    bool error;
    if( mPathToProgram.extension() == ".frag" )
        error = mTheShader->loadFromFile( mPathToProgram.string().c_str(), sf::Shader::Fragment );
    else if( mPathToProgram.extension() == ".vert" )
        error = mTheShader->loadFromFile( mPathToProgram.string().c_str(), sf::Shader::Vertex );

    assert( !error );
}


void
cShader2D::ApplyUniforms()
{
}


} // namespace nShader

