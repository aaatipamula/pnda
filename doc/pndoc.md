# Pndoc

> NOTE: This document is currently under construction. It is subject to change.

This document goes over a few important things about the **pnda** programming language.

# Motivation

I started this project out of curiosity. I really just wanted to know how programming languages work under the hood, so I just jumped right in to making one. After doing some preliminary research and writing some code however, I realized I don't even know what I want out of my programming language.

What language features do I like, how do I want my language to be evaluated? I got lost in trying to figure out what my language should look like. So I hung up the project, not sure how to procede.

My interest in programming languages didn't disappear however, and I eventually ended up taking a course on programming languages at my university. The professor for the class was amazing, he was a treasure trove of knowledge, and through his course my passion for programming lanauges was reignited.

So we get to where I am now. I've decided to rewrite the language in C, which may become my downfall, but I've come to enjoy programming in C after many of my classes require I do so. I've also decided to rewrite the document to include more than just the concrete syntax. I want to include evaluation semantics and be more rigorous about how the language is defined as a whole. The rest of the document exists to satisfy this goal.

# Concrete Syntax

The concrete syntax for **pnda** is fairly simple. I've seperated expressions into different categories based on the types of values they operate over.

> NOTE: The grammar is left-recursive

```
prog          -> decl*
decl          -> let_stmt | fn_stmt | expr ';'
let_stmt      -> 'let' IDENTIFIER '=' (expr | fn_stmt) ';'
fn_stmt       -> concrete_type 'fn' '(' fn_params? ')' block
fn_params     -> arg (',' arg)*
arg           -> IDENTIFIER concrete_type
concrete_type -> 'int' | 'float' | 'char' | 'bool'
block         -> '{' decl* '}'

expr          -> if_expr
if_expr       -> 'if' '(' equality_expr ')' equality_expr 'else' equality_expr
equality_expr -> compare_expr (('!=' | '==') compare_expr)*
compare_expr  -> binary_expr (('>' | '>=' | '<' | '<=') binary_expr)*
binary_expr   -> lor_expr ('&&' lor_expr)*
lor_expr      -> areth_expr ('||' areth_expr)*
areth_expr    -> fact_expr (('+' | '-') fact_expr)*
fact_expr     -> bwise_expr (('*' | '/') bwise_expr)*
bwise_expr    -> unary_expr (('&' | '|' | '^') unary_expr)*
unary_expr    -> ('-' | '!') unary_expr | app
app           -> expr_val ( '(' arguments? ')' )*
expr_val      -> base_type | IDENTIFIER | '(' expr ')'
base_type     -> TRUE | FALSE | INT | FLOAT | CHAR
arguments     -> expr (',' expr)*
```

# Evaluation Semantics

TBD...

# Reference & Notes

Pnda is a [curly brace language](https://en.wiktionary.org/wiki/curly-bracket_language). I appreciate the flexibility in code style that curly brace languages provide. It's a standard for many languages and most people are comfortable writing in that code style.

## Data Types

| Type | Syntax | Notes |
| ---  | --- | --- |
| Bool | `true`, `false` | I didn't particularly enjoy that Python treated boolean values as proper nouns. |
| Integer | `1234` | Integers are converted to floats at intepretation time. |
| Float | `.1234` or `12.34` | Should work like any other float. |
| Character | `'c'`| Characters must be single quoted. |

## Arithmetic Operators

**I plan on adding support for the mod operator as well as unary increment and decrement operators.**

| Operator | Syntax | Notes |
| --- | --- | --- |
| Addition | `+` | Works for integers. |
| Subtraction/Negation | `-` | |
| Multiplication | `*` | |
| Division | `/` | |

## Comparison Operators

| Operator | Syntax | Notes |
| --- | --- | --- |
| Less Than | `<` | |
| Less Than or Equal To | `<=` | |
| Greater Than | `>` | |
| Greater Than or Equal To | `>=` | |
| Not Equal To | `!=` | |

## Logical Operators

| Operator | Syntax | Notes |
| --- | --- | --- |
| Inverse | `!` | Easier than reaching for the `~` key. |
| AND | `&&` | |
| OR | `\|\|` | |

## Binary Operators

| Operator | Syntax | Notes |
| --- | --- | --- |
| AND | `&` | |
| OR | `\|` | |
| XOR | `^` | |

## Variable Assignment

Variables are *statically typed*. I also plan on eventually adding support for constant variable declarations as I occasionally find them useful. 

```rust
let myVar = 1234;

```
## Functions

Functions are anonymous and higher order, meaning they are values. Function arguments must be typed.

```rust
fn (a int, b int) {
  return a + b;
}
```

They can also be assigned to an identifier.

```rust
fn sub(a int, b int) { 
  return a - b;
}
```

## TODO

### Loops

**For Loop**:

```js
for (var a=1; a<0; a=a+1) {
}
```

**While Loop**:

```rust
while (a < 10) {
  print("true");
}
```
