#ifndef _PNDA_TOKEN_H
#define _PNDA_TOKEN_H

typedef enum _token_type {
  // End of File
  EOL = 258,

  // Grouping Characters
  LEFT_PAREN, RIGHT_PAREN, 
  LEFT_BRACE, RIGHT_BRACE, 

  // Special Characters
  DOT, COMMA, SEMICOLON,

  // Arethmetic Operators
  PLUS, MINUS, STAR, FORWARD_SLASH, 

  // Comparison Operators
  LESS, LESS_EQUAL,
  GREATER, GREATER_EQUAL, 
  EQUAL_EQUAL, BANG_EQUAL, 

  // Logical Operators
  BANG, L_AND, L_OR,

  // Binary Operators
  AND, OR, XOR, 

  // Binds
  IDENTIFIER, EQUAL,

  // Data Types
  INT, FLOAT, CHAR, 
  
  // Concrete types
  INT_T, FLOAT_T, CHAR_T, BOOL_T,

  // Keywords
  IF, ELSE, TRUE, FALSE, 
  /* FOR, WHILE, */
  FUNC, RETURN, LET, APP,
} token_type;

/* Convert tokens to string representations and vice versa */
char* type_to_str(token_type tok);
token_type match_keyword(const char *str);

#endif

