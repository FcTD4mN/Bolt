#pragma once


#include <vector>
#include <string>


namespace nCore {
namespace nBase {


std::vector< std::string >  Split( char iSplitChar, const std::string & iString );


template< class T >
inline
bool
VectorContains( const std::vector< T >& iVector, const T& iElement )
{
    for( auto elm : iVector )
    {
        if( elm == iElement )
            return  true;
    }

    return  false;
}


template< class T >
inline
void
EraseElementFromVector( std::vector< T >* oVector, const T& iElement )
{
    for( int i = 0; i < oVector->size(); ++i )
    {
        if( (*oVector)[ i ] == iElement )
            oVector->erase( oVector->begin() + i );
    }
}


template< typename tType >
inline
tType
Max( tType iA, tType iB )
{
    if( iA > iB )
        return  iA;

    return  iB;
}


template< typename tType >
inline
tType
Min( tType iA, tType iB )
{
    if( iA < iB )
        return  iA;

    return  iB;
}


template< typename tType >
inline
tType
Clamp( tType iA, tType iMin, tType iMax )
{
    if( iA <= iMin )
        return  iMin;
    else if( iA >= iMax )
        return  iMax;
    else
        return  iA;
}


} // namespace nBase
} // namespace nCore

