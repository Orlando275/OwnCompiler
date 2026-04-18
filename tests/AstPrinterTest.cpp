#include "AstPrinter.h"
#include "Token.h"
#include <iostream>

int main()
{
    using namespace MyLanguage;
    auto expression = std::make_unique<Binary>(
        std::make_unique<Unary>(Token(TokenType::MINUS, "-", std::any{}, 1),
                                std::make_unique<Literal>(123.0)),
        Token(TokenType::STAR, "*", std::any{}, 1),
        std::make_unique<Grouping>(std::make_unique<Literal>(45.67)));

    AstPrinter printer;
    std::cout << printer.print(*expression) << std::endl;
    return 0;
}