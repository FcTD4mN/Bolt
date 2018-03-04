#include "Base/Utilities.h"

#include <sstream>

std::vector<std::string>
Split( char iSplitChar, const std::string & iString )
{
    std::vector< std::string > strings;
    std::istringstream f( iString );
    std::string word;
    while( std::getline( f, word, iSplitChar ) )
    {
        strings.push_back( word );
    }

    return  strings;
}