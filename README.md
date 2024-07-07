# lexer-and-parser (regex-exp)

## Grammar
```
<match>    := <expr>
<expr>     := <subexpr> [<expr>]
<subexpr>  := <or> | <group> | <word> | <any> | <ignore>
<or>       := <word> '+' <word>
<group>    := '(' <expr> ')'
<word>     := <term> [<word>]
<term>     := <count> | <greedy> | <char>
<count>    := <char> '{' <digit> '}' | <any> '{' <digit> '}'
<greedy>   := <char> '*' | <any> '*'
<char>     := [a-zA-Z]
<digit>    := [0-9]
<any>      := '.'
<ignore>   := <expr> '\I'
<output>   := <expr> '\O{' <digit> '}'
```
