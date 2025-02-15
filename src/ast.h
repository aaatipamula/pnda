#ifndef _PNDA_AST_H
#define _PNDA_AST_H

/* Forward declaration to appease type checker */
typedef struct _ast_node ast;
typedef struct _func_arg fn_arg;

typedef union {
  int int_val;
  float float_val;
  char char_val;
  char *id;
} ast_val;

struct _func_arg {
  int type;
  ast *id;
};

struct _ast_node {
  int type;
  int ret_type;
  fn_arg *arg;
  ast_val data;

  ast* ter; // Only used for ternary operators
  ast* left;
  ast* right;
};

/* Literal nodes */
ast *create_int_literal(int val);
ast *create_float_literal(float val);
ast *create_char_literal(char val);
ast *create_bool_literal(int val);
ast *create_identifier(char *val);

/* Function helpers */
ast *create_function_arg(ast *id, int type);
ast *add_function_arg(ast *head, ast* next_id, int next_type);
ast *close_function(ast *fn_head, int type, ast *block);
ast *create_let(ast* id, ast* expr);

/* Expression nodes */
ast *create_unary(int op, ast *expr);
ast *create_binary(int op, ast *left, ast *right);
ast *create_ternary(int op, ast *cond, ast *left, ast *right);

/* AST helpers */
void destroy_ast(ast *node);
void pprint_ast(ast *node, unsigned int depth);

#endif

