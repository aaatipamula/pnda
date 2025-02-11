%{
#include <stdio.h>
#include "ast.h"

extern int yyparse();
int yylex();

// TODO: More robust error messages
void yyerror(const char *s) { fprintf(stderr, "ERROR: %s\n", s); }

ast* prog_start;
%}

%define parse.error verbose

%union {
  struct _ast_node* node;
  int int_val;
  float float_val;
  char char_val;
  char* id;
  int token; // token type enum
}

%token <token> LEFT_PAREN RIGHT_PAREN 
%token <token> IF ELSE TRUE FALSE 
%token <token> LEFT_BRACE RIGHT_BRACE 
%token <token> DOT COMMA SEMICOLON
%token <token> EQUAL
%token <token> INT_T FLOAT_T CHAR_T BOOL_T
%token <token> FUNC RETURN LET APP
%token <token> FOR WHILE
%token <token> EOL

%token <int_val> INT
%token <char_val> CHAR
%token <float_val> FLOAT
%token <id> IDENTIFIER

%left  <token> L_OR
%left  <token> L_AND
%left  <token> BANG_EQUAL EQUAL_EQUAL
%left  <token> GREATER GREATER_EQUAL LESS LESS_EQUAL
%left  <token> PLUS MINUS
%left  <token> STAR FORWARD_SLASH
%left  <token> OR XOR
%left  <token> AND
%right <token> BANG UMINUS

%type <node>  expr binary_expr unary_expr literal
%type <token> binop unop

%start expr

%%
expr : binary_expr { prog_start = $1; }
     ;

binary_expr : unary_expr binop unary_expr { $$ = create_binary($2, $1, $3); }
            | unary_expr
            ;

unary_expr : unop literal { $$ = create_unary($1, $2); }
           | literal
           ;

literal : INT   { $$ = create_int_literal(yylval.int_val); }
        | TRUE  { $$ = create_bool_literal(1); }
        | FALSE { $$ = create_bool_literal(0); }
        | FLOAT { $$ = create_float_literal(yylval.float_val); }
        | CHAR  { $$ = create_char_literal(yylval.char_val); }
        ;

binop : AND   { $$ = AND; }
      | OR    { $$ = OR; }
      | XOR   { $$ = XOR; }
      | L_AND { $$ = L_AND; }
      | L_OR  { $$ = L_OR; }
      | EQUAL_EQUAL   { $$ = EQUAL_EQUAL; }
      | BANG_EQUAL    { $$ = BANG_EQUAL; }
      | LESS_EQUAL    { $$ = LESS_EQUAL; }
      | GREATER_EQUAL { $$ = GREATER_EQUAL; }
      | LESS    { $$ = LESS; }
      | GREATER { $$ = GREATER; }
      | PLUS    { $$ = PLUS; }
      | MINUS   { $$ = MINUS; }
      | STAR    { $$ = STAR; }
      | FORWARD_SLASH { $$ = FORWARD_SLASH; }
      ;

unop : BANG   { $$ = BANG; }
     | MINUS  { $$ = MINUS; }
     ;
%%

#ifndef EBUG_BISON
#define EBUG_BISON 0

int main(int argc, char **argv) {

  FILE* fp = NULL;
  extern FILE* yyin;

  // Redirect yyin if file is given
  if (argc > 1) {
    fp = fopen(argv[1], "r");
    if (fp) yyin = fp;
  }

  // Parse the input
  if (yyparse() == 0) {
    // NOTE: Eventually pretty print the AST
    printf("Parse successful.\n");
  } else {
    printf("Parse failed.\n");
  }

  printf("Program:\n");
  pprint_ast(prog_start, 0);

  if (fp != NULL) {
    fclose(fp);
  }

  return 0;
}

#endif

