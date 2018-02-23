#include "Base/Clipboard.h"


#ifndef  _WIN32

std::string GetClipboardText()
{
    // Default Implementation returns an empty string
    std::string defaultStr = "";
    return defaultStr;
}

#endif // ! _WIN32

