#include "parser.h"
#include "node.h"

Parser::Parser(it &first, it &last) : first(first), last(last), match(parseMatch()) {}

Match *Parser::parseMatch() {
    Expr *expr = parseExpr();
    if (!expr)
        return nullptr;
    Match *m = new Match();
    m->addChild(expr);
    return m;
}

Expr *Parser::parseExpr() {
    Expr *expr = new Expr();
    while (true) {
        auto backup = first;
        SubExpr *sub = parseSubExpr();
        if (!sub) {
            first = backup;
            break;
        }
        expr->addChild(sub);
    }
    return expr;
}

SubExpr *Parser::parseSubExpr() {
    auto backup = first;

    Group *group = parseGroup();
    if (group) {
        SubExpr *s = new SubExpr();
        s->addChild(group);
        return s;
    }

    Or *orNode = parseOr();
    if (orNode) {
        SubExpr *s = new SubExpr();
        s->addChild(orNode);
        return s;
    }

    Word *word = parseWord();
    if (word) {
        SubExpr *s = new SubExpr();
        s->addChild(word);
        return s;
    }

    Any *any = parseAny();
    if (any) {
        SubExpr *s = new SubExpr();
        s->addChild(any);
        return s;
    }

    first = backup;
    return nullptr;
}

Group *Parser::parseGroup() {
    auto backup = first;
    if (lexer.lexer(first, last) != LPAREN) {
        first = backup;
        return nullptr;
    }

    Expr *expr = parseExpr();
    if (!expr) {
        first = backup;
        return nullptr;
    }

    if (lexer.lexer(first, last) != RPAREN) {
        first = backup;
        return nullptr;
    }

    Group *g = new Group();
    g->addChild(expr);
    return g;
}

Word *Parser::parseWord() {
    Word *word = new Word();

    while (true) {
        auto backup = first;
        ASTNode *term = parseTerm();
        if (!term) {
            first = backup;
            break;
        }
        word->addChild(term);
    }

    return word->children.empty() ? nullptr : word;
}

ASTNode *Parser::parseTerm() {
    auto backup = first;

    Count *count = parseCount();
    if (count)
        return count;

    Greedy *greedy = parseGreedy();
    if (greedy)
        return greedy;

    Char *ch = parseChar();
    if (ch)
        return ch;

    first = backup;
    return nullptr;
}

Count *Parser::parseCount() {
    auto backup = first;
    Token tok = lexer.lexer(first, last);

    if (tok != CHAR && tok != ANY) {
        first = backup;
        return nullptr;
    }

    char c = *(first - 1); // symbolen vi ska upprepa
    if (lexer.lexer(first, last) != LBRACE) {
        first = backup;
        return nullptr;
    }

    if (lexer.lexer(first, last) != DIGIT) {
        first = backup;
        return nullptr;
    }

    char digit = *(first - 1);
    if (lexer.lexer(first, last) != RBRACE) {
        first = backup;
        return nullptr;
    }

    Count *count = new Count();
    count->count = digit - '0';
    if (tok == CHAR) {
        Char *ch = new Char();
        ch->c = c;
        count->addChild(ch);
    } else {
        count->addChild(new Any());
    }
    return count;
}

Greedy *Parser::parseGreedy() {
    auto backup = first;
    Token tok = lexer.lexer(first, last);
    if (tok != CHAR && tok != ANY) {
        first = backup;
        return nullptr;
    }

    char c = *(first - 1);
    if (lexer.lexer(first, last) != GREEDY) {
        first = backup;
        return nullptr;
    }

    Greedy *g = new Greedy();
    if (tok == CHAR) {
        Char *ch = new Char();
        ch->c = c;
        g->addChild(ch);
    } else {
        g->addChild(new Any());
    }
    return g;
}

Char *Parser::parseChar() {
    auto backup = first;
    if (lexer.lexer(first, last) != CHAR) {
        first = backup;
        return nullptr;
    }
    Char *ch = new Char();
    ch->c = *(first - 1);
    return ch;
}

Any *Parser::parseAny() {
    auto backup = first;
    if (lexer.lexer(first, last) != ANY) {
        first = backup;
        return nullptr;
    }
    return new Any();
}

Or *Parser::parseOr() {
    auto backup = first;

    Word *left = parseWord();
    if (!left) {
        first = backup;
        return nullptr;
    }

    if (lexer.lexer(first, last) != OR) {
        first = backup;
        return nullptr;
    }

    Word *right = parseWord();
    if (!right) {
        first = backup;
        return nullptr;
    }

    Or *orNode = new Or();
    orNode->addChild(left);
    orNode->addChild(right);
    return orNode;
}
