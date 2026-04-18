#include "Lox.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
bool MyLanguage::Lox::handError = false;

void MyLanguage::Lox::run(const std::string &source)
{
    // Scanner scanner(source);
    // std::vector<Token> tokens = scanner.scanTokens();
    // for (Token& token : tokens) {
    //     std::cout << token.toString() << "\n";
    // }
    std::cout << source << '\n';
}

void MyLanguage::Lox::runPrompt() // REPL read eval prompt loop esto es
                                  // itneractivo cuando no se da un archivo e
                                  // interactuas con interprete
{
    std::string line;
    for (;;)
    {
        std::cout << "> ";
        if (!std::getline(std::cin, line))
            break;
        MyLanguage::Lox::run(line);
        handError = false;
    }
}

void MyLanguage::Lox::runFile(const std::string &path)
{
    std::ifstream file(path);
    if (!file)
        throw std::runtime_error("Could not open file: " + path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    run(buffer.str());
    if (handError)
        exit(65);
}

void MyLanguage::Lox::error(int line, const std::string &message)
{
    report(line, "", message);
}

void MyLanguage::Lox::report(int line, const std::string &where,
                             const std::string &message)
{
    std::cerr << "[line " << line << "] Error" << where << ": " << message
              << '\n';
    handError = true;
}

int main(int argc, char **argv)
{

    if (argc > 2)
    {
        std::cout << "Usage: jlox [script]\n";
        return 64; // salida del sistema
    }
    else if (argc == 2) // coportamiento distinto de java... en c++ incluye
                        // nombre del programa
    {
        try
        {
            MyLanguage::Lox::runFile(argv[1]);
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << e.what() << '\n';
            return 74;
        }
    }
    else
    {
        MyLanguage::Lox::runPrompt();
    }
}
