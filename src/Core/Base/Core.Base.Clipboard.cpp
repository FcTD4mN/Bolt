#include "Core.Base.Clipboard.h"


#ifndef  _WIN32

namespace nBase {

std::string
GetClipboardText()
{
    // Default Implementation returns an empty string
    std::string defaultStr = "";
    return defaultStr;
}

void
SetClipboardText( const  std::string&  iString )
{
}

}//nBase

#endif // ! _WIN32

