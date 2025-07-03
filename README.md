# lexer-and-parser (Regex-like Pattern Matcher)

A simple C++ project implementing a recursive-descent parser for a custom regular-expression grammar. \
Lab 1 of the *Theory of Programming Languages* [DT096G](https://www.miun.se/en/education/show-syllabus/DT096G/ATLAS_K27011/) course at Mid Sweden University.

## Grammar
```
<match>    := <expr>
<expr>     := <subexpr> [<expr>]
<subexpr>  := <group> | <or> | <word> | <any>
<group>    := '(' <expr> ')'
<or>       := <word> '+' <word>
<word>     := <term> [<word>]
<term>     := <count> | <greedy> | <char>
<count>    := <char> '{' <digit> '}' | <any> '{' <digit> '}'
<greedy>   := <char> '*' | <any> '*'
<char>     := [a-zA-Z]
<digit>    := [0-9]
<any>      := '.'
```

## Usage
To run the program use: `./match "(love+hate)" < input.txt`
