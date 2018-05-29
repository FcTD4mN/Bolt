#pragma once

#include "Core.ECS.Core.System.h"

#include "Core.Mapping.PhysicEntityGrid.h"


#include <SFML/Graphics.hpp>


namespace nECS {

class cEntity;
class cPosition;

class cOcclusionSystem :
    public cSystem
{
public:
    typedef  cSystem  tSuperClass;

public:
    virtual  ~cOcclusionSystem();
    cOcclusionSystem();


    // Overrides
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
    virtual  void  IncomingEntity( cEntity* iEntity ) override;

private:
    cEntity*    mListener;
    cPosition*  mListenerPosition;

    std::vector< cEntity* > mSoundEmitters;
    std::vector< cEntity* > mSoundOccluser;
};


} // namespace nECS

