#pragma once


#include "Core.ECS.Core.System.h"


#include <SFML/Graphics.hpp>


namespace nCore {
namespace nECS {
namespace nSystem {


class cSimplerRenderer :
    public ::nCore::nECS::nCore::cSystem
{
public:
    typedef  cSystem  tSuperClass;

public:
    virtual  ~cSimplerRenderer();
    cSimplerRenderer();
    cSimplerRenderer( const cSimplerRenderer& iSys );

    // Overrides
public:
    virtual     void        Initialize() override;
    virtual     cSystem*    Clone() const override;

public:
    // Update/Draw
    virtual  void  DrawEntity( sf::RenderTarget* iRenderTarget, ::nCore::nECS::nCore::cEntity* iEntity ) override;
    virtual  void  Update( unsigned int iDeltaTime ) override;

public:
    // Entity
    virtual  void  IncomingEntity( ::nCore::nECS::nCore::cEntity* iEntity ) override;

private:
    sf::Font mFont;
};


} // namespace nSystem
} // namespace nECS
} // namespace nCore

