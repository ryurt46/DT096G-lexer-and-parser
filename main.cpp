#include "parser.h"
#include <iostream>
#include <string>

// └──
void printTree(const std::string &prefix, ASTNode *node, bool isLeft) {
        if (!node)
                return;

        std::cout << prefix << (isLeft ? "|--" : "└─") << node->id() << '\n';

        for (size_t i = 0; i < node->children.size(); ++i)
                printTree(prefix + (isLeft ? "|   " : "    "),
                          node->children[i], i < node->children.size() - 1);
}
void printTree(ASTNode *node) { printTree("", node, false); }

int main(int argc, char *argv[]) {
        if (argc < 2) {
                std::cerr << "Usage: match <pattern> < input.txt>\n";
                return EXIT_FAILURE;
        }

        std::string pattern = argv[1];
        std::string input;
        std::getline(std::cin, input);

        it patFirst = pattern.begin();
        it patLast = pattern.end();
        Parser parser(patFirst, patLast);
        Match *root = parser.getMatch();
        if (!root) {
                std::cerr << "Parsing failed.\n";
                return EXIT_FAILURE;
        }

        ASTNode *patternNode =
            root->children.empty() ? nullptr : root->children[0];

        it matchBeg = input.end();
        it matchEnd = input.end();
        bool found = false;

        if (patternNode) {
                for (it start = input.begin(); start != input.end() && !found;
                     ++start) {
                        it tmpStart = start;
                        it tmpEnd = input.end();
                        if (patternNode->evaluate(tmpStart, tmpEnd)) {
                                matchBeg = start;
                                matchEnd = tmpStart;
                                found = true;
                        }
                }
        }

        if (found) {
                std::string matched(matchBeg, matchEnd);
                std::cout << "Match found: " << matched << '\n';
                std::cout << "|__\n";
                printTree(root);
                return EXIT_SUCCESS;
        } else {
                std::cout << "No match.\n";
                return EXIT_FAILURE;
        }
}
