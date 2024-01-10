@echo off
call build.bat
lingc.exe -i samples\import
lingc.exe -i samples\static_func
@echo on