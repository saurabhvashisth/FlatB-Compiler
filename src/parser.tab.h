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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
    FOR = 280,
    WHILE = 281,
    GOTO = 282,
    IF = 283,
    ELSE = 284,
    AND = 285,
    OR = 286,
    NOT = 287,
    READ = 288,
    PRINT = 289,
    PRINTLN = 290,
    NUMBER = 291,
    IDENTIFIER = 292,
    STRING = 293
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 12 "parser.y" /* yacc.c:1909  */

	int num; char *str;
	C_PROGRAM *program;
	C_BLOCK *block;
	C_CODESTATEMENT *codestatement;
	vector <C_VARIABLES*> *declarations;
	vector <C_VARIABLES*> *declaration;
	vector <C_VARIABLES*> *declarationlist;
	C_VARIABLES *variables;
	C_LABEL *label;
	vector <C_CODESTATEMENT*> *codestatements;
	C_TERM *term;
	C_IDS *ids;
	C_NUMEXP *numexp;
	vector <C_NUMEXP*> *expression;
	C_BOOLEXP *boolexp;
	vector <C_IDS *> *identifierlist;
	C_GOTO * cgoto;

#line 113 "parser.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
