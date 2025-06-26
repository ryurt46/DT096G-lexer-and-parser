#ifndef LEXER_H
#define LEXER_H
#include <cctype>
#include <string>

using it = std::string::iterator;

enum Token { LPAREN, RPAREN, OR, GREEDY, ANY, LBRACE, RBRACE, DIGIT, CHAR, END, INVALID };
class Lexer {
public:
    Lexer() = default;
    Token lexer(it &first, const it last);
};

#endif
