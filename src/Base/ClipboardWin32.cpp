#include "Base/Clipboard.h"


#ifdef  _WIN32

#include <Windows.h>

std::string GetClipboardText()
{
    std::string defaultStr = "";

    // Try opening the clipboard
    if (! OpenClipboard(nullptr))
    return  defaultStr;

    // Get handle of clipboard object for ANSI text
    HANDLE hData = GetClipboardData(CF_TEXT);
    if (hData == nullptr)
    return  defaultStr;

    // Lock the handle to get the actual text pointer
    char * pszText = static_cast<char*>( GlobalLock(hData) );
    if (pszText == nullptr)
    return  defaultStr;

    // Save text in a string class instance
    std::string text( pszText );

    // Release the lock
    GlobalUnlock( hData );

    // Release the clipboard
    CloseClipboard();

    return text;
}


void
SetClipboardText( const  std::string&  iString )
{
    const char* output = iString.c_str();
    const size_t len = strlen(output) + 1;
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), output, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
}

#endif // _WIN32

