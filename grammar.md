### Current state of the Ske Language Grammar

```
<program>               ::= <fun-decl>

<fun-decl>		::= pub fn IDENTIFIER()
			|   fn IDENTIFIER() <compound-statement>

<compound-statement>	::= { }
			|   { <statement-list> }

<statement-list>	::= <statement>
			|   <statement-list> <statement>

<statement>		::= <expression-statement>

<expression-statement>	::= ;
			|   <expression> ;

<expression>            ::= <binary-expression>
                        |   <unary-expression>
                        |   <constant-expression>

<binary-expression>     ::= <expression> <binary-operator> <expression>

<binary-operator>       ::= +
                        |   -
                        |   *
                        |   /

<unary-expression>      ::= <unary-operator> <expression>

<unary-operator>        ::= -
                        |   +

<constant-expression>   ::= <constant>

<constant>              ::= <integer-constant>
```
