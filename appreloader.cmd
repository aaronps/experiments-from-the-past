@echo off
setlocal
set scriptfile=%~f0
escript.exe "%scriptfile:.cmd=%" %*