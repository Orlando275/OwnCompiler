#include "AstPrinter.h"
#include "Token.h"
#include <memory>

std::string MyLanguage::AstPrinter::print(Expr &expr)
{
    return expr.accept(*this);
}

std::string MyLanguage::AstPrinter::visitBinary(const Binary &expr)
{
    return parenthesize(expr.op.lexeme, {expr.left.get(), expr.right.get()});
}

std::string MyLanguage::AstPrinter::visitGrouping(const Grouping &expr)
{
    return parenthesize("group", {expr.expression.get()});
}

std::string MyLanguage::AstPrinter::visitLiteral(const Literal &expr)
{
    if (!expr.value.has_value())
        return "nil";
    if (auto *d = std::any_cast<double>(&expr.value))
        return std::to_string(*d);
    if (auto *s = std::any_cast<std::string>(&expr.value))
        return *s;
    if (auto *b = std::any_cast<bool>(&expr.value))
        return *b ? "true" : "false";
    return "nil";
}

std::string MyLanguage::AstPrinter::visitUnary(const Unary &expr)
{
    return parenthesize(expr.op.lexeme, {expr.right.get()});
}
