#pragma once


#include <string>
#include <vector>


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


void  ParseDir( std::vector< std::wstring >* oFileNames, const std::wstring& iDir );


} // namespace  nBase

