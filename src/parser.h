#ifndef PARSER_H
#define PARSER_H

#include <list>

#include "token.h"
#include "Expr.h"

class Parser {

  const std::list<Token> _tokens
  static int current = 0;

  bool match(const TokenType types...);
  bool check(TokenType type);
  bool atEnd();

  Token advance();
  Token peek();
  Token previous();
  Token consume();

  Expr expression();
  Expr equality();
  Expr comparison();
  Expr factor();
  Expr urnary();
  Expr primary();

  public:
    Expr parse();
}

#endif
