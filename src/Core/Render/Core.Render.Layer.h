#pragma once


#include <SFML/Graphics.hpp>
#include <tinyxml2.h>
#include <unordered_map>
#include <list>


namespace nCore::nECS::nCore    { class cEntity; }
namespace nCore::nMapping       { class cEntityMap; }
namespace nCore::nShader        { class cShader2D; }
namespace nCore::nRender        { class cLayerEngine; }


namespace nCore {
namespace nRender {


class cLayer
{
    friend cLayerEngine; // The only thing that can create/destroy layers

public:
    enum  eLayerMappingType
    {
        kPositionSize,
        kPhysics
    };

private:
    // Contruction/Destruction
    ~cLayer();
    cLayer( cLayerEngine* iParentLayerEngine, const sf::Vector2f& iViewSize, eLayerMappingType iType );

public:
    // Draw related methods
    void  Draw( sf::RenderTarget* iRenderTarget );

public:
    // Entity
    int  AddEntity( ::nCore::nECS::nCore::cEntity* iEntity );
    void RemoveEntity( ::nCore::nECS::nCore::cEntity* iEntity );

public:
    // Access
    void                ZLayer( float iZLayer );
    float               ZLayer() const;
    void                SetView( const sf::View& iViewCenter );
    sf::View            View();
    void                ApplyZoom( float iZoom );

    const std::string&  Name() const;
    void                Name( const std::string& iName );

    bool                Fixed() const;
    void                Fixed( bool iFixed );

    bool                Visible() const;
    void                Visible( bool iVisible );

    int                 Index() const;

    // EntityMap
    ::nCore::nMapping::cEntityMap* EntityMap();

    //EDITOR
    int                                 EntityCount() const;
    ::nCore::nECS::nCore::cEntity*      EntityAtIndex( int iIndex );
    int                                 EntityIndex( ::nCore::nECS::nCore::cEntity* iEntity );
    int                                 LayerIndex() const;

public:
    void            AddShader( ::nCore::nShader::cShader2D* iShader );

public:
    // Coordinates
    sf::Vector2f    MapVectToLayer( const sf::Vector2f& iVector ) const;
    sf::Vector2f    MapVectFromLayer( const sf::Vector2f& iVector ) const;
    sf::FloatRect   MapRectToLayer( const sf::FloatRect& iRect) const;
    sf::FloatRect   MapRectFromLayer( const sf::FloatRect& iRect) const;

private:
    // Private
    void  ClearShaders();

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument );
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

protected:
    cLayerEngine*                               mParentLayerEngine;

    std::string                                 mName;
    std::list< ::nCore::nECS::nCore::cEntity* > mEntities;

    // View transformation stuff
    sf::View                                    mView;
    sf::Vector2f                                mOffset;        // The offset this layer's view has
    float                                       mZoomFactor;    // The zoom of this specific layer
    float                                       mZLayer;

    ::nCore::nMapping::cEntityMap*             mEntityMap;
    eLayerMappingType                           mMappingType;

    bool                                        mFixedLayer;    // Means that this layer is completely fixed : not affected by zoom or camera movement
    bool                                        mVisible;

    sf::RenderTexture*                          mShaderRenderTextureInput;
    sf::RenderTexture*                          mShaderRenderTextureOutput;
    std::vector< ::nCore::nShader::cShader2D* > mShaders;       // Pointers otherwise it won't compile for some annoying reasons
};


} // namespace nRender
} // namespace nCore

