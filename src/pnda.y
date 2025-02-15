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
  struct _ast_node *node;
  struct _func_arg *arg;
  int int_val;
  float float_val;
  char char_val;
  char* id;
  int token; // token type enum
}

%token <token> LEFT_PAREN RIGHT_PAREN 
%token <token> IF ELSE TRUE FALSE 
%token <token> LEFT_BRACE RIGHT_BRACE 
%token <token> COMMA SEMICOLON
%token <token> EQUAL
%token <token> INT_T FLOAT_T CHAR_T BOOL_T
%token <token> FUNC LET APP
%token <token> SEQ

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
%type <node>  fn_expr fn_arg block decls let_stmt
%type <token> binop unop

%start expr

%%
prog : decls { prog_start = $1; }
     ;

decls : decl
      | { $$ = NULL; } // Empty
      | decls decl { $$ = create_binary(SEQ, $1, $2); }
      ;

decl : let_stmt | fn_expr
     | expr SEMICOLON { $$ = $1 }
     ;

let_stmt : LET IDENTIFIER EQUAL expr SEMICOLON { $$ = create_let($2, $4); }
         ;

fn_expr : concrete_type FUNC LEFT_PAREN fn_args RIGHT_PAREN block { $$ = close_function($4, $1, $6); }
        ;

fn_args : IDENTIFIER concrete_type { $$ = create_function_arg($1, $2); }
        | fn_arg COMMA IDENTIFIER concrete_type { $$ = add_function_arg($1, $3, $4); }
        ;

concrete_type : INT_T   { $$ = INT_T; }
              | FLOAT_T { $$ = FLOAT_T; }
              | CHAR_T  { $$ = CHAR_T; }
              | BOOL_T  { $$ = BOOL_T; }
              ;

block : LEFT_BRACE decls RIGHT_BRACE { $$ = $2; }

expr : if_expr | binary_expr | unary_expr | literal
     | LEFT_PAREN expr RIGHT_PAREN { $$ = $2; }
     | fn_expr expr { $$ = create_binary(APP, $1, $2); }
     ;

if_expr : IF LEFT_PAREN expr RIGHT_PAREN expr ELSE expr { $$ = create_ternary(IF, $3, $5, $7); }
        ;

unary_expr : unop expr { $$ = create_unary($1, $2); }
           ;

unop : BANG  { $$ = BANG; }
     | MINUS { $$ = MINUS; }
     ;

binary_expr : expr binop expr { $$ = create_binary($2, $1, $3); }
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

literal : INT   { $$ = create_int_literal(yylval.int_val); }
        | TRUE  { $$ = create_bool_literal(1); }
        | FALSE { $$ = create_bool_literal(0); }
        | FLOAT { $$ = create_float_literal(yylval.float_val); }
        | CHAR  { $$ = create_char_literal(yylval.char_val); }
        | IDENTIFIER { $$ = create_identifier(yylval.id); }
        ;
%%

#ifndef EBUG_BISON
#define EBUG_BISON

int main(int argc, char **argv) {

  FILE* fp = NULL;
  extern FILE* yyin;

  // Redirect yyin if file is given
  if (argc > 1) {
    fp = fopen(argv[1], "r");
    if (fp) yyin = fp;
  }


  int parse_result = yyparse();

  // Parse the input
  if (parse_result == 0) {
    printf("Program:\n");
    pprint_ast(prog_start, 0);
  } else {
    printf("Parse failed.\n");
  }

  if (fp != NULL) {
    fclose(fp);
  }

  return parse_result;
}

#endif

