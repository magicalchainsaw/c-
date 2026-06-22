@echo off
setlocal

set "SCRIPT_DIR=%~dp0"
set "WORK_DIR=%SCRIPT_DIR%实训"
set "EXE_PATH=%SCRIPT_DIR%x64\Release\实训.exe"

if not exist "%EXE_PATH%" (
    echo Release executable not found:
    echo %EXE_PATH%
    pause
    exit /b 1
)

pushd "%WORK_DIR%" >nul
start "" "%EXE_PATH%"
popd >nul

endlocal
