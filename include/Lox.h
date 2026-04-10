#ifndef MYLANGUAGE_LOX_H
#define MYLANGUAGE_LOX_H
#include <string>

namespace MyLanguage
{
    class Lox
    {
      public:
        static void runFile(const std::string &path);
        static void runPrompt();
        static void run(const std::string &source);
        static void error(int line, const std::string &message);

      private:
        static void report(int line, const std::string &where,
                           const std::string &message);
        static bool handError;
    };
} // namespace MyLanguage

#endif