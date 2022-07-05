@echo off
pushd ..\
call tools\premake\premake5.exe vs2022
popd
PAUSE