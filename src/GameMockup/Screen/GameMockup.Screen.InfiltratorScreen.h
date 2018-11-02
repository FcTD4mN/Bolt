#pragma once


#include "Core.Screen.Screen.h"

#include "Core.GUI.ConsoleWidget.h"


namespace nCore { namespace nECS { namespace  nCore { class cEntity; } } }


namespace nScreen {


class cInfiltratorScreen :
    public cScreen
{
public:
    typedef  cScreen tSuperClass;

public:
    // Contruction/Destruction
    virtual  ~cInfiltratorScreen();
    cInfiltratorScreen();

public:
    virtual  void  Initialize() override;
    virtual  void  Finalize() override;

public:
    virtual  void  AdditionnalBuildScreen() override;

private:
    void  BuildBehaviourTree( ::nCore::nECS::nCore::cEntity* iEntity );

public:
    // Events
    virtual  void  KeyPressed( const sf::Event& iEvent ) override;             ///< A key was pressed (data in event.key)

private:
    ::nCore::nECS::nCore::cEntity* mMechant;

    sf::Transform mRotationFOV;
};


} // namespace nScreen

