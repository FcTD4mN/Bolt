#pragma once


#include <string>


namespace nBase {

// Default Implementation returns an empty string, see OS specific implementations.
std::string GetClipboardText();

// Default Implementation does nothing, see OS specific implementations.
void SetClipboardText( const  std::string&  iString );

} // nBase

