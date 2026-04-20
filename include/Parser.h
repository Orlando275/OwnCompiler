

#include "TokenType.h"
#ifndef MYLANGUAGE_PARSER_H
#include "Expr.h"
#include "Token.h"
#include <vector>

namespace MyLanguage
{
    class Parser
    {
      private:
        std::vector<Token> tokens;
        int current = 0;
        std::shared_ptr<Expr> expression();
        std::shared_ptr<Expr> equality();

        bool match(std::initializer_list<TokenType> types);
        bool check(TokenType type);

        Token advance();
        bool isAtEnd();
        Token peek();
        Token previous();

      public:
        Parser(std::vector<Token> tokens);
    };
} // namespace MyLanguage

#endif