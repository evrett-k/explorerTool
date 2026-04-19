@echo off
setlocal

net session >nul 2>&1
if not "%errorlevel%"=="0" (
	echo Requesting administrator privileges...
	powershell -NoProfile -ExecutionPolicy Bypass -Command "Start-Process -FilePath '%ComSpec%' -ArgumentList '/k ""%~f0"" elevated' -Verb RunAs"
	exit /b
)

cd /d "%~dp0"

if not exist "%~dp0ExplorerBgTool.dll" (
	echo [ERROR] ExplorerBgTool.dll not found in:
	echo %~dp0
	echo.
	pause
	exit /b 1
)

echo Unregistering ExplorerBgTool.dll...
"%SystemRoot%\System32\regsvr32.exe" /u "%~dp0ExplorerBgTool.dll"
if errorlevel 1 (
	echo [ERROR] Unregister failed.
	pause
	exit /b 1
)

echo Restarting Explorer...
taskkill /f /im explorer.exe >nul 2>&1
start explorer.exe

echo The DLL may still be locked by another process.
echo If you cannot delete it, restart Windows and try again.
pause