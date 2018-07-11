#include "Core.Base.Utilities.h"


#include <iostream>
#include <sstream>
#include <regex>

#ifdef WINDOWS
#include <Windows.h>
#else
#include <locale>
#include <codecvt>
#include <experimental/filesystem>
namespace nFileSystem = std::experimental::filesystem;
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

void
ParseDir( std::vector< std::string >* oFileNames, const std::string& iDir )
{
    if( !nFileSystem::exists( iDir ) )
        return;
    for( auto it : nFileSystem::directory_iterator( iDir ) )
        oFileNames->push_back( it.path() );
}

#else

std::wstring s2ws(const std::string& str)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.from_bytes(str);
}

std::string ws2s(const std::wstring& wstr)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}

void
ParseDir( std::vector< std::wstring >* oFileNames, const std::wstring& iDir )
{
    std::string  dir = ws2s(iDir);
    if( !nFileSystem::exists( dir ) )
        return;
    for( auto it : nFileSystem::directory_iterator( dir ) )
        oFileNames->push_back( s2ws(it.path()) );
}

void
ParseDir( std::vector< std::string >* oFileNames, const std::string& iDir )
{
    if( !nFileSystem::exists( iDir ) )
        return;
    for( auto it : nFileSystem::directory_iterator( iDir ) )
        oFileNames->push_back( it.path() );
}

#endif


} //nBase

