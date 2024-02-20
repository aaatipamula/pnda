#ifndef EXPR_H
#define EXPR_H

#include <any>
#include <memory>
#include <utility>
#include "token.h"

class Expr {
  public:
    virtual ~Expr() = default;
};

class Binary : public Expr {
  std::unique_ptr<Expr> left;
  Token oper;
  std::unique_ptr<Expr> right;
  public:
    Binary(std::unique_ptr<Expr> left, Token oper, std::unique_ptr<Expr> right)
      : left(std::move(left)), oper(oper), right(std::move(right)) {}
};

class Grouping : public Expr {
  std::unique_ptr<Expr> expression;
  public:
    Grouping(std::unique_ptr<Expr> expression)
      : expression(std::move(expression)) {}
};

class Literal : public Expr {
  std::any value;
  public:
    Literal(std::any value)
      : value(value) {}
};

class Urnary : public Expr {
  Token oper;
  std::unique_ptr<Expr> right;
  public:
    Urnary(Token oper, std::unique_ptr<Expr> right)
      : oper(oper), right(std::move(right)) {}
};

#endif
