#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "parser.tab.h"
#include "token.tab.h"

void check_malloc(void *p) {
  if (p == NULL) {
    fprintf(stderr, "pnda: Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }
}

ast *create_ast_node(int type) {
  ast *node = (ast *)malloc(sizeof(ast));
  check_malloc(node);

  node->type = type;
  node->left = node->right = node->ter = NULL;

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

ast *create_bool_literal(int val) {
  ast *node = create_ast_node(val);
  node->data.int_val = val;
  return node;
}

ast *create_identifier(char *val) {
  ast *node = create_ast_node(IDENTIFIER);
  node->data.id = val;
  return node;
}

ast *create_unary(int op, ast *expr) {
  ast *node = create_ast_node(op);
  node->left = expr;
  return node;
}

ast *create_binary(int op, ast *left, ast *right) {
  ast *node = create_ast_node(op);
  node->left = left;
  node->right = right;
  return node;
}

ast *create_ternary(int op, ast *cond, ast *left, ast *right) {
  ast *node = create_ast_node(op);
  node->ter = cond;
  node->left = left;
  node->right = right;
  return node;
}

void destroy_ast(ast *node) {
  if (node == NULL) return;

  if (node->type == IDENTIFIER || node->type == FUNC) {
    free(node->data.id); // Free the identifier string
    node->data.id = NULL; 
  }

  destroy_ast(node->left);
  node->left = NULL;
  destroy_ast(node->right);
  node->right = NULL;
  destroy_ast(node->ter); // Free the third child for ternary nodes
  node->ter = NULL;

  free(node);
  node = NULL;
}

void pprint_ast(ast *node, unsigned int depth) {
  if (depth == 0) {
    printf("%s\n", type_to_str(node->type));
  } else {
    printf("%*s%s\n", depth, "  ", type_to_str(node->type));
  }

  if (node->left) {
    pprint_ast(node->left, depth+1);
  }

  if (node->right) {
    pprint_ast(node->right, depth+1);
  }

  if (node->ter) {
    pprint_ast(node->ter, depth+1);
  }
}

