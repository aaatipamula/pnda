#include "token.h"
#include <string.h>

// Helper function to turn TokenType enum into a string
char* type_to_str(token_type type) {
  switch(type) {
    // Grouping Characters
    case LEFT_PAREN:  return "LEFT_PAREN";
    case RIGHT_PAREN: return "RIGHT_PAREN";
    case LEFT_BRACE:  return "LEFT_BRACE";
    case RIGHT_BRACE: return "RIGHT_BRACE";

    // Special Characters
    case DOT: return "DOT";
    case COMMA: return "COMMA";
    case SEMICOLON: return "SEMICOLON";

    // Arethmetic Operators
    case STAR: return "STAR";
    case PLUS: return "PLUS";
    case MINUS: return "MINUS";
    case FORWARD_SLASH: return "FORWARD_SLASH";

    // Comparison Operators
    case LESS: return "LESS";
    case LESS_EQUAL: return "LESS_EQUAL";
    case GREATER: return "GREATER";
    case GREATER_EQUAL: return "GREATER_EQUAL";
    case EQUAL_EQUAL: return "EQUAL_EQUAL";
    case BANG_EQUAL: return "BANG_EQUAL";

    // Logical Operators
    case BANG: return "BANG";
    case L_AND: return "L_AND";
    case L_OR: return "L_OR";
    
    // Binary Operators
    case AND: return "AND";
    case OR: return "OR";
    case XOR: return "XOR";

    // Data Types
    case INT: return "INT";
    case FLOAT: return "INT";
    case CHAR: return "CHAR";
               //
    // Data Types
    case INT_T: return "TYPE(INT)";
    case FLOAT_T: return "TYPE(FLOAT)";
    case CHAR_T: return "TYPE(CHAR)";
    case BOOL_T: return "TYPE(BOOL)";
    
    // Binds
    case EQUAL: return "EQUAL";
    case IDENTIFIER: return "IDENTIFIER";

    // Keywords
    case IF: return "IF";
    case ELSE: return "ELSE";
    case TRUE: return "TRUE";
    case FALSE: return "FALSE";
    case LET: return "LET";
    case FUNC: return "FUNC";
    case RETURN: return "RETURN";
    case YYEOF: return "EOF";
  }

  return NULL;
}

token_type match_keyword(const char *str) {
  if (strcmp(str, "if") == 0) {
    return IF;
  } else if (strcmp(str, "else") == 0) {
    return ELSE;
  } else if (strcmp(str, "true") == 0) {
    return TRUE;
  } else if (strcmp(str, "false") == 0) {
    return FALSE;
  } else if (strcmp(str, "return") == 0) {
    return RETURN;
  } else if (strcmp(str, "let") == 0) {
    return LET;
  } else if (strcmp(str, "fn") == 0) {
    return FUNC;
  } else if (strcmp(str, "int") == 0) {
    return INT_T;
  } else if (strcmp(str, "float") == 0) {
    return FLOAT_T;
  } else if (strcmp(str, "char") == 0) {
    return CHAR_T;
  } else if (strcmp(str, "bool") == 0) {
    return BOOL_T;
  }

  return IDENTIFIER;
}

