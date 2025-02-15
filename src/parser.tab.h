/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SRC_PARSER_TAB_H_INCLUDED
# define YY_YY_SRC_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    LEFT_PAREN = 258,              /* LEFT_PAREN  */
    RIGHT_PAREN = 259,             /* RIGHT_PAREN  */
    IF = 260,                      /* IF  */
    ELSE = 261,                    /* ELSE  */
    TRUE = 262,                    /* TRUE  */
    FALSE = 263,                   /* FALSE  */
    LEFT_BRACE = 264,              /* LEFT_BRACE  */
    RIGHT_BRACE = 265,             /* RIGHT_BRACE  */
    COMMA = 266,                   /* COMMA  */
    SEMICOLON = 267,               /* SEMICOLON  */
    EQUAL = 268,                   /* EQUAL  */
    INT_T = 269,                   /* INT_T  */
    FLOAT_T = 270,                 /* FLOAT_T  */
    CHAR_T = 271,                  /* CHAR_T  */
    BOOL_T = 272,                  /* BOOL_T  */
    FUNC = 273,                    /* FUNC  */
    LET = 274,                     /* LET  */
    APP = 275,                     /* APP  */
    SEQ = 276,                     /* SEQ  */
    INT = 277,                     /* INT  */
    CHAR = 278,                    /* CHAR  */
    FLOAT = 279,                   /* FLOAT  */
    IDENTIFIER = 280,              /* IDENTIFIER  */
    L_OR = 281,                    /* L_OR  */
    L_AND = 282,                   /* L_AND  */
    BANG_EQUAL = 283,              /* BANG_EQUAL  */
    EQUAL_EQUAL = 284,             /* EQUAL_EQUAL  */
    GREATER = 285,                 /* GREATER  */
    GREATER_EQUAL = 286,           /* GREATER_EQUAL  */
    LESS = 287,                    /* LESS  */
    LESS_EQUAL = 288,              /* LESS_EQUAL  */
    PLUS = 289,                    /* PLUS  */
    MINUS = 290,                   /* MINUS  */
    STAR = 291,                    /* STAR  */
    FORWARD_SLASH = 292,           /* FORWARD_SLASH  */
    OR = 293,                      /* OR  */
    XOR = 294,                     /* XOR  */
    AND = 295,                     /* AND  */
    BANG = 296,                    /* BANG  */
    UMINUS = 297                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "src/pnda.y"

  struct _ast_node *node;
  struct _func_arg *arg;
  int int_val;
  float float_val;
  char char_val;
  char* id;
  int token; // token type enum

#line 116 "src/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SRC_PARSER_TAB_H_INCLUDED  */
