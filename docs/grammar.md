# Borno Programming Language

## Formal Grammar (BNF)

### Program

<program> ::= <statement_list>

<statement_list> ::= <statement> <statement_list>
| ε

### Statement

<statement> ::= <declaration>
| <assignment>
| <if_statement>
| <while_statement>
| <print_statement>
| <block>

### Declaration

<declaration> ::= <type> <identifier> "=" <expression> ";"

<type> ::= "সংখ্যা"
| "দশমিক"
| "লেখা"

### Assignment

<assignment> ::= <identifier> "=" <expression> ";"

### If-Else Statement

<if_statement> ::= "যদি" "(" <expression> ")" <block>
<else_part>

<else_part> ::= "নাহলে" <block>
| ε

### While Statement

<while_statement> ::= "যতক্ষণ" "(" <expression> ")" <block>

### Print Statement

<print_statement> ::= "দেখাও" "(" <expression> ")" ";"

### Block

<block> ::= "{" <statement_list> "}"

### Expression

<expression> ::= <term> <comparison_part>

<comparison_part> ::= ">" <term>
| "<" <term>
| "==" <term>
| ε

### Term

<term> ::= <factor> <term_tail>

<term_tail> ::= "+" <factor> <term_tail>
| "-" <factor> <term_tail>
| ε

### Factor

<factor> ::= <primary> <factor_tail>

<factor_tail> ::= "\*" <primary> <factor_tail>
| "/" <primary> <factor_tail>
| ε

### Primary

<primary> ::= <number>
| <string>
| <identifier>
| "(" <expression> ")"

### Lexical Elements

<identifier> ::= valid Bangla or English identifier

<number> ::= integer
| decimal

<string> ::= '"' characters '"'
