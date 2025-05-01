#ifndef PARSER_H
#define PARSER_H
#include "node.h"

class Parser {
      public:
        Parser(it &first, it &last);
        Match *getMatch() const { return match; }

      private:
        Match *parseMatch();
        Expr *parseExpr();
        SubExpr *parseSubExpr();
        Or *parseOr();
        Group *parseGroup();
        Word *parseWord();
        ASTNode *parseTerm();
        Count *parseCount();
        Greedy *parseGreedy();
        Char *parseChar();
        Any *parseAny();

        // members
        it &first;
        it &last;
        Lexer lexer;
        Match *match;
};

#endif
