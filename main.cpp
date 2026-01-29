#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

#include "vyne/compiler/lexer/lexer.h"
#include "vyne/compiler/parser/parser.h"
#include "vyne/compiler/ast/ast.h"
#include "vyne/compiler/ast/value.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

int main(int argc, char* argv[]) {
    SymbolContainer env;
    env["global"] = {};
    
    uint32_t piId = StringPool::instance().intern("pi");
    env["global"][piId] = Value(3.14159);

    std::string input;

    if (argc > 1) {
        std::string filename = argv[1];

        size_t dotPos = filename.find_last_of(".");
        if (dotPos == std::string::npos || filename.substr(dotPos + 1) != "vy") {
            std::cerr << RED << "Error: File must end in .vy" << RESET << "\n";
            return 1;
        }

        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << RED << "Could not open file: " << filename << RESET << "\n";
            return 1;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        const std::string& content = buffer.str();

        try {
            auto tokens = tokenize(content);
            Parser parser(tokens);
            
            auto start = std::chrono::high_resolution_clock::now();
            while (parser.peekToken().type != TokenType::End) {
                auto ast = parser.parseStatement();
                if (ast) {
                    try {
                        ast->evaluate(env);
                    } catch (const ReturnException&) {
                        break; 
                    }
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> ms = end - start;
            std::cout << GREEN << "\nExecution finished in: " << ms.count() << "ms" << RESET << std::endl;
        } catch (const std::exception& e) {
            std::cerr << RED << "Runtime/Compilation Error: " << e.what() << RESET << "\n";
        }

        return 0;
    }

    // --- REPL MODE ---
    std::cout << BOLD << CYAN << "Vyne Interpreter v1.0 (ID-Optimized)" << RESET << "\n";
    std::cout << "Type " << RED << "exit" << RESET << " to quit.\n\n";

    while (true) {
        std::cout << GREEN << ">> " << RESET;
        if (!std::getline(std::cin, input)) break;

        if (input == "exit") break;
        if (input.empty()) continue;

        if (input == "view tree") {
            std::cout << YELLOW << "--- Current Symbol env ---" << RESET << "\n";
            bool hasAnyVariables = false;

            for (const auto& [groupName, table] : env) {
                for (const auto& [varId, val] : table) {
                    hasAnyVariables = true;
                    
                    std::string realName = StringPool::instance().get(varId);

                    if (groupName == "global") {
                        std::cout << BOLD << realName << RESET << " = ";
                    } else {
                        std::cout << CYAN << groupName << RESET << "." << BOLD << realName << RESET << " = ";
                    }

                    val.print(std::cout);
                    std::cout << "\n";
                }
            }

            if (!hasAnyVariables) {
                std::cout << "(no variables defined)" << "\n";
            }
            std::cout << YELLOW << "-----------------------------" << RESET << "\n";
            continue;
        }

        try {
            auto tokens = tokenize(input);
            Parser parser(tokens);

            auto root = parser.parseStatement();
            if (root) {
                Value result;
                try {
                    result = root->evaluate(env); 
                } 
                catch (const ReturnException& e) {
                    result = e.value; 
                }

                if (result.getType() != Value::NONE) { 
                    result.print(std::cout);
                    std::cout << "\n";
                }
            }
        }
        catch (const std::exception& e) {
            std::cerr << RED << "Error: " << e.what() << RESET << "\n";
        }
    }

    return 0;
}