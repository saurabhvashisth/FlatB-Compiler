%{ 
#include "AST.h"
#include <bits/stdc++.h>
#include "parser.tab.h"
using namespace std;
int lines = 1;
%}

%%
	/* CONTAINERS */
declblock	return DECLBLOCK;
codeblock	return CODEBLOCK;

	/* PRINT */
"println" 	return PRINTLN;
"print"		return PRINT;
"read" 		return READ;

	/* REL OP */

"!="	return NE;
"=" 	return EQ;
"=="	return EQEQ;
"<="	return LE; 
"<"		return LT;
">"		return GT;
">="	return GE;

	/* BIN OP */

"+"		return PLUS;
"-"		return MINUS;
"*"		return MUL;
"/"		return DIV;


	/* LOGICAL OP */

"&&"	return AND;
"||"	return OR;
"!"		return NOT;

	/* CONTROL STATEMENTS */

"for"	return FOR;
"while"	return WHILE;
"goto"	return GOTO;
"if"	return IF;
"else"	return ELSE;

	/* CHARACTERS */	

"{"		return LBRACE;
"}"		return RBRACE;
"["		return LBRACKET;
"]"		return RBRACKET;
"("		return LPARAN;
")" 	return RPARAN;
":"		return ':';
";"		return ';';
","		return COMMA;


	/* DATATYPE */
int return INTEGER;
\".*\"	{  //printf("string"); 
    	yytext[yyleng-1] = '\0';
		yylval.str = strdup(yytext+1);
			return STRING; }


	/* OTHERS */
[0-9][0-9]*  	{  //printf("number"); 
 				yylval.num = atoi(yytext);
					return NUMBER; } 

[_a-zA-Z][_a-zA-Z0-9]*  {	 //printf("identifier");  
						yylval.str = strdup(yytext);
							return IDENTIFIER; }
[ \t]		{ /* Do nothing */ }
[\n]		{lines++;}
.			{ printf("Unexpected token : %s\n", yytext);}


%%

int yywrap(void){
	return 1;
}
