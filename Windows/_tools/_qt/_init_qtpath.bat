:::::::::::::::
:: _INIT_QTPATH.BAT
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
:: CHECK IF EXIST IN ENV & VALID
IF DEFINED QTDIR (
    set "MOC_PATH=%QTDIR%\bin\moc.exe"
    dir %MOC_PATH% > nul
    IF %ERRORLEVEL%==0 (
        chgcolor %CTEXT%
        echo Valid Qt Path red from env
        echo SAVING PATH FOR FUTURE REUSE
        echo %QTDIR%>"%~dp0qtpath.txt"
        goto :success
    )
)

:::::::::::::::
:: NORMAL START HERE
:: FWD DECL
set "QT_PATH="

:::::::::::::::
:: Looking for value in text file
IF EXIST "%~dp0qtpath.txt" (

for /f "delims=" %%a in ('type "%~dp0qtpath.txt"') do (
SET QT_PATH=%%a
GOTO :break
)

:break
SET BREAK_PLACEHOLDER_STATEMENT=

:::::::::::::::
:: Set MOC path for checking purposes
set "MOC_PATH=%QT_PATH%\bin\moc.exe"

:::::::::::::::
:: Check if valid
dir %MOC_PATH% > nul
IF %ERRORLEVEL%==0 (
chgcolor %CTEXT%
echo Valid Qt Path red from qtpath.txt
goto :success
) ELSE (
chgcolor %CERROR%
echo Invalid Qt Path in qtpath.txt
call "%~dp0_ask_qtpath.bat" || goto :error
goto :success
)
) ELSE (
chgcolor %CTEXT%
echo First time launch ? Cannot find qtpath.txt
call "%~dp0_ask_qtpath.bat" || goto :error
goto :success
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

