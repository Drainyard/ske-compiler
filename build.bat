@echo off

WHERE cl
IF %ERRORLEVEL% NEQ 0 call %VCVARSALL% x64

set BUILD_DIR=build
set EXECUTABLE_NAME=__ske

setlocal ENABLEDELAYEDEXPANSION

set CommonCompilerFlags=/MD -fp:fast -fp:except- -nologo /Od -Oi -W4 -Gm- -GR- -EHa- -FC -Z7 /Fe%EXECUTABLE_NAME%
set CommonLinkerFlags=shell32.lib kernel32.lib
set ExtraLinkerFlags=/NODEFAULTLIB:"LIBCMT" -incremental:no -opt:ref

IF NOT EXIST %BUILD_DIR% mkdir %BUILD_DIR%
pushd %BUILD_DIR%

del *.pdb > NUL 2> NUL

echo Compilation started on: %time%
cl %CommonCompilerFlags% ..\src\main.c /link %ExtraLinkerFlags% %CommonLinkerFlags%

echo Compilation finished on: %time%

popd %BUILD_DIR%
