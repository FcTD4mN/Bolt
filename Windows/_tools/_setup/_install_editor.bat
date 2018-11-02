:::::::::::::::
:: _INSTALL_EDITOR.BAT
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
:: Check if Extlibs are installed properly since we are going to install them in the project directories
chgcolor %CTEXT%
ECHO Checking install setup before proceeding
CALL "%EXTLIBS_BUILD_WIN_DIR%\check_install.bat" || goto :error

:::::::::::::::
:: Copy DLL Files
call:checkMakeDir "%BOLT_EDITOR_DIR%\x64\"
call:checkMakeDir "%BOLT_EDITOR_DIR%\x64\Release\"
call:checkMakeDir "%BOLT_EDITOR_DIR%\x64\Debug\"
COPY "%EXTLIBS_DIR%\_install\release_x64\bin\openal32.dll" "%BOLT_EDITOR_DIR%\x64\Release\openal32.dll"
COPY "%EXTLIBS_DIR%\_install\debug_x64\bin\openal32.dll" "%BOLT_EDITOR_DIR%\x64\Debug\openal32.dll"

:::::::::::::::
:: Copy Python STD lib files
call:checkMakeDir "%BOLT_EDITOR_DIR%\Lib\"
XCOPY /e /h /y "%EXTLIBS_DIR%\Custom-Minimal-Static-Safe-cpython\Lib" "%BOLT_EDITOR_DIR%\Lib\"

GOTO :success

:::::::::::::::
:: Dir processing
:checkMakeDir
IF NOT EXIST "%~1\" ( MKDIR "%~1" )
goto:EOF
:: Return

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

