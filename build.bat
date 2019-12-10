@ECHO off

set PROJECT_PATH=%cd%

set MINGW_PATH=%PROJECT_PATH%\Tools\windows\mingw64

set PATH=%PATH%;%MINGW_PATH%\bin
set PATH=%PATH%;%MINGW_PATH%\bin\gcc.exe
set PATH=%PATH%;%MINGW_PATH%\x86_64-w64-mingw32\bin

mingw32-make -f Makefile
