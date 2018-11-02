:::::::::::::::
:: UPDATEX.BAT
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

:::::::::::::::
:: Display Info
chgcolor %CTEXT%
ECHO Update specific libs from extlibs and fast reinstall.
ECHO You can pass multiple values separated with ';'
ECHO Possible values: "SFML;tinyxml2;glew;glm;cpython;Rivet"
ECHO An empty input just does reinstall.

:::::::::::::::
:: Ask User
chgcolor %CRESET%
set /p SENDCOMMAND=":"
SET "SENDCOMMAND=%SENDCOMMAND%;NO_CLEAN_BY_EMPTY"

:::::::::::::::
:: Init repo & Checking changes & warning before issuing git operation
CALL "%BOLT_WIN_TOOLS_GIT_DIR%\_initgitsubmodules.bat" || goto :error

:::::::::::::::
:: Build
CALL "%EXTLIBS_BUILD_WIN_DIR%\buildall.bat" "%SENDCOMMAND%" || goto :error

:::::::::::::::
:: Install
CALL "%BOLT_WIN_TOOLS_SETUP_DIR%\_install_core.bat" || goto :error
CALL "%BOLT_WIN_TOOLS_SETUP_DIR%\_install_editor.bat" || goto :error
CALL "%BOLT_WIN_TOOLS_SETUP_DIR%\_install_ext_res.bat" || goto :error

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

