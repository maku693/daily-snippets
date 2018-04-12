// (+ 1 2)
// (+ . (1 . (2 . ())))
//
// <s_expr> ::= <atom> | <pair> | <list>
// <atom>   ::= <empty> | <letter>
// <empty>  ::= "" | " "
// <letter> ::= "a" | "b" | ... | "z"
// <pair>   ::= "(" <s_expr> "." <s_expr> ")"
// <list>   ::= "(" <s_expr> ")" | "(" <s_expr> <empty> <s_expr> ")"

function s_expr() {}
function atom() {}
function pair() {}
function list() {}

