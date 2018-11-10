#pragma once


#include "Core.ECS.Core.System.h"


#include <SFML/Graphics.hpp>


namespace nCore {
namespace nECS {
namespace nSystem {


class cInputConverter :
    public ::nCore::nECS::nCore::cSystem
{
public:
    typedef  cSystem  tSuperClass;

public:
    virtual  ~cInputConverter();
    cInputConverter();
    cInputConverter( const cInputConverter& iSys );

    // Overrides
public:
    virtual  cSystem* Clone() const override;

public:
    // Entity
    virtual  void  IncomingEntity( ::nCore::nECS::nCore::cEntity* iEntity ) override;

public:
    // Events
    virtual  void  KeyPressed( const sf::Event& iEvent ) override;             ///< A key was pressed (data in event.key)
    virtual  void  KeyReleased( const sf::Event& iEvent ) override;            ///< A key was released (data in event.key)

};


} // namespace nSystem
} // namespace nECS
} // namespace nCore

