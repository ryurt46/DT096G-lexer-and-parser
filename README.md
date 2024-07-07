# lexer-and-parser (regex-exp)

## Grammar
```
<!-- <match>    := <expr>
<expr>     := <subexpr>
<subexpr>  := <or> | <multiple> | <group> | <any> | <count> | <ignore> | <word>
<or>       := <expr> '+' <expr>
<multiple> := <expr> '*'
<group>    := '(' <expr> ')'
<any>      := '.'
<count>    := <expr> '{' <digit> '}'
<ignore>   := <expr> '\I'
<word>     := [char] [<word>]
<digit>    := [0-9]+
<char>     := [a-zA-Z]
-->
<match>    := <expr>
<expr>     := <subexpr> [<subexpr>]
<subexpr>  := <or> | <group> | <count> | <word>
<or>       := <word> '+' <word> 
<group>    := '(' <expr> ')'
<word>     := <term> [<word>]
<term>     := <count> | <greedy> | <char>
<count>    := <char> '{' <digit> '}' | <any> '{' <digit> '}'
<greedy>   := <char> <'*'> | <any>
<char>     := [a-zA-Z]
<digit>    := [0-9]
<any>      := '.'
```
