#include "Size.h"


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------ Construction/Destruction
// ------------------------------------------------------------------------------------- 


cSize::~cSize()
{
}


cSize::cSize() :
    tSuperClass( "size" ),
    mSize( sf::Vector2f( 0, 0 ) )
{
}


cSize::cSize( float iW, float iH ) :
    tSuperClass( "size" ),
    mSize( sf::Vector2f( iW, iH ) )
{
}


cSize::cSize( const sf::Vector2f& iSize ) :
    tSuperClass( "size" ),
    mSize( iSize )
{
}

