:::::::::::::::
:: FULL_CLEAN.BAT
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

CALL "%BOLT_WIN_TOOLS_PREBUILD_DIR%\_clean_res_hash.bat"
call:checkRmDir "%BOLT_WIN_DIR%\BoltEditor_Deployed"
call:checkRmDir "%BOLT_WIN_DIR%\BoltCore_Deployed"
call:checkRmDir "%BOLT_EDITOR_DIR%\x64"
call:checkRmDir "%BOLT_EDITOR_DIR%\.vs"
call:checkRmDir "%BOLT_EDITOR_DIR%\GeneratedFiles"
call:checkRmDir "%BOLT_EDITOR_DIR%\Lib"
call:checkRmDir "%BOLT_EDITOR_DIR%\resources"
call:checkRmDir "%BOLT_CORE_DIR%\x64"
call:checkRmDir "%BOLT_CORE_DIR%\.vs"
call:checkRmDir "%BOLT_CORE_DIR%\GeneratedFiles"
call:checkRmDir "%BOLT_CORE_DIR%\Lib"
call:checkRmDir "%BOLT_CORE_DIR%\resources"

DEL "%BOLT_EDITOR_DIR%\BoltEditor.vcxproj.user"
DEL ""%BOLT_CORE_DIR%\BoltCore.vcxproj.user"
GOTO :success

:::::::::::::::
:: Dir processing
:checkRmDir
:Repeat
RMDIR /s /q "%~1\"
IF EXIST "%~1\" goto :Repeat
chgcolor %CTEXT%
ECHO "%~1\" was cleaned
goto:EOF
:: Return

:::::::::::::::
:error
chgcolor %CERROR%   
ECHO %0: ERROR
ECHO //////////
chgcolor %CRESET%
PAUSE
EXIT /B 1

:::::::::::::::
:success
chgcolor %CSUCCESS%
ECHO %0: SUCCESS
ECHO //////////
chgcolor %CRESET%
PAUSE
EXIT /B 0

