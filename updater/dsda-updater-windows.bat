@ECHO OFF
setlocal

set REPO=kraflab/dsda-doom

set "DEST=%~dp0"
if not "%~1"=="" (
    if "%~2"=="" (
        set "DEST=%~f1"
    ) else (
        :: Older launchers pass an unquoted path as multiple arguments
        set "DEST=%*"
    )
)
set "DEST=%DEST:/=\%"
if "%DEST:~-1%"=="\" set "DEST=%DEST:~0,-1%"
echo Destination folder is "%DEST%"

:: Get latest version
for /f %%i in ('powershell -NoProfile -command "(Invoke-WebRequest https://api.github.com/repos/%REPO%/releases | ConvertFrom-Json)[0].tag_name"') do set "TAG=%%i"
if errorlevel 1 goto :fail

echo Latest dsda-doom version is %TAG%
set "VERSION=%TAG:~1%"

:: File name
set "v_win64=dsda-doom-%VERSION%-win-x64"

set "TMPDIR=%temp%\dsda-doom-temp"
mkdir "%TMPDIR%" 2>nul

:: Download zip
echo Downloading latest release
powershell -NoProfile -Command "Invoke-WebRequest -OutFile '%TMPDIR%\%v_win64%.zip' -Uri 'https://github.com/%REPO%/releases/download/%TAG%/%v_win64%.zip'"
if errorlevel 1 goto :fail
if not exist "%TMPDIR%\%v_win64%.zip" goto :fail

:: Extract zip
echo Extracting files
powershell -NoProfile -Command "Expand-Archive -Force '%TMPDIR%\%v_win64%.zip' '%TMPDIR%'"
if errorlevel 1 goto :fail

:: Copy to destination folder
echo Copying files to destination
robocopy "%TMPDIR%\%v_win64%" "%DEST%" * /nfl /ndl /njh /njs /nc /ns /np
set "RC=%ERRORLEVEL%"
if %RC% GEQ 8 goto :fail

:: Delete downloaded files without deleting this running batch file.
if exist "%TMPDIR%\%v_win64%.zip" del /q "%TMPDIR%\%v_win64%.zip" >nul 2>&1
if exist "%TMPDIR%\%v_win64%" rmdir /s /q "%TMPDIR%\%v_win64%" >nul 2>&1

echo dsda-doom %VERSION% has been installed successfully!
echo.
powershell -NoProfile -Command "for ($seconds = 10; $seconds -gt 0; $seconds--) { [Console]::Write([char]13); Write-Host -NoNewline ('Closing in {0} seconds. Press any key to close now... ' -f $seconds); for ($tick = 0; $tick -lt 10; $tick++) { if ([Console]::KeyAvailable) { [void][Console]::ReadKey($true); exit }; Start-Sleep -Milliseconds 100 } }"
exit 0

:: Failure? - do pause
:fail
echo.
echo Update failed.
echo.

pause
exit /b 1
