@echo OFF

PUSHD %~dp0\..\
CALL Scripts\premake\premake5.exe vs2022
POPD

PAUSE