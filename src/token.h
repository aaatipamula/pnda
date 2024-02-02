#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <any>

enum TokenType {
  // Grouping Characters
  LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, 

  // Special Characters
  PLUS, MINUS, STAR, FORWARD_SLASH, DOT, COMMA, SEMICOLON,

  // Logical Operators
  EXCLAMATION, EXCLAMATION_EQUAL, EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,

  // Data Types
  STRING, NUM, CHAR, IDENTIFIER,

  // Keywords
  AND, OR, IF, ELSE, _TRUE, _FALSE, PRINT, RETURN, 
  FOR, WHILE, VAR, FUNC, SUPER, SELF, CLASS, _NULL,

  // End of File
  _EOF
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
