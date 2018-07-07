#include "Core.Base.Utilities.h"


#include <sstream>
#include <regex>

#ifdef WINDOWS
#include <Windows.h>
#endif

namespace nBase {


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


// -------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------ TOMOVE
// -------------------------------------------------------------------------------------

#ifdef WINDOWS

void
ParseDir( std::vector< std::wstring >* oFileNames, const std::wstring& iDir )
{
    //TODO: Create a file manager class to handle every OS, or find a way with sfml
    WIN32_FIND_DATAW  finddata;

    std::wstring substitute = std::regex_replace( iDir, std::wregex( L"/" ), L"\\" );
    substitute.push_back( L'*' );

    HANDLE f = FindFirstFileW( substitute.c_str(), &finddata );
    if( f == INVALID_HANDLE_VALUE )
        return;

    std::wstring file( finddata.cFileName );
    if( ( file != L"." ) && ( file != L".." ) )
        ( *oFileNames ).push_back( iDir + file );

    while( FindNextFileW( f, &finddata ) )
    {
        std::wstring file( finddata.cFileName );
        if( ( file != L"." ) && ( file != L".." ) )
            ( *oFileNames ).push_back( iDir + file );
    }

    FindClose( f );
}

#else

void
ParseDir( std::vector< std::wstring >* oFileNames, const std::wstring& iDir )
{
    //todo
}

#endif


} //nBase

