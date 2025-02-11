#ifndef _PNDA_AST_H
#define _PNDA_AST_H

typedef struct _ast_node ast;

typedef union {
  int int_val;
  float float_val;
  char char_val;
  char *id;
} ast_val;


struct _ast_node {
  int type;
  ast_val data;

  ast* left;
  ast* right;
  ast* ter; // Only used for ternary operators
};

/* AST functions */
ast* create_int_literal(int val);
ast* create_float_literal(float val);
ast* create_char_literal(char val);
ast* create_bool_literal(int val);
ast* create_identifier(char *val);

ast* create_unary(int op, ast *expr);
ast* create_binary(int op, ast *left, ast *right);
ast* create_ternary(int op, ast *cond, ast *left, ast *right);

void destroy_ast(ast *node);
void pprint_ast(ast *node, unsigned int depth);

#endif
