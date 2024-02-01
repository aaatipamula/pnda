#include <string>
#include "token.h"

std::string typeToString(TokenType type) {
  switch(type) {
    case LEFT_PAREN:
      return "lparen";
    case RIGHT_PAREN:
      return "rparen";
    case LEFT_BRACE:
      return "lbrace";
    case RIGHT_BRACE:
      return "rbrace";
    case PLUS:
      return "plus";
    case MINUS:
      return "minus";
    case STAR:
      return "star";
    case FORWARD_SLASH:
      return "slash";
    case DOT:
      return "dot";
    case COMMA:
      return "comma";
    case SEMICOLON:
      return "semicolon";
    case EXCLAMATION:
      return "inverse";
    case EXCLAMATION_EQUAL:
      return "ne";
    case EQUAL:
      return "equals";
    case EQUAL_EQUAL:
      return "eq";
    case GREATER:
      return "gt";
    case GREATER_EQUAL:
      return "ge";
    case LESS:
      return "lt";
    case LESS_EQUAL:
      return "le";
    case STRING:
      return "string";
    case NUM:
      return "n";
    case IDENTIFIER:
      return "identifier";
    case AND:
      return "and";
    case PRINT:
      return "print";
    case OR:
      return "or";
    case IF:
      return "if";
    case ELSE:
      return "else";
    case TRU:
      return "true";
    case FALS:
      return "false";
    case RETURN:
      return "return";
    case FOR:
      return "for";
    case WHILE:
      return "while";
    case VAR:
      return "var";
    case FUNC:
      return "func";
    case SUPER:
      return "super";
    case SELF:
      return "self";
    case NIL:
      return "null";
    case EF:
      return "eof";
  }
}

Token::Token(TokenType type, std::any literal, std::string lexeme, int line) {
  _type = type;
  _literal = literal;
  _lexeme = lexeme;
  _line = line;
}

std::string Token::toString() {
  return typeToString(_type) + " " + _lexeme + " ";
}
