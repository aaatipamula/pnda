#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <any>

enum TokenType {
  // groupings
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, 

  // special characters
  PLUS, MINUS, STAR, FORWARD_SLASH, DOT, COMMA, SEMICOLON,

  // logical operators
  EXCLAMATION, EXCLAMATION_EQUAL, EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,

  // data types
  STRING, NUM, IDENTIFIER,

  // keywords (TRU = TRUE, FALS = FALSE)
  AND, OR, IF, ELSE, TRU, FALS, PRINT, RETURN, 
  FOR, WHILE, VAR, FUNC, SUPER, SELF, CLASS, NIL,

  // EOF
  EF
};

std::string typeToString(TokenType type);

class Token{
  TokenType _type;
  std::any _literal;
  std::string _lexeme;
  int _line;

  public: 
    Token(TokenType type, std::any literal, std::string lexeme, int line);
    std::string toString();
};

#endif
