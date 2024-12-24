#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "token.h"

void check_malloc(void *p) {
  if (p == NULL) {
    fprintf(stderr, "pnda: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }
}

param *create_param(char *id, token_type type) {
  param *node = (param *)malloc(sizeof(param));
  check_malloc(node);

  node->id = id;
  node->type = type;
  node->next = NULL;
  
  return node;
}

seq *create_seq(ast *expr) {
  seq *node = (seq *)malloc(sizeof(seq));
  check_malloc(node);

  node->expr = expr;
  node->next = NULL;
  
  return node;
}

ast *create_ast_node(token_type type) {
  ast *node = (ast *)malloc(sizeof(ast));
  check_malloc(node);

  node->type = type;
  node->left = node->right = node->ter = NULL;

  node->call_args = node->scope = NULL;
  node->params = NULL;

  return node;
}

ast *create_int_literal(int val) {
  ast *node = create_ast_node(INT);
  node->data.int_val = val;
  return node;
}

ast *create_float_literal(float val) {
  ast *node = create_ast_node(FLOAT);
  node->data.float_val = val;
  return node;
}
ast *create_char_literal(char val) {
  ast *node = create_ast_node(CHAR);
  node->data.char_val = val;
  return node;
}
ast *create_bool_literal(token_type val) {
  ast *node = create_ast_node(val);
  node->data.int_val = (val == TRUE);
  return node;
}

ast *create_identifier(char *val) {
  ast *node = create_ast_node(IDENTIFIER);
  node->data.id = val;
  return node;
}

ast *create_unary(token_type op, ast *expr) {
  ast *node = create_ast_node(op);
  node->left = expr;
  return node;
}

ast *create_binary(token_type op, ast *left, ast *right) {
  ast *node = create_ast_node(op);
  node->left = left;
  node->right = right;
  return node;
}

ast *create_ternary(token_type op, ast *cond, ast *left, ast *right) {
  ast *node = create_ast_node(op);
  node->ter = cond;
  node->left = left;
  node->right = right;
  return node;
}

void destory_seq(seq *node) {
  if (node == NULL) return;

  destroy_ast(node->expr);
  node->expr = NULL;

  destroy_seq(node->next);
  node->next = NULL;

  free(node);
  node = NULL;
}

void destroy_param(param *node) {
  if (node == NULL) return;

  free(node->id);
  node->id = NULL;

  destroy_param(node->next);
  node->next = NULL;

  free(node);
  node = NULL;
}

void destroy_ast(ast *node) {
  if (node == NULL) return;

  if (node->type == IDENTIFIER || node->type == FUNC) {
    free(node->data.id); // Free the identifier string
    node->data.id = NULL; 
  }

  destroy_seq(node->call_args);
  node->call_args = NULL;
  destroy_seq(node->scope);
  node->scope = NULL;
  destroy_param(node->params);
  node->params = NULL;

  destroy_ast(node->left);
  node->left = NULL;
  destroy_ast(node->right);
  node->right = NULL;
  destroy_ast(node->ter); // Free the third child for ternary nodes
  node->ter = NULL;

  free(node);
  node = NULL;
}
