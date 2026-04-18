#ifndef MYLANGUAGE_EXPR_H
#define MYLANGUAGE_EXPR_H
#include "Token.h"
#include <any>
#include <memory>

namespace MyLanguage
{

    class Binary;
    class Unary;
    class Literal;
    class Grouping;

    template <typename R> class Visitor
    {
      public:
        virtual R visitBinary(const Binary &expr) = 0;
        virtual R visitUnary(const Unary &expr) = 0;
        virtual R visitLiteral(const Literal &expr) = 0;
        virtual R visitGrouping(const Grouping &expr) = 0;
        virtual ~Visitor() = default;
    };

    class Expr
    {
      public:
        virtual ~Expr() = default;
        virtual std::string accept(Visitor<std::string> &visitor) = 0;
    };

    class Binary : public Expr // sirve para mostrar como es la estructura de
                               // una clase binary
    {
      public:
        std::unique_ptr<Expr> left;
        Token op;
        std::unique_ptr<Expr> right;

        /*se ocupan punteros para demarcar que ahi puede caber otra clase ero el
         * compilador sabe de que tamaño hacerlo*/
        Binary(std::unique_ptr<Expr> left, Token op,
               std::unique_ptr<Expr> right)
            : left(std::move(left)), op(op), right(std::move(right))
        {
        }

        // implementacion del temaplate accept utilizando visitor
        std::string accept(Visitor<std::string> &visitor) override
        {
            return visitor.visitBinary(*this);
        }
    };

    class Unary : public Expr
    {
      public:
        Token op;
        std::unique_ptr<Expr> right;

        Unary(Token op, std::unique_ptr<Expr> right)
            : op(op), right(std::move(right))
        {
        }

        std::string accept(Visitor<std::string> &visitor) override
        {
            return visitor.visitUnary(*this);
        }
    };

    class Literal : public Expr
    {
      public:
        std::any value;

        Literal(std::any value) : value(std::move(value)) {}

        std::string accept(Visitor<std::string> &visitor) override
        {
            return visitor.visitLiteral(*this);
        }
    };

    class Grouping : public Expr
    {
      public:
        std::unique_ptr<Expr> expression;

        Grouping(std::unique_ptr<Expr> expression)
            : expression(std::move(expression))
        {
        }

        std::string accept(Visitor<std::string> &visitor) override
        {
            return visitor.visitGrouping(*this);
        }
    };
} // namespace MyLanguage
#endif