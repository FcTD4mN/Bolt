#pragma once

#include "ECS/Core/System.h"

#include <SFML/Graphics.hpp>

#include "Math/Triangle.h"

class cSightSystem :
    public cSystem
{
public:
    typedef  cSystem  tSuperClass;

public:
    virtual  ~cSightSystem();
    cSightSystem();


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
    std::vector< cEntity* > mPointsOfInterest;

    cTriangleF mFOVTriangle;

    std::vector< sf::VertexArray > mTriangles;
    sf::Transform mTransformation;

    std::vector< sf::VertexArray > mDEBUGClips;
    std::vector< sf::VertexArray > mDEBUGEntities;

};

