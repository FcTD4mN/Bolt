:::::::::::::::
:: CP_RESOURCES.BAT
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
:: Check Extlibs Libraries
chgcolor %CTEXT%
ECHO Copy Resources Task

:::::::::::::::
:: Arg processing
IF [%1]==[] (
    chgcolor %CERROR%
    ECHO %0: ERROR
    ECHO You need to pass outdir path as first param
    goto :error
)

SET PREBUILD_OUTDIR=%1
set PREBUILD_OUTDIR=%PREBUILD_OUTDIR:"=%
:::::::::::::::
:: Cleaning Install
:Repeat
RMDIR /s /q "%PREBUILD_OUTDIR%\resources\"
IF EXIST "%PREBUILD_OUTDIR%\resources\" goto :Repeat
chgcolor %CTEXT%
ECHO old resources at output location were cleaned
MKDIR "%PREBUILD_OUTDIR%\resources"
ECHO "%PREBUILD_OUTDIR%\resources"
XCOPY /e /h /y "%BOLT_DIR%\resources" "%PREBUILD_OUTDIR%\resources"
:::::::::::::::
:: Reaching End of the Script
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

