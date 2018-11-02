#include "Core.Base.Clipboard.h"


#ifndef  _WIN32


namespace nCore {
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


} // namespace nBase
} // namespace nCore


#endif // ! _WIN32

