@echo off

if not exist build (
    mkdir build
    cmake -S . -B build -G "Visual Studio 17 2022" -A x64
)

cmake --build build --config Debug
if errorlevel 1 exit /b %errorlevel%

copy /Y "build\Debug\sse.exe" "sse.exe" >nul

echo.
echo Build Successful.
echo Executable copied to: %CD%\sse.exe