%option noyywrap yylineno

%{
#include "parser.tab.h"
#include "token.h"

extern yylval;
%}

%%
[ \t\r\n\a] ;

"("  { return LEFT_PAREN; }
")"  { return RIGHT_PAREN; }
"{"  { return LEFT_BRACE; }
"}"  { return RIGHT_BRACE; }

"."  { return DOT; }
","  { return COMMA; }
";"  { return SEMICOLON; }

"+"  { return PLUS; }
"*"  { return STAR; }
"-"  { return MINUS; }
"/"  { return FORWARD_SLASH; }

"!=" { return BANG_EQUAL; }
"==" { return EQUAL_EQUAL; }
">"  { return GREATER; }
">=" { return GREATER_EQUAL; }
"<"  { return LESS; }
"<=" { return LESS_EQUAL; }

"!"  { return BANG; }
"&&" { return L_AND; }
"||" { return L_OR; }

"&"  { return AND; }
"|"  { return OR; }
"^"  { return XOR; }

"="  { return EQUAL; }

<<EOF>> { return EOL; }

"//".*|\/\*(.|\n)*?\*\/ /* Ignore comments */

[0-9]+                 { yylval.int_val = atoi(yytext); return INT; }
[0-9]*\.[0-9]+         { yylval.float_val = atof(yytext); return FLOAT; }
\'([a-zA-Z0-9_])\'     { yylval.char_val = yytext[1]); return CHAR; }

[a-zA-Z_][a-zA-Z0-9_]* { 
                         token_type tok = match_keyword(yytext);

                         if (tok == IDENTIFIER) {
                           yylval.id = strdup(yytext);
                         }

                         return tok;
                       }

. { fprintf(stderr, "Invalid lexeme: %s\n", yytext); yyterminate(); } /* Theoretically unused rule */
%%

#ifndef EBUG
#define EBUG 0

#include <stdio.h>

int main(int argc, char **argv) {
  FILE* fp = NULL;

  if (argc > 1) {
    fp = fopen(argv[1], "r");
    if (redirect) yyin = redirect;
  }

  TokenType tok = yylex();
  while (tok != EOL) {
    switch (tok) {
      case IDENTIFIER:
        printf("IDENTIFIER: %s\n", yylval.id);
        break;
      case INT:
        printf("INT: %d\n", yylval.int_val);
        break;
      case FLOAT:
        printf("FLOAT: %f\n", yylval.float_val);
        break;
      case CHAR:
        printf("CHAR: %c\n", yylval.char_val);
        break;
      default:
        printf("%s\n", type_to_str(tok));
    }
  }

  if (fp != NULL) {
    fclose(fp);
  }

  return 0;
}

#endif

