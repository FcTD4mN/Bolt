:::::::::::::::
:: _ASK_QTPATH.BAT
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

:::::::::::::::
:: Display Info
chgcolor %CTEXT%
echo Enter the path to the Qt installation folder for the platform you are compiling on and want to target.
echo Example: "D:\Qt\5.10.1\msvc2017_64"
echo Prefere backslash '\' and use double quotes "" if the path has spaces in it

:::::::::::::::
:: Ask User
chgcolor %CRESET%
set /p QT_PATH=":"

:::::::::::::::
:: Set MOC path for checking purposes
set "MOC_PATH=%QT_PATH%\bin\moc.exe"

:::::::::::::::
:: Check if valid
dir %MOC_PATH% > nul
IF %ERRORLEVEL%==0 (
chgcolor %CSUCCESS%
echo Success: \bin\moc.exe found in input path, valid Qt directory.
REM SAVING PATH FOR FUTURE REUSE
echo %QT_PATH%>"%~dp0qtpath.txt"
GOTO :success
) ELSE (
chgcolor %CERROR%    
echo Error: \bin\moc.exe not found in input path, invalid Qt directory.
GOTO :error
)

:::::::::::::::
:: Reaching End of the Script
GOTO :error

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

