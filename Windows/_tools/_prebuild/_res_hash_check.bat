:::::::::::::::
:: _RES_HASH_CHECK.BAT
:::::::::::::::
@ECHO OFF
:::::::::::::::
:: Fast Init
CALL "%~dp0..\_initboltshell.bat"
:::::::::::::::
chgcolor %CHEADER%
ECHO //////////
ECHO %0: START
:::::::::::::::
:: Init Bolt Dev Env Variables
CALL _initboltenv.bat || goto :error
:::::::::::::::

chgcolor %CRESET%
set "LAST_CHECKSUM="
IF EXIST "%~dp0reschecksum.txt" (
for /f "delims=" %%a in ('type "%~dp0reschecksum.txt"') do (
SET LAST_CHECKSUM=%%a
GOTO :break1
)
)

:break1
SET BREAK_PLACEHOLDER_STATEMENT=

DirHash %BOLT_RESOURCES_DIR% SHA256 -t "%~dp0reschecksum.txt" -overwrite -quiet -nowait -hashnames
set "NEW_CHECKSUM="
for /f "delims=" %%a in ('type "%~dp0reschecksum.txt"') do (
SET NEW_CHECKSUM=%%a
GOTO :break2
)

:break2
SET BREAK_PLACEHOLDER_STATEMENT=

ECHO %LAST_CHECKSUM%
ECHO %NEW_CHECKSUM%

SET "CHANGE_DETECTED="
chgcolor %CTEXT%
IF "%LAST_CHECKSUM%"=="%NEW_CHECKSUM%" (
    ECHO SAME
    SET "CHANGE_DETECTED=0"
) ELSE (
    ECHO DIFF
    SET "CHANGE_DETECTED=1"
)

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

