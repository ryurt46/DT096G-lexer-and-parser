#ifndef LEXER_H
#define LEXER_H
#include <string>

using it = std::string::iterator;

enum Token {
    OPEN_GROUP,      // '('
    CLOSE_GROUP,     // ')'
    OR,              // '+'
    REPEAT,          // '*'
    ANY_CHAR,        // '.'
    OPEN_COUNT,      // '{'
    CLOSE_COUNT,     // '}'
    IGNORE_CASE,     // '\I'
    OUTPUT_GROUP,    // '\O'
    NUMBER,          // A sequence of digits
    WORD,            // A sequence of characters that forms a word
    END_OF_FILE,     // Special token to represent the end of the input
    INVALID          // Special token to represent an invalid or unrecognized token
};

class Lexer{
public:
    Lexer() = default;
    Token lexing(it& first, it last);
};

#endif
