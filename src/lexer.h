#ifndef LEXER_H
#define LEXER_H

#include <list>
#include <string>
#include <unordered_map>

#include "token.h"

class Lexer {
  int curr, start = 0;
  int line = 1;

  // Keyword Identifier Hashmap
  const std::unordered_map<std::string, TokenType> _keywords = {
    {"and", AND},
    {"or", OR},
    {"if", IF},
    {"else", ELSE},
    {"true", _TRUE},
    {"false", _FALSE},
    {"print", PRINT},
    {"return", RETURN},
    {"for", FOR},
    {"while", WHILE},
    {"var", VAR},
    {"func", FUNC},
    {"super", SUPER},
    {"self", SELF},
    {"class", CLASS},
    {"null", _NULL}
  };

  // Helper Methods
  bool atEnd();
  bool find(char ch);
  bool isDigit(char ch);
  bool isAlpha(char ch);
  bool isAlphaNumeric(char ch);

  // Lookahead Methods
  char advance();
  char peek();
  char peekTwo();

  // Scanning Methods
  void scanString();
  void scanNumber();
  void scanIdentifier();

  // Adding tokens
  void appendToken(TokenType type, std::any literal);
  Token scanToken();

  public:
    std::string _source;
    std::list<Token> _tokens;

    Lexer(std::string source);
    std::list<Token> scanSource();
};

#endif
