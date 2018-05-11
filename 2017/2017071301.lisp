(atom (quote 1))
; -> T
(atom (quote nil))
; -> T
(atom (quote (cons 1 2)))
; -> false
(atom '(1 . 2))
; -> false

; open parenthesis
; symbol atom
; quote
; open parenthesis
; number literal 1
; dot
; number literal 2
; closing parenthesis
; closing parenthesis
