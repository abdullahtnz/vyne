@echo off
g++ -std=c++17 main.cpp vyne/lexer/lexer.cpp vyne/parser/parser.cpp vyne/ast/ast.cpp -o tf-compiler.exe -Wall -Wextra
if %errorlevel% neq 0 (
    echo Build Failed!
    pause
) else (
    echo Build Successful: tf-compiler.exe created.
)
