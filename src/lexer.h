#ifndef LEXER_H
#define LEXER_H

#include <list>
#include <string>
#include <unordered_map>

#include "token.h"

class Lexer {
  int curr, start = 0;
  int line = 1;

  const std::unordered_map<std::string, TokenType> _keywords = {
    {"and", AND},
    {"or", OR},
    {"if", IF},
    {"else", ELSE},
    {"true", TRU},
    {"false", FALS},
    {"print", PRINT},
    {"return", RETURN},
    {"for", FOR},
    {"while", WHILE},
    {"var", VAR},
    {"func", FUNC},
    {"super", SUPER},
    {"self", SELF},
    {"class", CLASS},
    {"null", NIL}
  };

  bool atEnd();
  bool find(char ch);
  bool isDigit(char ch);
  bool isAlpha(char ch);
  bool isAlphaNumeric(char ch);

  char advance();
  char peek();
  char peekTwo();

  void scanString();
  void scanNumber();
  void scanIdentifier();
  void appendToken(TokenType type, std::any literal);

  Token scanToken();

  public:
    std::string _source;
    std::list<Token> _tokens;

    Lexer(std::string source);
    std::list<Token> scanSource();
};

#endif
