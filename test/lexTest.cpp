#include <iostream>
#include <string>
#include "lexer.h"

void printToken(Token token) {
    switch (token) {
        case Token::LPAREN:
            std::cout << "Token: LPAREN\n";
            break;
        case Token::RPAREN:
            std::cout << "Token: RPAREN\n";
            break;
        case Token::OR:
            std::cout << "Token: OR\n";
            break;
        case Token::GREEDY:
            std::cout << "Token: GREEDY\n";
            break;
        case Token::ANY:
            std::cout << "Token: ANY\n";
            break;
        case Token::LBRACE:
            std::cout << "Token: LBRACE\n";
            break;
        case Token::RBRACE:
            std::cout << "Token: RBRACE\n";
            break;
        case Token::IGNORE:
            std::cout << "Token: IGNORE\n";
            break;
        case Token::OUTPUT:
            std::cout << "Token: OUTPUT\n";
            break;
        case Token::DIGIT:
            std::cout << "Token: DIGIT\n";
            break;
        case Token::CHAR:
            std::cout << "Token: CHAR\n";
            break;
        case Token::END:
            std::cout << "Token: END\n";
            break;
        case Token::INVALID:
            std::cout << "Token: INVALID\n";
            break;
        default:
            break;
    }
}

int main() {
    std::string input;
    std::cout << "Enter input for lexer: ";
    std::getline(std::cin, input);

    Lexer lexer;
    it first = input.begin();
    it last = input.end();
    Token token;

    while ((token = lexer.lexer(first, last)) != Token::END) {
        printToken(token);
    }

    return 0;
}

