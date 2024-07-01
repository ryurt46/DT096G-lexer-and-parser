# lexer-and-parser (regex-exp)

## Grammar
```
<match>    := <expr>
<expr>     := <subexpr>
<subexpr>  := <or> | <multiple> | <group> | <any> | <count> | <ignore> | <word>
<or>       := <expr> '+' <expr>
<multiple> := <expr> '*'
<group>    := '(' <expr> ')'
<any>      := '.'
<count>    := <expr> '{' <number> '}'
<ignore>   := <expr> '\I'
<word>     := [char] [<word>]
<number>   := [0-9]+
<char>     := [a-zA-Z]

```
