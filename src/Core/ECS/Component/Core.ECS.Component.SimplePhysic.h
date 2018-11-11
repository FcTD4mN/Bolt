#pragma once


#include "Core.ECS.Core.Component.h"


#include <SFML/Graphics.hpp>


namespace nCore { namespace nECS { namespace nCore { class cEntity; } } }


namespace nCore {
namespace nECS {
namespace nComponent {


class cSimplePhysic :
    public ::nCore::nECS::nCore::cComponentGeneric
{
public:
    typedef  ::nCore::nECS::nCore::cComponentGeneric  tSuperClass;

public:
    enum eType
    {
        kStatic = 0,
        kDynamic
    };

public:
    virtual  ~cSimplePhysic();
    cSimplePhysic();
    cSimplePhysic( double iW, double iH, eType iType, bool iIsTrigger );
    cSimplePhysic( const cSimplePhysic& iSimplePhysic );

private:
    void BuildComponent( double iCenterX, double iCenterY, double iSizeW, double iSizeH, eType iType, bool iIsTrigger );
    void BuildCallbacks();

public:
    // Copy
    virtual  ::nCore::nECS::nCore::cComponent* Clone() const;

public:
    eType  PhysicType() const;
    void   PhysicType( eType  iType );

    double  CenterX();
    double  CenterY();
    sf::Vector2f CenterAsVector2f();
    void SetCenter( const sf::Vector2f& iCenter );

    double  SizeW();
    double  SizeH();
    sf::Vector2f SizeAsVector2f();
    void SetSize( const sf::Vector2f& iSize );

    double  GravityFactor();
    void    GravityFactor( double iGravityFactor );

    bool  IsTrigger();
    void  IsTrigger( bool iIsTrigger );

    void  SetCollisionCB( std::function<void( ::nCore::nECS::nCore::cEntity* iCollider ) > iCB );
    void  CallCollisionCB( ::nCore::nECS::nCore::cEntity* iEntity );

    sf::FloatRect RelativeHitBox();

    sf::FloatRect GetAbsoluteHitBoxUsingCenterPosition( const sf::Vector2f& iCenterPosition );

public:
    // Input/Output
    virtual  void SaveXML( tinyxml2::XMLElement* iNode, tinyxml2::XMLDocument* iDocument )  const;
    virtual  void LoadXML( tinyxml2::XMLElement* iNode );

public:
    sf::Vector2f        mVelocity;
    eType               mType;

    std::function< void( ::nCore::nECS::nCore::cEntity* iCollider ) > mCollisionCB;

    // Cached stuff
    sf::FloatRect           mCachedHitBox;
    bool                    mIsCacheValid;
    sf::Vector2f            mCachedHitBoxCenter;
};


} // namespace nComponent
} // namespace nECS
} // namespace nCore

