#include "lexer.h"
#include <cctype>

Token Lexer::lexer(it& first, it last){
   while(std::isspace(*first) && first != last){
        first++;
    }
    if(first == last){
        return Token::END;
    }
    if(std::isdigit(*first)){
        ++first;
        return Token::DIGIT;
    }
    if(std::isalpha(*first)){
        ++first;
        return Token::CHAR;
    }
    switch (*first) {
        case '+':
            ++first;
            return Token::OR;
        case '*':
            ++first;
            return Token::GREEDY;
        case '.':
            ++first;
            return Token::ANY;
        case '(':
            ++first;
            return Token::LPAREN;
        case ')':
            ++first;
            return Token::RPAREN;
        case '{':
            ++first;
            return Token::LBRACE;
        case '}':
            ++first;
            return Token::RBRACE;
        case '\\':
            ++first;
            if (first != last) {
                if (*first == 'I') {
                    ++first;
                    return Token::IGNORE;
                } else if (*first == 'O') {
                    ++first;
                    if (first != last && *first == '{') {
                        ++first;
                        while (first != last && std::isdigit(*first)) {
                            ++first;
                        }
                        if (first != last && *first == '}') {
                            ++first;
                            return Token::OUTPUT;
                        }
                    }
                }
            }
            return Token::INVALID;
        default:
            ++first;
            return Token::INVALID;
    } 
}
