@REM mkdir if not exist .\build
if not exist .\build mkdir .\build
gcc -o .\build\main.o -c .\src\main.c

if not exist .\bin mkdir .\bin
gcc -o .\bin\lingc.exe .\build\main.o .\lib\win_64\raylib.dll

copy .\lib\win_64\raylib.dll .\bin\raylib.dll

@echo Build Done!