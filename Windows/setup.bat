@echo off
echo /////////%0 start

cd %~dp0
cd ../
set "SETUP_ROOT=%cd%"

git submodule init
git submodule update
cd BoltExtlibs
git submodule init
git submodule update
cd _install/windows/tools
call build_extlibs.bat
git checkout master

cd %SETUP_ROOT%

set "IN_RELEASE64_DIR=%SETUP_ROOT%\BoltExtlibs\_build\windows\bin\release64"
set "IN_DEBUG64_DIR=%SETUP_ROOT%\BoltExtlibs\_build\windows\bin\debug64"
set "OUT_RELEASE64_DIR=%SETUP_ROOT%\Windows\BoltCore-VS2017\BoltCore\x64\Release"
set "OUT_DEBUG64_DIR=%SETUP_ROOT%\Windows\BoltCore-VS2017\BoltCore\x64\Debug"
mkdir "%OUT_RELEASE64_DIR%"
mkdir "%OUT_DEBUG64_DIR%"
xcopy /s /e /h /y "%IN_RELEASE64_DIR%" "%OUT_RELEASE64_DIR%"
xcopy /s /e /h /y "%IN_DEBUG64_DIR%" "%OUT_DEBUG64_DIR%"

rmdir /s /q %SETUP_ROOT%\SFML\_build
rmdir /s /q %SETUP_ROOT%\tinyxml2\_build

echo /////////%0 done