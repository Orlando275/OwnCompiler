#ifndef MYLANGUAGE_ASTPRINTER_H
#define MYLANGUAGE_ASTPRINTER_H
#include "Expr.h"
#include <string>
#include <vector>

namespace MyLanguage
{
    class AstPrinter : public Visitor<std::string>
    {

      public:
        std::string print(Expr &expr);
        std::string visitBinary(const Binary &expr) override;
        std::string visitGrouping(const Grouping &expr) override;
        std::string visitLiteral(const Literal &expr) override;
        std::string visitUnary(const Unary &expr) override;

      private:
        std::string parenthesize(const std::string &name,
                                 std::vector<Expr *> exprs)
        {
            std::string result = "(" + name;
            for (auto *expr : exprs)
            {
                result += " ";
                result += expr->accept(*this);
            }
            result += ")";
            return result;
        }
    };

} // namespace MyLanguage

#endif