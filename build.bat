@echo off

clang -std=c2x -o test.exe tests/test.c
if %errorlevel% neq 0 (
    echo Build failed.
    exit /b 1
)
test.exe %*