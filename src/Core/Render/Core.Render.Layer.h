#pragma once

#include <SFML/Graphics.hpp>
#include <tinyxml2.h>

#include <unordered_map>

namespace nECS { class cEntity; }
namespace nMapping { class cEntityGrid; }
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
    void				ZLayer( float iZLayer );
    void				SetView( const sf::View& iViewCenter );
	sf::View			View();
    void				ApplyZoom( float iZoom );

    const std::string&  Name() const;
    void                Name( const std::string& iName );

	// EntityGrid
	::nMapping::cEntityGrid* EntityGrid();

    //EDITOR
    int					EntityCount() const;
    ::nECS::cEntity*	EntityAtIndex( int iIndex );

public:
    void  AddShader( ::nShaders::cShader2D* iShader );

public:
	// Coordinates
	sf::Vector2f	MapVectToLayer( const sf::Vector2f& iVector ) const;
	sf::Vector2f	MapVectFromLayer( const sf::Vector2f& iVector ) const;
	sf::FloatRect	MapRectToLayer( const sf::FloatRect& iRect) const;
	sf::FloatRect	MapRectFromLayer( const sf::FloatRect& iRect) const;

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

	// View transformation stuff
    sf::View                                mView;
	sf::Vector2f							mOffset;		// The offset this layer's view has
	float									mZoomFactor;	// The zoom of this specific layer
    float                                   mZLayer;

	::nMapping::cEntityGrid*				mEntityGrid;

	bool									mFixedLayer;	// Means that this layer is completely fixed : not affected by zoom or camera movement

    sf::RenderTexture*                      mShaderRenderTextureInput;
    sf::RenderTexture*                      mShaderRenderTextureOutput;
    std::vector< ::nShaders::cShader2D* >   mShaders;		// Pointers otherwise it won't compile for some annoying reasons
};


} // namespace nECS

