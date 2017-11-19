/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CODEBLOCK = 258,
    DECLBLOCK = 259,
    INTEGER = 260,
    NE = 261,
    EQ = 262,
    EQEQ = 263,
    LE = 264,
    LT = 265,
    GT = 266,
    GE = 267,
    LBRACE = 268,
    RBRACE = 269,
    LBRACKET = 270,
    RBRACKET = 271,
    LPARAN = 272,
    RPARAN = 273,
    COMMA = 274,
    PLUS = 275,
    MINUS = 276,
    MUL = 277,
    DIV = 278,
    MOD = 279,
    PLUSEQ = 280,
    MINUSEQ = 281,
    MULEQ = 282,
    DIVEQ = 283,
    MODEQ = 284,
    BITANDEQ = 285,
    BITOREQ = 286,
    BITXOREQ = 287,
    LSHIFTEQ = 288,
    RSHIFTEQ = 289,
    FOR = 290,
    WHILE = 291,
    GOTO = 292,
    IF = 293,
    ELSE = 294,
    AND = 295,
    OR = 296,
    NOT = 297,
    BITAND = 298,
    BITOR = 299,
    BITXOR = 300,
    LSHIFT = 301,
    RSHIFT = 302,
    READ = 303,
    PRINT = 304,
    PRINTLN = 305,
    NUMBER = 306,
    IDENTIFIER = 307,
    STRING = 308
  };
#endif
/* Tokens.  */
#define CODEBLOCK 258
#define DECLBLOCK 259
#define INTEGER 260
#define NE 261
#define EQ 262
#define EQEQ 263
#define LE 264
#define LT 265
#define GT 266
#define GE 267
#define LBRACE 268
#define RBRACE 269
#define LBRACKET 270
#define RBRACKET 271
#define LPARAN 272
#define RPARAN 273
#define COMMA 274
#define PLUS 275
#define MINUS 276
#define MUL 277
#define DIV 278
#define MOD 279
#define PLUSEQ 280
#define MINUSEQ 281
#define MULEQ 282
#define DIVEQ 283
#define MODEQ 284
#define BITANDEQ 285
#define BITOREQ 286
#define BITXOREQ 287
#define LSHIFTEQ 288
#define RSHIFTEQ 289
#define FOR 290
#define WHILE 291
#define GOTO 292
#define IF 293
#define ELSE 294
#define AND 295
#define OR 296
#define NOT 297
#define BITAND 298
#define BITOR 299
#define BITXOR 300
#define LSHIFT 301
#define RSHIFT 302
#define READ 303
#define PRINT 304
#define PRINTLN 305
#define NUMBER 306
#define IDENTIFIER 307
#define STRING 308

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 10 "parser.y" /* yacc.c:1909  */
int num; char *id;

#line 163 "y.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
