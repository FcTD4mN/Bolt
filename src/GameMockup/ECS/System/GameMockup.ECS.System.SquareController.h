#pragma once


#include "Core.ECS.Core.System.h"


#include <SFML/Graphics.hpp>


namespace nECS {


class cSquareController :
    public ::nCore::nECS::nCore::cSystem
{
public:
    typedef  ::nCore::nECS::nCore::cSystem  tSuperClass;

public:
    virtual  ~cSquareController();
    cSquareController();
    cSquareController( const cSquareController& iSys );


    // Overrides
public:
    ::nCore::nECS::nCore::cSystem*  Clone() const override;
public:
    // Init/Finalize
    virtual  void  Initialize() override;
    virtual  void  Finalize() override;

public:
    // Update/Draw
    virtual  void  Draw( sf::RenderTarget* iRenderTarget ) override;
    virtual  void  Update( unsigned int iDeltaTime ) override;

public:
    // Entity
    virtual  void  IncomingEntity( ::nCore::nECS::nCore::cEntity* iEntity ) override;

private:
    unsigned int mVieuxTimer;
};


} // namespace ECS

