#include "Edge.h"


#include "Math/Utils.h"

// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------ Construction
// -------------------------------------------------------------------------------------


cEdgeF::~cEdgeF()
{
}


cEdgeF::cEdgeF() :
    mPoint( sf::Vector2f( 0.0F, 0.0F ) ),
    mDirection( sf::Vector2f( 0.0F, 0.0F ) )
{
}


cEdgeF
cEdgeF::MakePointDirection( const sf::Vector2f & iPoint, const sf::Vector2f & iDirection )
{
    cEdgeF  ret;
    ret.mPoint = iPoint;
    ret.mDirection = iDirection;
    return  ret;
}


cEdgeF
cEdgeF::MakePointPoint( const sf::Vector2f & iPoint, const sf::Vector2f & iPoint2 )
{
    cEdgeF  ret;
    ret.mPoint = iPoint;
    ret.mDirection = iPoint2 - iPoint;
    return  ret;
}


bool
cEdgeF::Intersect( float* oParameterA, float* oParameterB, const cEdgeF & iEdge ) const
{
    if( iEdge.mPoint == mPoint && iEdge.mDirection == mDirection )
    {
        *oParameterA = 0.0F;
        *oParameterB = 0.0F;
        return true;
    }

    if( Collinear( mDirection, iEdge.mDirection ) )
    {
        return  iEdge.mPoint == mPoint;
    }

    sf::Vector2f O = mPoint;
    sf::Vector2f P = iEdge.mPoint;
    sf::Vector2f u = mDirection;
    sf::Vector2f v = iEdge.mDirection;

    *oParameterA = ( O.y * v.x - P.y * v.x - O.x * v.y + P.x * v.y ) / ( u.x * v.y - u.y * v.x );

    if( abs(v.y) < kEpsilonF )
        *oParameterB = ( O.x + ( *oParameterA ) * u.x - P.x ) / v.x;
    else
        *oParameterB = ( O.y + ( *oParameterA ) * u.y - P.y ) / v.y;

    return  true;
}


bool
cEdgeF::Intersect( float* oParameterA, float* oParameterB, const cEdgeF & iEdgeA, const cEdgeF & iEdgeB )
{
    return  iEdgeA.Intersect( oParameterA, oParameterB, iEdgeB );
}

