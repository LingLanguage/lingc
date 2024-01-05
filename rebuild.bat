@echo off
@REM delete if exist .\bin
if exist .\bin rmdir /s /q .\bin
@REM delete if exist .\build
if exist .\build rmdir /s /q .\build

call build.bat
@echo on