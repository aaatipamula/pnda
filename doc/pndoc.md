# Pndoc

This is a document describing the philosophy and reasoning behind the syntax of the Pnda language. 

# Syntax/Structure

Pnda is a [curly brace language](https://en.wiktionary.org/wiki/curly-bracket_language). While I appreciate Python's emphasis on newlines and tab spacing for code readability, I've found it annoying to work with at times. Especially with the inconsistent handling of tabs/spaces in many code editors. This also allows for Pnda to be reduced to as few characters as possible, if required for any reason.

## Data Types

| Type | Syntax | Notes |
| --- | --- | --- |
| Bool | `true`, `false` | I didn't particularly enjoy that Python treated boolean values as proper nouns. |
| Integer | `1234` | Integers are converted to floats at intepretation time. TODO: Integers ending with a dot (`1234.`) are not yet supported. |
| Float | `.1234` or `12.34` | Should work like any other float. |
| String | `"Hello World!"` | Strings must be double quoted. |
| Character | `'c'`| Characters must be single quoted. TODO: Only single characters are accepted for now, escape sequence support will be added. |

## Arithmetic Operators

**I plan on adding support for the mod operator as well as most of the assignment operators found in python.**

| Operator | Syntax | Notes |
| --- | --- | --- |
| Addition | `+` | Works for integers. TODO: Support for string contatenation should be added. |
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

## Logical Operators

| Operator | Syntax | Notes |
| --- | --- | --- |
| Inverse | `!` | Easier than reaching for the `~` key. |
| AND | `and` | |
| OR | `or`| |

## Misc. Operators/Expressions

| Operator | Syntax | Notes |
| --- | --- | --- |
| Grouping | `()` | Standard to group items/expressions. |
| Output | `print()` | Print is treated like a command here. |

## Variable Assignment

Variables are *dynamically typed*. I also plan on eventually adding support for constant variable declarations as I occasionally find them useful. 

```js
var myVar = "hello";

```

## Loops

**For Loop**:

I'm also thinking of adding support for a `for in ` loop similar to Python. This may come in a style similar to C++.

```js
for (var a = 1; a < 0; a = a + 1) {
  print(a);
}
```

**While Loop**:

```js
while (a < 10) {
  print("true");
}
```

## Functions

I considered not even including a keyword for function declarations, however after some consideration I decided that the convention of having a function declaration keyword was much more common than not. I will consider eventually adding support for [arrow functions](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Functions/Arrow_functions) similar to JavaScript.

I didn't want to type out the entire word `function` but also didn't like the use of `def` in Python. I settled for func.

```js
func add(a, b){
  return a + b;
}
```

## Classes

I wanted my language to have support for both functional and OOP paradigms. Classes also support inheritance.

```java
class baseClass {
  init(a, b) {
    self.a = a;
    self.b = b;
  }

  out() {
    print(a + " " + b);
  }
}

class superClass(baseClass) {
  init(a, b, c) {
    super.init(a, b);
    self.c = c;
  }
}
```

