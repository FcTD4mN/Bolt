 #include "Color.h"


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// -------------------------------------------------------------------------------------


cColor::~cColor()
{
}


cColor::cColor() :
    tSuperClass( "color" ),
    mColor( sf::Color( 0, 0, 0, 255 ) )
{
}


cColor::cColor( int iR, int iG, int iB, int iA ) :
    tSuperClass( "color" ),
    mColor( sf::Color( iR, iG, iB, iA ) )
{
}


cColor::cColor( sf::Color iColor ) :
    tSuperClass( "color" ),
    mColor( sf::Color( iColor ) )

{
}

