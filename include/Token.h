#ifndef MYLANGUAGE_TOKEN_H
#define MYLANGUAGE_TOKEN_H
#include "TokenType.h"
#include <any>
#include <string>

namespace MyLanguage
{
    class Token
    {
      private:
      public:
        const MyLanguage::TokenType type;
        const std::string lexeme;
        const std::any literal;
        const int line;

        Token(MyLanguage::TokenType type, std::string lexeme, std::any literal,
              int line)
            : type(type), lexeme(std::move(lexeme)),
              literal(std::move(literal)), line(line)
        {
        }

        std::string
        toString() const // lo mismo no se modifica nada en este metodo
        {
            return std::to_string(static_cast<int>(type)) + " " + lexeme;
        }
    };
} // namespace MyLanguage
#endif