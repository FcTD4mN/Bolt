:::::::::::::::
:: FIX_INSTALL.BAT
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
:: Init Bolt Dev Env Variables
CALL _initboltenv.bat || goto :error

:::::::::::::::
:: Install Bolt Extlibs Libraries
chgcolor %CTEXT%
ECHO Installing Extlibs
CALL "%BOLT_WIN_TOOLS_PREBUILD_DIR%\_clean_res_hash.bat"
SETLOCAL
CALL "%BOLT_WIN_TOOLS_SETUP_DIR%\_install_core.bat" || goto :error
CALL "%BOLT_WIN_TOOLS_SETUP_DIR%\_install_editor.bat" || goto :error
CALL "%BOLT_WIN_TOOLS_SETUP_DIR%\_install_ext_res.bat" || goto :error
ENDLOCAL

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

