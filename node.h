#ifndef NODE_H
#define NODE_H
#include "lexer.h"
#include <iostream>
#include <vector>

struct ASTNode {
        virtual bool evaluate(it &first, it &last) = 0;
        std::vector<ASTNode *> children;
        virtual ~ASTNode() = default;
        void addChild(ASTNode *child) {
                if (child != nullptr) {
                        children.push_back(child);
                }
        }
};

struct Any : ASTNode {
        bool evaluate(it &first, it &last) override {
                if (first == last)
                        return false;
                ++first;
                return true;
        }
};

// "a{3}" → CHAR, LBRACE, DIGIT, RBRACE
struct Char : ASTNode {
        char c;
        bool evaluate(it &first, it &last) override {
                if (first == last)
                        return false;
                if (*first == c) {
                        ++first;
                        return true;
                }
                return false;
        }
};

struct Count : ASTNode {
        int count;
        bool evaluate(it &first, it &last) override {
                auto original = first;
                for (int i = 0; i < count; ++i) {
                        if (!children[0]->evaluate(first, last)) {
                                first = original;
                                return false;
                        }
                }
                return true;
        }
};

struct Greedy : ASTNode {
        bool evaluate(it &first, it &last) override {
                it latestMatch = first;

                while (children[0]->evaluate(first, last)) {
                        latestMatch = first;
                }

                first = latestMatch;
                return true;
        }
};

struct Group : ASTNode {
        bool evaluate(it &first, it &last) {
                return children[0]->evaluate(first, last);
        }
};

struct Or : ASTNode {
        bool evaluate(it &first, it &last) override {
                auto original = first;
                if (children[0]->evaluate(first, last)) {
                        return true;
                }
                first = original;
                return children[1]->evaluate(first, last);
        }
};

struct Word : ASTNode {
        bool evaluate(it &first, it &last) override {
                auto original = first;
                for (auto &child : children) {
                        if (!child->evaluate(first, last)) {
                                first = original;
                                return false;
                        }
                }
                return true;
        }
};

struct Expr : ASTNode {
        bool evaluate(it &first, it &last) override {
                auto original = first;
                for (auto &child : children) {
                        if (!child->evaluate(first, last)) {
                                first = original;
                                return false;
                        }
                }
                return true;
        }
};

struct SubExpr : ASTNode {
        bool evaluate(it &first, it &last) override {
                return children[0]->evaluate(first, last);
        }
};

struct Match : ASTNode {
        bool evaluate(it &first, it &last) override {
                while (first != last) {
                        it temp = first;
                        if (children[0]->evaluate(temp, last)) {
                                first = temp;
                                return true;
                        }
                        ++first;
                }
                return false;
        }
};
#endif
