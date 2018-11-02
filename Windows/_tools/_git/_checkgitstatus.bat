:::::::::::::::
:: _CHECKGITSTATUS.BAT
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
:: Init Bolt Dev Env Variables
CALL _initboltenv.bat || goto :error
:::::::::::::::

:::::::::::::::
:: Backup
PUSHD "%CD%"

:::::::::::::::
:: CD To Bolt Repository Root
CD %BOLT_DIR%

:::::::::::::::
:: Checking Git Status
FOR /F "tokens=* USEBACKQ" %%F IN (`git status --porcelain`) DO SET GITSTATUS=%%F

:::::::::::::::
:: Handling Status Cases
IF "%GITSTATUS%" NEQ "" (
    REM There are modifications
    chgcolor %CTEXT%
    ECHO Warning ! You have uncommitted changes in the repository.
    chgcolor %CGIT%
    git status --porcelain
    chgcolor %CTEXT%
    ECHO You might want to stash your changes before issuing any kind of operations here.
    GOTO ask
) ELSE (
    REM The repo is Clean
    chgcolor %CTEXT%
    ECHO No change detected in repository, proceeding.
    GOTO proceed
)

:::::::::::::::
:: Ask User Before Continue
:ask
CALL _ask_confirm.bat || goto :error

:::::::::::::::
:: Proceeding Execution
:proceed

:::::::::::::::
:: Reaching End of the Script
GOTO :success

:::::::::::::::
:error
POPD
chgcolor %CERROR%
ECHO %0: ERROR
ECHO //////////
chgcolor %CRESET%
EXIT /B 1

:::::::::::::::
:success
POPD
chgcolor %CSUCCESS%
ECHO %0: SUCCESS
ECHO //////////
chgcolor %CRESET%
EXIT /B 0

