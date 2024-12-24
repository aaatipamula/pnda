%{
#include <stdio.h>
#include "ast.h"

extern token_type yylex();
void yyerror(const char *s) { printf("ERROR %s\n", s); }

seq* prog_start;

%}

%union {
  ast* node;
  seq* sequence;
  param* fn_args;
  token_type token;
  int int_val;
  float float_val;
  char char_val;
  char* id;
}

%token <int_val> INT
%token <char_val> CHAR
%token <float_val> FLOAT
%token <id> IDENTIFIER

%token LEFT_PAREN RIGHT_PAREN 
%token LEFT_BRACE RIGHT_BRACE 
%token DOT COMMA SEMICOLON
%token PLUS MINUS STAR FORWARD_SLASH 
%token LESS LESS_EQUAL
%token GREATER GREATER_EQUAL 
%token EQUAL_EQUAL BANG_EQUAL 
%token BANG L_AND L_OR
%token AND OR XOR 
%token EQUAL
%token INT_T FLOAT_T CHAR_T BOOL_T
%token IF ELSE TRUE FALSE 
%token FUNC RETURN LET APP
%token EOL

%type <sequence> prog stmts block
%type <fn_args> fn_params arg
%type <node> let_stmt fn_stmt expr stmt
%type <node> if_expr unary_expr binary_expr literal
%type <sequence> call_args
%type <token> binary_op unary_op c_type

%left BANG_EQUAL EQUAL_EQUAL
%left GREATER GREATER_EQUAL LESS LESS_EQUAL
%left L_AND
%left L_OR
%left PLUS MINUS
%left STAR FORWARD_SLASH
%left AND OR XOR

%start prog

%%
prog : stmts { prog_start = $1; }
     ;

stmts : stmt { $$ = create_seq($1); }
      | stmts stmt { $1->next = $2; }
      ;

stmt : let_stmt | fn_stmt 
     | expr SEMICOLON { $$ = $1; }
   ;

let_stmt : LET IDENTIFIER SEMICOLON { $$ = create_identifier(IDENTIFIER, $2); }
         | LET IDENTIFIER EQUAL expr SEMICOLON { $$ = create_identifier(IDENTIFIER, $2); $$->ter = $4; }

fn_stmt : FUNC IDENTIFIER RIGHT_PAREN fn_params LEFT_PAREN block { $$ = create_identifier(FUNC, $2); $$->params = $4; $$->scope = $6; }
        ;

fn_params : arg
          | /* No params */ { $$ = create_param(NULL, EOL); }
          | fn_params COMMA arg { $1->next = $3; }
          ;

arg : IDENTIFIER c_type { $$ = create_param($1, $2); }

c_type : INT_T | FLOAT_T | CHAR_T | BOOL_T
       ;

block : RIGHT_BRACE stmts LEFT_BRACE { $$ = $2; }
      ;

expr : if_expr | binary_expr | unary_expr
     | expr RIGHT_PAREN call_args LEFT_PAREN { create_binary(APP, $1, $3); }
     | RIGHT_PAREN expr LEFT_PAREN { $$ = $2 }
     | literal
     ;

call_args : /* No args */ { $$ = create_seq(NULL) }
          | expr { $$ = create_seq($1); }
          | call_args COMMA expr { $1->next = create_seq($3); }
          ;

if_expr : IF RIGHT_PAREN binary_expr LEFT_PAREN binary_expr ELSE binary_expr { $$ = create_ternary(IF, $3, $5, $7); }
        ;

unary_expr : unary_op expr { $$ = create_unary($1, $2); }

unary_op : MINUS | BANG
         ;

binary_expr : expr binary_op expr { $$ = create_binary($2, $1, $3); }
            ; 

binary_op : BANG_EQUAL EQUAL_EQUAL
          | GREATER GREATER_EQUAL LESS LESS_EQUAL
          | L_AND
          | L_OR
          | PLUS MINUS
          | STAR FORWARD_SLASH
          | AND OR XOR
          | MINUS BANG
          ;

literal : TRUE       { $$ = create_bool_literal(TRUE); }
        | FALSE      { $$ = create_bool_literal(FALSE); }
        | CHAR       { $$ = create_char_literal($1); }
        | INT        { $$ = create_int_literal($1); }
        | FLOAT      { $$ = create_float_literal($1); }
        | IDENTIFIER { $$ = create_identifier($1); }
%%
