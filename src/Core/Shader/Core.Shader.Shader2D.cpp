#include "Core.Shader.Shader2D.h"


#include "Core.Application.GlobalAccess.h"

#include <filesystem>
#include <assert.h>


namespace nCore {
namespace nShader {


//----------------------------------------------------------------------------------------------
//------------------------------------------------------------------- Construction / Destruction
//----------------------------------------------------------------------------------------------


cShader2D::~cShader2D()
{
    delete  mTheShader;
}


cShader2D::cShader2D( const std::string& iPathToProgram, const std::string& iShaderName ) :
    mTheShader( 0 ),
    tSuperClass( iShaderName )
{
    mPathToProgram = PROJECTDIR + "/Assets/Shaders/" + iPathToProgram;
    LoadShader();
}


void
cShader2D::LoadShader()
{
    bool noError;
    mTheShader = new sf::Shader();
    if( mPathToProgram.extension() == ".frag" )
        noError = mTheShader->loadFromFile( mPathToProgram.string().c_str(), sf::Shader::Fragment );
    else if( mPathToProgram.extension() == ".vert" )
        noError = mTheShader->loadFromFile( mPathToProgram.string().c_str(), sf::Shader::Vertex );

    assert( noError );
}


void
cShader2D::ApplyUniforms()
{
    VariableEnumerator( [ this ]( const std::string& iVarName, ::nCore::nBase::cVariant* iVariant )
    {
        switch( iVariant->Type() )
        {
            case ::nCore::nBase::kNumber :
                mTheShader->setUniform( iVarName.c_str(), float(iVariant->GetValueNumber()) );
                break;
            default :
                printf( "Invalid Variant Type.\n" );
        }
    } );
}


//----------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------- Get/Set
//----------------------------------------------------------------------------------------------


sf::Shader*
cShader2D::GetSFShader()
{
    return  mTheShader;
}


const nStdFileSystem::path&
cShader2D::GetPathToProgram() const
{
    return  mPathToProgram;
}


} // namespace nShader
} // namespace nCore

