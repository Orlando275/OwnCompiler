#ifndef MYLANGUAGE_SCANNER_H
#define MYLANGUAGE_SCANNER_H
#include "Token.h"
#include "TokenType.h"
#include <cstdio>
#include <string>
#include <unordered_map>
#include <vector>

namespace MyLanguage
{
    class Scanner
    {
      private:
        const std::string source;
        std::vector<Token> tokens;
        int start = 0;
        int current = 0;
        int line = 1;
        bool isAtEnd();
        void scanToken();
        char advance();
        void addToken(TokenType type);
        void addToken(TokenType type, std::any literal);
        bool match(char expected);
        char peek();
        void string();
        bool isDigit(char c);
        void number();
        char peekNext();
        void identifier();
        bool isAlpha(char c);
        bool isAlphaNumeric(char c);
        static const std::unordered_map<std::string, TokenType>
            keywords; // el static es para que sea independientemente a las
                      // instancias si 10 scanners son creados solo hay un map

      public: // es publico lo que se requiere que otra clase utilice se llamada
              // encapsulamiento
        Scanner(std::string source);
        std::vector<Token> scanTokens();
    };
} // namespace MyLanguage
#endif