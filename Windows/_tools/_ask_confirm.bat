:::::::::::::::
:: _ASK_CONFIRM.BAT
:::::::::::::::
@ECHO OFF
:::::::::::::::
:: Fast Init
CALL "%~dp0_initboltshell.bat"
:::::::::::::::
:: NO HEADER
:::::::::::::::
:: NO ENV
:::::::::::::::

:::::::::::::::
:: Ask User Before Continue

IF DEFINED SILENT_ASK ( 
    goto:EOF
)

:ask
chgcolor %CRESET%
SET CHOICE=
SET /p CHOICE=Do you want to proceed? [Y/N]: 
IF NOT '%CHOICE%'=='' SET choice=%choice:~0,1%
IF '%CHOICE%'=='Y' EXIT /B 0 REM EXIT WITH ERROR
IF '%CHOICE%'=='y' EXIT /B 0 REM EXIT WITH ERROR
IF '%CHOICE%'=='N' EXIT /B 1 REM EXIT WITH SUCCESS
IF '%CHOICE%'=='n' EXIT /B 1 REM EXIT WITH SUCCESS
:: Override Enable Enter Skip
::IF '%CHOICE%'=='' EXIT /B 0
ECHO "%CHOICE%" is not valid
ECHO.
GOTO :ask

