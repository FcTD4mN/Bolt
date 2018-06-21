#pragma once

#include <SFML/Graphics.hpp>
#include <tinyxml2.h>

#include <unordered_map>

namespace nECS { class cEntity; }
namespace nShaders { class cShader2D; }

namespace nRender {

class cLayer
{
public:
    // Contruction/Destruction
    ~cLayer();
    cLayer( const sf::Vector2f& iViewSize );

public:
    // Draw related methods
    void  Draw( sf::RenderTarget* iRenderTarget );

public:
    // Entity
    int  AddEntity( ::nECS::cEntity* iEntity );
    void RemoveEntity( ::nECS::cEntity* iEntity );

public:
    // Access
    void  ZLayer( float iZLayer );
    void  SetViewCenter( const sf::Vector2f& iViewCenter );

    const std::string&  Name() const;
    void                Name( const std::string& iName );

    //EDITOR
    int  EntityCount() const;
    ::nECS::cEntity* EntityAtIndex( int iIndex );

public:
    void  AddShader( ::nShaders::cShader2D* iShader );

private:
    // Private
    void  ClearShaders();

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

protected:
    std::string                             mName;
    std::list< ::nECS::cEntity* >           mEntities;
    sf::View                                mView;
    float                                   mZLayer;

    sf::RenderTexture*                      mShaderRenderTextureInput;
    sf::RenderTexture*                      mShaderRenderTextureOutput;
    std::vector< ::nShaders::cShader2D* >   mShaders; // Pointers otherwise it won't compile for some annoying reasons
};


} // namespace nECS

