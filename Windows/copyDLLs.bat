@echo off
echo /////////%0 start

cd %~dp0
cd ../
set "SETUP_ROOT=%cd%"
cd %SETUP_ROOT%

set "IN_RELEASE64_DIR=%SETUP_ROOT%\BoltExtlibs\_build\windows\bin\release64"
set "IN_DEBUG64_DIR=%SETUP_ROOT%\BoltExtlibs\_build\windows\bin\debug64"
set "OUT_RELEASE64_DIR=%SETUP_ROOT%\Windows\BoltCore-VS2017\BoltCore\x64\Release"
set "OUT_DEBUG64_DIR=%SETUP_ROOT%\Windows\BoltCore-VS2017\BoltCore\x64\Debug"\
set "OUT_CONSOLEDEBUG64_DIR=%SETUP_ROOT%\Windows\BoltCore-VS2017\BoltCore\x64\ConsoleDebug"\
mkdir "%OUT_RELEASE64_DIR%"
mkdir "%OUT_DEBUG64_DIR%"
mkdir "%OUT_CONSOLEDEBUG64_DIR%"
xcopy /s /e /h /y "%IN_RELEASE64_DIR%" "%OUT_RELEASE64_DIR%"
xcopy /s /e /h /y "%IN_DEBUG64_DIR%" "%OUT_DEBUG64_DIR%"
xcopy /s /e /h /y "%IN_DEBUG64_DIR%" "%OUT_CONSOLEDEBUG64_DIR%"

taskkill /F /IM vctip.exe
rmdir /s /q %SETUP_ROOT%\SFML\_build
rmdir /s /q %SETUP_ROOT%\tinyxml2\_build

mkdir "%SETUP_ROOT%/Windows/BoltCore-VS2017/BoltCore/Lib"
xcopy /s /e /h /y "%SETUP_ROOT%/BoltExtlibs/cpython/Lib" "%SETUP_ROOT%/Windows/BoltCore-VS2017/BoltCore/Lib"

echo /////////%0 done