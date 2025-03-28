%option noyywrap yylineno

%{
#include <string.h>
#include "parser.tab.h"
#include "token.tab.h"

extern YYSTYPE yylval;
int last_token = 0; // Store last parsed token
%}

%%
[ \t\r\n\a] ;

"("  { return LEFT_PAREN; }
")"  { return RIGHT_PAREN; }
"{"  { return LEFT_BRACE; }
"}"  { return RIGHT_BRACE; }

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

<<EOF>> { return YYEOF; }

"//".*|\/\*(.|\n)*?\*\/ /* Ignore comments */

[0-9]+                 { yylval.int_val = atoi(yytext); return INT; }
[0-9]*\.[0-9]+         { yylval.float_val = atof(yytext); return FLOAT; }
\'([a-zA-Z0-9_])\'     { yylval.char_val = yytext[1]; return CHAR; }

[a-zA-Z_][a-zA-Z0-9_]* { 
                         /* tok type should be bison token enum */
                         int tok = match_keyword(yytext);

                         if (tok == IDENTIFIER) {
                           yylval.id = strdup(yytext);
                         }

                         return tok;
                       }

. { fprintf(stderr, "Invalid lexeme: %s\n", yytext); yyterminate(); } /* Theoretically unused rule */
%%

#ifdef  DEBUG_FLEX
#define DEBUG_FLEX

#include <stdio.h>

int main(int argc, char **argv) {
  FILE* fp = NULL;

  // Redirect yyin if file is given
  if (argc > 1) {
    fp = fopen(argv[1], "r");
    if (fp) yyin = fp;
  }

  int tok = yylex();
  while (tok != YYEOF) {
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
    tok = yylex();
  }

  if (fp != NULL) {
    fclose(fp);
  }

  return 0;
}

#endif

