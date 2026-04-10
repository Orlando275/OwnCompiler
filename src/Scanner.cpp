#include "Scanner.h"

#include "Lox.h"
/*constructor con member initializer list se utiliza porque source fue declarado
const=final para quue no fuera modificado por lo que se debe inicializar antes
de que inicie la funcion
----  move transfiere la info del buffer a la variable source es mas eficiente
que copiar*/
MyLanguage::Scanner::Scanner(std::string source) : source(std::move(source)) {}

/*hasmap con todas las keywords and their TokeType*/
const std::unordered_map<std::string, MyLanguage::TokenType>
    MyLanguage::Scanner::keywords = {
        {"and", TokenType::AND},       {"class", TokenType::CLASS},
        {"else", TokenType::ELSE},     {"false", TokenType::FALSE},
        {"for", TokenType::FOR},       {"fun", TokenType::FUN},
        {"if", TokenType::IF},         {"nil", TokenType::NIL},
        {"or", TokenType::OR},         {"print", TokenType::PRINT},
        {"return", TokenType::RETURN}, {"super", TokenType::SUPER},
        {"this", TokenType::THIS},     {"true", TokenType::TRUE},
        {"var", TokenType::VAR},       {"while", TokenType::WHILE},
};

bool MyLanguage::Scanner::isAtEnd() // si current se pasa de la longitud de
                                    // esta shit cierra el bucle principal de
                                    // scanTokens()
{
    return current >= source.length();
}

std::vector<MyLanguage::Token> MyLanguage::Scanner::scanTokens() {
    while (!isAtEnd()) // mientras siga sin encontrar el final sigue funcionando
    {
        start = current; // mueve el pointer al siguiente token o sea el start
        scanToken();     // metodo para ir a crer tokens
    }
    // una ves termina se agrega el final del documento y se retorna la lista de
    // tokens creados
    tokens.push_back(MyLanguage::Token(MyLanguage::TokenType::END_OF_FILE, "",
                                       std::any{}, line));

    return tokens;
}
// lee el caracter actual y aumenta en 1 siempre
char MyLanguage::Scanner::advance() { return source[current++]; }

/*estas dos funciones se llaman overload que cargan un token a la lista una ves
 * que ya se tiene su tipo se extrae el texto y se añade al vector*/
void MyLanguage::Scanner::addToken(MyLanguage::TokenType type) {
    addToken(type, std::any{});
}
void MyLanguage::Scanner::addToken(MyLanguage::TokenType type,
                                   std::any literal) {
    std::string text = source.substr(start, current - start);
    tokens.push_back(MyLanguage::Token(
        type, text, literal,
        line)); // text abarca todo el contenido del toker, si no tiene
                // literalpara a estar vacio y line e que linea
}
// encuentra si el siguiente char es una pareja deseada
bool MyLanguage::Scanner::match(char expected) {
    if (isAtEnd())
        return false;
    if (source[current] != expected)
        return false;
    current++;
    return true;
}
// permite revisar el siguiente char
char MyLanguage::Scanner::peek() {
    if (isAtEnd())
        return '\0';
    return source[current];
}
// permite revisar los proximos dos caracteres adelante
char MyLanguage::Scanner::peekNext() {
    if (current + 1 >= source.length())
        return '\0';
    return source[current + 1];
}
/*
checa strings hasta que encutnre "" si hay salto de linea sigue checando
*/
void MyLanguage::Scanner::string() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n')
            line++;
        advance();
    }
    // si llega al final y aun no cierra da error
    if (isAtEnd()) {
        MyLanguage::Lox::error(line, "Unterminated string.");
        return;
    }
    advance(); // avanza hasta "
    std::string value = source.substr(
        start + 1,
        current - 1 - start); // no contempla las comillas por eso +1 y -1
    addToken(TokenType::STRING, value); // agrega el token sin las comillas
}

void MyLanguage::Scanner::number() {
    while (isDigit(peek())) // checa si es el actual es un numero si si avanza
        advance();
    if (peek() == '.' && isDigit(peekNext())) // si llega a un punto y el
                                              // siguiente es un numero sigue
    {
        advance();
        while (isDigit(peek())) // checa todos los numeros siguientes y aumenta
            advance();
    }
    addToken(TokenType::NUMBER,
             std::stod(source.substr(start, current - start)));
}

void MyLanguage::Scanner::identifier() {
    while (isAlphaNumeric(peek()))
        advance();
    std::string text = source.substr(start, current - start);
    auto it =
        keywords.find(text); // busca si existe el texto de todo lo alfanumerico
    TokenType type =
        (it != keywords.end()) ? it->second : TokenType::IDENTIFIER;
    addToken(type);
}
bool MyLanguage::Scanner::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}
bool MyLanguage::Scanner::isDigit(char c) { return c >= '0' && c <= '9'; }
bool MyLanguage::Scanner::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}

void MyLanguage::Scanner::scanToken() {
    char c = advance(); // current avanza uno pero lee el anterior
    switch (c)          // lee n posicion y current ya esta en n+1
    {
    case '(':
        addToken(TokenType::LEFT_PAREN);
        break;
    case ')':
        addToken(TokenType::RIGHT_PAREN);
        break;
    case '{':
        addToken(TokenType::LEFT_BRACE);
        break;
    case '}':
        addToken(TokenType::RIGHT_BRACE);
        break;
    case ',':
        addToken(TokenType::COMMA);
        break;
    case '.':
        addToken(TokenType::DOT);
        break;
    case '-':
        addToken(TokenType::MINUS);
        break;
    case '+':
        addToken(TokenType::PLUS);
        break;
    case ';':
        addToken(TokenType::SEMICOLON);
        break;
    case '*':
        addToken(TokenType::STAR);
        break;
    case '!':
        addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
        break;
    case '=':
        addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
        break;
    case '<':
        addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
        break;
    case '>':
        addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        break;
    case '/':
        if (match('/')) {
            while (peek() != '\n' && !isAtEnd()) {
                advance();
            }
        } else if (match('*')) {
            while (!(peek() == '*' && peekNext() == '/') && !isAtEnd()) {
                if (peek() == '\n')
                    line++;

                advance();
            }
            if (isAtEnd()) {
                MyLanguage::Lox::error(line, "Unterminated block comment. ");
                break;
            }
            advance();
        }

        else {
            addToken(TokenType::SLASH);
        }

        break;
    case ' ':
    case '\t':
    case '\r':
        break;
    case '\n':
        line++;
        break;
    case '"':
        string();
        break;
    default:
        if (isDigit(c)) {
            number();
        } else if (isAlpha(c)) {
            identifier();
        }

        else {
            MyLanguage::Lox::error(line, "Unexpected character. ");
        }

        break;
    }
}
