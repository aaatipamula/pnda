#ifndef EXPR_H
#define EXPR_H

#include <any>
#include "token.h"

class Expr {
  protected:
    Expr* _left;
    Expr* _right;
    Token _oper;
};

class Binary : public Expr {
  public:
    Binary(Expr* left, Token oper, Expr* right) {
      _left = left;
      _oper = oper;
      _right = right;
    }
};


class Grouping : public Expr {
  Expr* _expression;
  public:
    Grouping(Expr* expression) {
      _expression = expression;
    }
};


class Literal : public Expr {
  std::any _value;
  public:
    Literal(std::any value) {
      _value = value;
    }
};


class Urnary : public Expr {
  public:
    Urnary(Token oper, Expr* right) {
      _oper = oper;
      _right = right;
    }
};

#endif