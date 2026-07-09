@echo off

if not exist build (
    mkdir build
    cmake -S . -B build
)

cmake --build build --config Debug
if errorlevel 1 exit /b %errorlevel%

copy /Y "build\Debug\SSE.exe" "SSE.exe" >nul

echo.
echo Build Successful.
echo Executable copied to: %CD%\SSE.exe