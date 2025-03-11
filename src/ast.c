#include <stdio.h>
#include <stdlib.h>

#include "ast.h"
#include "parser.tab.h"
#include "token.tab.h"

/**
 * TODO:
 * - Try using arena allocation instead of plain malloc.
 */

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
  node->arg = NULL;

  return node;
}

fn_arg *create_arg(ast *id, int type) {
  fn_arg *node = (fn_arg*)malloc(sizeof(fn_arg));
  check_malloc(node);

  node->id = id;
  node->type = type;

  return node;
}


/* Create literal nodes */
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


/* Create function related nodes */
ast *create_function_arg(ast *id, int type) {
  fn_arg *arg = create_arg(id, type);
  ast *node = create_ast_node(FUNC);
  node->arg = arg;
  node->ret_type = 0; //TODO: Change this to a non-value token
  return node;
}

/**
 * @brief Curries arguments as functions
 *
 * @param head The 'outermost' function
 * @param next_id The identifier of the argument for the next function to add
 * @param next_type The type of the argument for the next function to add
 * @return Outermost function node
 */
ast *add_function_arg(ast *head, ast* next_id, int next_type) {
  ast *next_func = create_function_arg(next_id, next_type);

  ast *curr_node = head;
  while (curr_node->ter) {
    curr_node = curr_node->ter;
  }

  curr_node->ret_type = FUNC;
  curr_node->ter = next_func;
  return head;
}

/**
 * @brief Gives the innermost function the correct return type and expression.
 *
 * @param fn_head The 'outermost' function
 * @param type The innermost function type
 * @param block The final expression to be evaluated
 * @return Outermost function node
 */
ast *close_function(ast *fn_head, int type, ast *block) {
  ast *curr_node = fn_head;
  while (curr_node->ter) {
    curr_node = curr_node->ter;
  }

  curr_node->ret_type = type;
  curr_node->ter = block;
  return fn_head;
}

ast *create_let(ast* identifier, ast* expr){
  ast *node = create_ast_node(LET);

  node->data.id = identifier->data.id;
  free(identifier);
  identifier = NULL;
  
  node->ter = expr;
  return node;
}


/* Expression nodes */
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


/* AST helpers */
void destroy_ast(ast *node) {
  if (node == NULL) return;

  if (node->type == IDENTIFIER) {
    free(node->data.id); // Free the identifier string
    node->data.id = NULL; 
  } 

  if (node->arg) {
    destroy_ast(node->arg->id); // Free identifiers
    node->arg->id = NULL;
    
    free(node->arg);
    node->arg = NULL;
  }

  destroy_ast(node->left);
  node->left = NULL;
  destroy_ast(node->right);
  node->right = NULL;
  destroy_ast(node->ter);
  node->ter = NULL;

  free(node);
  node = NULL;
}

void pprint_ast(ast *node, unsigned int depth) {
  printf("%*s%s\n", depth*2, "", type_to_str(node->type));

  if (node->ter) {
    pprint_ast(node->ter, depth + 1);
  }

  if (node->left) {
    pprint_ast(node->left, depth + 1);
  }

  if (node->right) {
    pprint_ast(node->right, depth + 1);
  }
}

