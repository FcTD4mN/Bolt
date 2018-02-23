#include "Base/Clipboard.h"


#include <string>
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
