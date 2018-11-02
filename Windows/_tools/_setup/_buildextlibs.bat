:::::::::::::::
:: _BUILDEXTLIBS.BAT
:::::::::::::::
@ECHO OFF
:::::::::::::::
:: Init Shell
CALL "%~dp0../_initboltshell.bat"
:::::::::::::::
:: HEADER
chgcolor %CHEADER%
ECHO //////////
ECHO %0: START
:::::::::::::::
:: Init Bolt Dev Env Variables
CALL _initboltenv.bat || goto :error
:::::::::::::::

:::::::::::::::
:: Init repo & Checking changes & warning before issuing git operation
CALL "%BOLT_WIN_TOOLS_GIT_DIR%\_initgitsubmodules.bat" || goto :error

:::::::::::::::
:: Delegate build to Extlibs Scripts
CALL "%EXTLIBS_BUILD_WIN_DIR%\buildall.bat" || goto :error

GOTO :success

:::::::::::::::
:error
chgcolor %CERROR%
ECHO %0: ERROR
ECHO //////////
chgcolor %CRESET%
EXIT /B 1

:::::::::::::::
:success
chgcolor %CSUCCESS%
ECHO %0: SUCCESS
ECHO //////////
chgcolor %CRESET%
EXIT /B 0

