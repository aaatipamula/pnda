#ifndef _PNDA_AST_H
#define _PNDA_AST_H

#include "token.h"

typedef struct _ast_node ast;
typedef struct _seq_list seq;
typedef struct _fn_params param;

struct _fn_params {
  char* id;
  token_type type;
  param *next;
};

struct _seq_list {
  ast *expr;
  seq *next;
};

typedef union {
  int int_val;
  float float_val;
  char char_val;
  char *id;
} ast_val;

struct _ast_node {
  token_type type;
  ast_val data;

  seq *call_args;
  param *params;
  seq *scope;

  ast *left;
  ast *right;
  ast *ter; // Only used for ternary operators
};

/* AST functions */
ast *create_int_literal(int val);
ast *create_float_literal(float val);
ast *create_char_literal(char val);
ast *create_bool_literal(token_type val);
ast *create_identifier(char *val);

ast *create_unary(token_type op, ast *expr);
ast *create_binary(token_type op, ast *left, ast *right);
ast *create_ternary(token_type op, ast *cond, ast *left, ast *right);
void destroy_ast(ast *node);

/* Sequence functions */
seq *create_seq(ast *expr);
void destroy_seq(seq *node);

/* Argument list functions */
param *create_param(char *id, token_type type);
void destroy_param(param* node);

#endif
