:::::::::::::::
:: DEPLOY_CORE.BAT
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
:: Check & Init
CALL "%EXTLIBS_BUILD_WIN_DIR%\check_install.bat" || goto :error
CALL "%BOLT_WIN_TOOLS_MSVC_DIR%\_init_msvc.bat" || goto :error
CALL "%BOLT_WIN_TOOLS_PREBUILD_DIR%\_clean_res_hash.bat"
:::::::::::::::
:: Building Core
SET "OVERRIDE_WIN_SDK=$(WindowsTargetPlatformVersion)"
IF "%WINDOWS_VERSION%" == "7" SET "OVERRIDE_WIN_SDK=10.0.16299.0"
IF "%WINDOWS_VERSION%" == "10" SET "OVERRIDE_WIN_SDK=10.0.17134.0"

MSBUILD "%BOLT_CORE_DIR%\BoltCore.sln" /p:Configuration=Release;WindowsTargetPlatformVersion="%OVERRIDE_WIN_SDK%" || goto :error

:::::::::::::::
:: Clean & create deploy dir
:Repeat
RMDIR /s /q "%BOLT_WIN_DIR%\BoltCore_Deployed\"
IF EXIST "%BOLT_WIN_DIR%\BoltCore_Deployed\" goto :Repeat
chgcolor %CTEXT%
ECHO old deployment was cleaned
MKDIR "%BOLT_WIN_DIR%\BoltCore_Deployed\"
ECHO "%BOLT_WIN_DIR%\BoltCore_Deployed\"

:::::::::::::::
:: Copy Files
COPY "%BOLT_CORE_DIR%\x64\Release\BoltCore.exe" "%BOLT_WIN_DIR%\BoltCore_Deployed\BoltCore.exe"
COPY "%BOLT_CORE_DIR%\x64\Release\openal32.dll" "%BOLT_WIN_DIR%\BoltCore_Deployed\openal32.dll"
CALL "cp_resources.bat" "%BOLT_WIN_DIR%\BoltCore_Deployed"

:::::::::::::::
:: Copy Python STD lib files
call:checkMakeDir "%BOLT_WIN_DIR%\BoltCore_Deployed\Lib\"
XCOPY /e /h /y "%EXTLIBS_DIR%\Custom-Minimal-Static-Safe-cpython\Lib" "%BOLT_WIN_DIR%\BoltCore_Deployed\Lib\"

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

