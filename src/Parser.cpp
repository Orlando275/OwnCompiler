#include "Parser.h"
#include "Expr.h"
#include "Token.h"
#include "TokenType.h"
#include <vector>
MyLanguage::Parser::Parser(std::vector<MyLanguage::Token> tokens)
    : tokens(std::move(tokens)) {};

std::shared_ptr<MyLanguage::Expr> MyLanguage::Parser::expression()
{
    return equality();
}

std::shared_ptr<MyLanguage::Expr> MyLanguage::Parser::equality()
{
    auto expr = comparison();
    while (match({
        TokenType::BANG_EQUAL,
        TokenType::EQUAL_EQUAL,
    }))
    {
        Token op = previous();
        auto right = comparison();
        expr = std::make_shared<Binary>(expr, op, right);
    }
    return expr;
}

bool MyLanguage::Parser::match(std::initializer_list<TokenType> types)
{
    for (auto type : types)
    {
        if (check(type))
        {
            advance();
            return true;
        }
    }
    return false;
}

bool MyLanguage::Parser::check(TokenType type)
{
    if (isAtEnd())
        return false;
    return peek().type == type;
}

MyLanguage::Token MyLanguage::Parser::advance()
{
    if (!isAtEnd())
        current++;
    return previous();
}

bool MyLanguage::Parser::isAtEnd()
{
    return peek().type == TokenType::END_OF_FILE;
}

MyLanguage::Token MyLanguage::Parser::peek() { return tokens[current]; }

MyLanguage::Token MyLanguage::Parser::previous() { return tokens[current - 1]; }