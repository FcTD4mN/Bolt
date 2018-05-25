#pragma once


#include <SFML/Graphics.hpp>
#include <tinyxml2.h>


#include <unordered_map>


namespace nECS { class cEntity; }

namespace nRender {

class cLayer
{
public:
    // Contruction/Destruction
    ~cLayer();
    cLayer();

public:
    // Draw related methods
    void  Draw( sf::RenderTarget* iRenderTarget );

public:
    // Entity
    void AddEntity( ::nECS::cEntity* iEntity );

public:
    // Access
    size_t EntityCount() const;
    void  ZLayer( float iZLayer );
    void SetViewCenter( const sf::Vector2f& iViewCenter );

public:
    void  AddShader( sf::Shader* iShader );

private:
    // Private
    void  RemoveEntity( ::nECS::cEntity* iEntity );

protected:
    std::list< ::nECS::cEntity* >   mEntities;
    sf::View                        mView;
    float                           mZLayer;

    sf::RenderTexture*              mShaderRenderTextureInput;
    sf::RenderTexture*              mShaderRenderTextureOutput;
    std::vector< sf::Shader* >      mShaders; // Pointers otherwise it won't compile for some annoying reasons
};


} // namespace nECS

