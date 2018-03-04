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

cd %~dp0
call copyDLLs.bat

echo /////////%0 done