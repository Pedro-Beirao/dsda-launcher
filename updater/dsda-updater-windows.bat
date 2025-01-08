@ECHO OFF

set REPO=kraflab/dsda-doom

set DEST="%~dp0"
if not [%1]==[] set DEST="%1"
echo Destination folder is %DEST%

:: Get latest version
for /f %%i in ('powershell -command "(Invoke-WebRequest https://api.github.com/repos/%REPO%/releases | ConvertFrom-Json)[0].tag_name"') do set TAG=%%i
echo Latest dsda-doom version is %TAG%
set VERSION=%TAG:~1%

:: File name
set v_win64=dsda-doom-%VERSION%-win64

mkdir "%temp%\dsda-doom-temp"

:: Download zip
echo Downloading latest release
powershell -command "Invoke-WebRequest -OutFile \"%temp%\dsda-doom-temp\%v_win64%.zip\" -Uri https://github.com/%REPO%/releases/download/%TAG%/%v_win64%.zip"

:: Extract zip
if exist "%temp%\dsda-doom-temp\%v_win64%.zip" (
  echo Extracting files
  powershell -command "Expand-Archive -Force \"%temp%\dsda-doom-temp\%v_win64%.zip\" \"%temp%\dsda-doom-temp\""
) else (
  echo "Error downloading update"
  del /q "%temp%\dsda-doom-temp\%v_win64%.zip"
  rmdir /s /q "%temp%\dsda-doom-temp\%v_win64%"
  pause
  exit
)

:: Copy to destination folder
echo Copying files to destination
robocopy "%temp%\dsda-doom-temp\%v_win64%" "%DEST%" * /nfl /ndl /njh /njs /nc /ns /np

:: Delete temp files
del /q "%temp%\dsda-doom-temp\%v_win64%.zip"
rmdir /s /q "%temp%\dsda-doom-temp\%v_win64%"

echo dsda-doom %VERSION% has been installed succesfully!

pause
exit
