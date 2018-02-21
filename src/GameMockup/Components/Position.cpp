#include "Position.h"


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cPosition::~cPosition()
{
}


cPosition::cPosition() :
    tSuperClass( "position" ),
    mPosition( sf::Vector2i( 0, 0 ) )
{
}


cPosition::cPosition( float iX, float iY ) :
    tSuperClass( "position" ),
    mPosition( sf::Vector2f( iX, iY ) )
{
}


cPosition::cPosition( const sf::Vector2f& iPosition ) :
    tSuperClass( "position" ),
    mPosition( iPosition )
{
}

