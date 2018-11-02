#include "Core.Registries.ShaderRegistry.h"


#include "Core.Application.GlobalAccess.h"
#include "Core.Shader.Shader2D.h"

#include <tinyxml2.h>
#include <algorithm>


namespace nCore {
namespace nRegistries {


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cShaderRegistry::~cShaderRegistry()
{
}


cShaderRegistry::cShaderRegistry()
{
}


// -------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------- Instance
// -------------------------------------------------------------------------------------


cShaderRegistry*
cShaderRegistry::Instance()
{
    static cShaderRegistry* sgSystemsRegistry = 0;
    if( !sgSystemsRegistry )
        sgSystemsRegistry = new cShaderRegistry();

    return  sgSystemsRegistry;
}


// -------------------------------------------------------------------------------------
// ----------------------------------------------------------------------- Init/Finalize
// -------------------------------------------------------------------------------------


void
cShaderRegistry::Initialize()
{
    // This is kinda more complex than this,
    // each shader is a generic component with its own values.
    // Loading a shader should mean loading all variables as well = reading a xml file.
    // So do we have two files ? the .frag/.vec + an xml descriptor ?
    nStdFileSystem::path shadersDir = PROJECTDIR + "/Assets/Shaders/";
    nStdFileSystem::directory_iterator end{};

    for( nStdFileSystem::directory_iterator it { shadersDir }; it != end; ++it )
    {
        if( nStdFileSystem::is_regular_file( *it ) )
        {
            ::nCore::nShader::cShader2D* shader = new ::nCore::nShader::cShader2D( it->path().string(), it->path().stem().string() );
            shader->LoadShader(); // Do we need to here ? or do we wait later ?
            RegisterItem( it->path().stem().string(), shader );
            SetItemFileUsingItemName( it->path().stem().string(), it->path() );
        }
    }
}


void
cShaderRegistry::Finalize()
{
    for( auto it = mItems.begin(); it != mItems.end(); ++it )
        delete  it->second.mItem;

    mItems.clear();
}


} // namespace nRegistries
} // namespace nCore

