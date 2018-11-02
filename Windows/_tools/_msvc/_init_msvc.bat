:::::::::::::::
:: _INIT_MSVC.BAT
:::::::::::::::
@ECHO OFF
:::::::::::::::
:: Init Shell
CALL "%~dp0..\_initboltshell.bat"
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
:: Init MSVC Dev Env Variables

where /q MSBUILD
IF ERRORLEVEL 1 (
    GOTO :proceed
) ELSE (
    chgcolor %CTEXT%
    ECHO MSBUILD env already initialized.
    GOTO :success
)

:proceed
PUSHD "%CD%"
chgcolor %CMSVC%
CALL "%MSVC_VCVARS_DIR%\vcvars64.bat" || goto :error
POPD

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

