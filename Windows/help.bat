:::::::::::::::
:: SETUP.BAT
:::::::::::::::
@ECHO OFF
:::::::::::::::
:: Init Shell
CALL "%~dp0_tools\_initboltshell.bat"
:::::::::::::::
:: HEADER
chgcolor %CHEADER%
ECHO //////////
ECHO %0: START
:::::::::::::::

:::::::::::::::
:: SHUT ASK
SET SILENT_ASK=1

:::::::::::::::
:: Display README & Ask User Before Continue
chgcolor %CTEXT%
TYPE "%~dp0README.txt"

ECHO deploy_all.bat         ... Call both deploy_core and deploy_editor
ECHO deploy_core.bat        ... Build Core, mkdir BoltCore_Deployed, ready to use
ECHO deploy_editor.bat      ... Build Core, mkdir BoltEditor_Deployed, ready to use
ECHO fix_install.bat        ... Copy ext dependancies in both solution dirs
ECHO full_clean.bat         ... Clean deploy, dependancies and VisualStudio files
ECHO help.bat               ... Display help
ECHO prebuild_core.bat      ... Copy resources in Core if needed before build
ECHO prebuild_editor.bat    ... Copy resources in Editor if needed before build
ECHO quick_clean.bat        ... Clean deploy and VisualStudio files but keeps dependancies
ECHO README.txt             ... Display info
ECHO setup.bat              ... Full setup of Bolt environment, ready for development. Delegate Extlibs build
ECHO updatex.bat            ... Update a specific Extlib ( prompted ) and reinstall
ECHO _tools                 ... Batch framework tools.

:::::::::::::::
:: Reaching End of the Script
GOTO :success

:::::::::::::::
:error
chgcolor %CERROR%
ECHO %0: ERROR
ECHO //////////
chgcolor %CRESET%
PAUSE
EXIT /B 1

:::::::::::::::
:success
chgcolor %CSUCCESS%
ECHO %0: SUCCESS
ECHO //////////
chgcolor %CRESET%
PAUSE
EXIT /B 0

