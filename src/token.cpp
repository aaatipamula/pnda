#include <string>
#include "token.h"

// Helper function to turn TokenType enum into a string
std::string typeToString(TokenType type) {
  switch(type) {

    // Grouping Characters
    case LEFT_PAREN: return "LEFT_PAREN";
    case RIGHT_PAREN: return "RIGHT_PAREN";
    case LEFT_BRACE: return "LEFT_BRACE";
    case RIGHT_BRACE: return "RIGHT_BRACE";

    // Special Characters
    case PLUS: return "PLUS";
    case MINUS: return "MINUS";
    case STAR: return "STAR";
    case FORWARD_SLASH: return "FORWARD_SLASH";
    case DOT: return "DOT";
    case COMMA: return "COMMA";
    case SEMICOLON: return "SEMICOLON";

    // Logical Operators
    case EXCLAMATION: return "EXCLAMATION";
    case EXCLAMATION_EQUAL: return "EXCLAMATION_EQUAL";
    case EQUAL: return "EQUAL";
    case EQUAL_EQUAL: return "EQUAL_EQUAL";
    case GREATER: return "GREATER";
    case GREATER_EQUAL: return "GREATER_EQUAL";
    case LESS: return "LESS";
    case LESS_EQUAL: return "LESS_EQUAL";

    // Data Types
    case STRING: return "STRING";
    case NUM: return "NUM";
    case CHAR: return "CHAR";
    case IDENTIFIER: return "IDENTIFIER";

    // Keywords
    case AND: return "AND";
    case OR: return "OR";
    case IF: return "IF";
    case ELSE: return "ELSE";
    case _TRUE: return "TRUE";
    case _FALSE: return "FALSE";
    case PRINT: return "PRINT";
    case RETURN: return "RETURN";
    case FOR: return "FOR";
    case WHILE: return "WHILE";
    case VAR: return "VAR";
    case FUNC: return "FUNC";
    case CLASS: return "CLASS";
    case SUPER: return "SUPER";
    case SELF: return "SELF";
    case _NULL: return "NULL";
    
    // End of file
    case _EOF: return "_EOF";
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
