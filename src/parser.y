%{
  #include <stdio.h>
  #include <stdlib.h>
  extern int yylex (void);
  extern int yyparse();
  void yyerror (char const *s);
  extern int lines;
  #include "lex.yy.c"
  extern FILE *yyin;
%}

%union {
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
}

/* TYPE DECLARATINOS */
%type <program> PROGRAM
%type <codestatement> ASSIGNMENT
%type <codestatement> INPUT
%type <codestatement> OUTPUT
%type <codestatement> CONTROL
%type <codestatement> LOOPS
%type <declarations> DECLARATIONS
%type <declaration> DECLARATION
%type <declarationlist> DECLARATIONLIST
%type <variables> VARIABLES
%type <block> BLOCK
%type <label> LABEL
%type <codestatements> CODESTATEMENTS
%type <codestatement> CODESTATEMENT
%type <term> TERM
%type <ids> IDS
%type <numexp> NUMEXP
%type <expression> EXPRESSION
%type <boolexp> BOOLEXP
%type <identifierlist> IDENTIFIERLIST
%type <cgoto> GOTOSTATEMENT
%type <num> NUMBER
%type <str> IDENTIFIER
%type <str> STRING
/* TOKENS */
%start PROGRAM

%token CODEBLOCK 
%token DECLBLOCK 

%token INTEGER 
%token STRING

%token NE 
%token EQ 
%token EQEQ 
%token LE 
%token LT 
%token GT 
%token GE 

%token LBRACE 
%token RBRACE 
%token LBRACKET 
%token RBRACKET 
%token LPARAN 
%token RPARAN 
%token COMMA 

%token PLUS 
%token MINUS 
%token MUL 
%token DIV 
%token MOD 

%token FOR 
%token WHILE 
%token GOTO 
%token IF 
%token ELSE 

%token AND 
%token OR 
%token NOT 

%token READ
%token PRINT
%token PRINTLN

%token NUMBER 
%token IDENTIFIER


%left PLUS MINUS MUL DIV MOD

%%

PROGRAM : DECLBLOCK LBRACE DECLARATIONS RBRACE CODEBLOCK BLOCK { $$ = new C_PROGRAM($3, $6); ROOT = $$;}

DECLARATIONS : DECLARATION {$$ = $1;}
			 | DECLARATIONS DECLARATION {$1->insert($1->end(), $2->begin(), $2->end()); $$ = $1;}

DECLARATION : INTEGER DECLARATIONLIST ';' {$$ = $2;}
			| ';' {$$ = new vector<C_VARIABLES*> ;}

DECLARATIONLIST : VARIABLES {$$ = new vector <C_VARIABLES*>; $$->push_back($1);}
				| DECLARATIONLIST COMMA VARIABLES {$1->push_back($3); $$ = $1;}

VARIABLES : IDENTIFIER {$$ = new C_VARIABLES($1);}
		  | IDENTIFIER LBRACKET NUMBER RBRACKET {$$ = new C_VARIABLES($1, $3);}

BLOCK :	LBRACE CODESTATEMENTS RBRACE {$$ = new C_BLOCK($2);}
	  |	LBRACE RBRACE {$$ = new C_BLOCK();}

CODESTATEMENTS : CODESTATEMENT {$$ = new vector <C_CODESTATEMENT*>; $$->push_back($1);}
			   | CODESTATEMENT CODESTATEMENTS {$2->insert($2->begin(),$1); $$ = $2;}
			   | LABEL CODESTATEMENTS  { INTP_VISITOR->labelT.insert({$1->name,*$2});$$ = $2;}

CODESTATEMENT : INPUT ';' {$$ = $1;}
			  | ASSIGNMENT ';' {$$ = $1;}
			  | CONTROL {$$ = $1;}
			  |	LOOPS {$$ = $1;}  
			  |	OUTPUT ';' {$$ = $1;} 
			  | GOTOSTATEMENT ';' {$$ = $1;}

INPUT : READ IDENTIFIERLIST {$$ = new C_INPUT($2);}

LABEL : IDENTIFIER ':' {$$ = new C_LABEL($1);}

ASSIGNMENT 	: IDS EQ NUMEXP {$$ = new C_ASSIGNMENT($1, $3);}

CONTROL : IF BOOLEXP BLOCK ELSE BLOCK {$$ = new C_CONTROL($2, $3, $5);}
		| IF BOOLEXP BLOCK {$$ = new C_CONTROL($2, $3);}

GOTOSTATEMENT : GOTO IDENTIFIER IF BOOLEXP {$$ = new C_GOTO($2, $4);}
			  | GOTO IDENTIFIER {$$ = new C_GOTO($2);}

OUTPUT : PRINT EXPRESSION {$$ = new C_OUTPUT($2,0,"");}
	   | PRINTLN EXPRESSION {$$ = new C_OUTPUT($2,1,"");}
	   | PRINT STRING COMMA EXPRESSION {$$ = new C_OUTPUT($4,0,$2);}
	   | PRINTLN STRING COMMA EXPRESSION {$$ = new C_OUTPUT($4,1,$2);}

LOOPS :	FOR IDS EQ NUMBER COMMA NUMBER BLOCK {$$ = new C_FOR($2, $4, 1, $6, $7);}
	  | FOR IDS EQ NUMBER COMMA NUMBER COMMA NUMBER BLOCK {$$ = new C_FOR($2, $4, $6, $8, $9);}
	  | WHILE BOOLEXP BLOCK {$$ = new C_WHILE($2,$3);}

BOOLEXP : NUMEXP NE NUMEXP   {$$ = new C_BOOLEXP($1, REL_OP::_NE,   $3);}
		| NUMEXP EQEQ NUMEXP {$$ = new C_BOOLEXP($1, REL_OP::_EQEQ, $3);}
		| NUMEXP LE NUMEXP   {$$ = new C_BOOLEXP($1, REL_OP::_LE,   $3);}	
		| NUMEXP LT NUMEXP   {$$ = new C_BOOLEXP($1, REL_OP::_LT,   $3);}
		| NUMEXP GT NUMEXP   {$$ = new C_BOOLEXP($1, REL_OP::_GT,   $3);}
		| NUMEXP GE NUMEXP   {$$ = new C_BOOLEXP($1, REL_OP::_GE,   $3);}


EXPRESSION 	: NUMEXP  {$$ = new vector <C_NUMEXP*>; $$->push_back($1);}
			| EXPRESSION COMMA NUMEXP {$1->push_back($3); $$ = $1;}

NUMEXP	: TERM {$$ = $1;}
		| NUMEXP PLUS NUMEXP  {$$ = new C_BINEXP($1, ARITH_OP::_PLUS,  $3);}
	   	| NUMEXP MINUS NUMEXP {$$ = new C_BINEXP($1, ARITH_OP::_MINUS, $3);}
	   	| NUMEXP MUL NUMEXP   {$$ = new C_BINEXP($1, ARITH_OP::_MUL,   $3);}
	   	| NUMEXP DIV NUMEXP   {$$ = new C_BINEXP($1, ARITH_OP::_DIV,   $3);}
	   	| NUMEXP MOD NUMEXP   {$$ = new C_BINEXP($1, ARITH_OP::_MOD,   $3);}


IDENTIFIERLIST : IDS {$$ = new vector <C_IDS *> ; $$->push_back($1);}
			   | IDENTIFIERLIST COMMA IDS {$1->push_back($3); $$ = $1;}

TERM : IDS {$$ = new C_TERM($1,INT_MAX);}
	 | NUMBER {$$ = new C_TERM(NULL,$1);}

IDS : IDENTIFIER LBRACKET NUMEXP RBRACKET { $$ = new C_IDS($1, $3);}
	| IDENTIFIER {$$ = new C_IDS($1);}

%%

void yyerror (char const *s) {
       fprintf (stderr, "%s\n", s);
       fprintf (stderr, "Error @ %d\n",lines);
       exit(1);
}

int main(int argc, char *argv[])
{
	/* if (argc == 1 ) { */
	/* 	fprintf(stderr, "Correct usage: bcc filename\n"); */
	/* 	exit(1); */
	/* } */

	/* if (argc > 2) { */
	/* 	fprintf(stderr, "Passing more arguments than necessary.\n"); */
	/* 	fprintf(stderr, "Correct usage: bcc filename\n"); */
	/* 	exit(1); */
	/* } */

	/* yyin = fopen(argv[1], "r"); */
	/* if (!yyin) { */ 
	/* 	fprintf(stderr,"Some error in opening %s file\n",argv[1]); */
	/* 	exit(1); */
	/* } */
	/* yyparse(); */
	/* ROOT->visit(INTP_VISITOR); */
  BLOCKS.push(mainblock);
	FILE *myfile = fopen(argv[1], "r");
	yyin = myfile;
	do {
		yyparse();
	} while (!feof(yyin));
	ROOT->Codegen();
  legacy::PassManager pm;
  pm.add(createPrintModulePass(outs()));
  pm.run(*module);

		// do 
		// {
		// 		yyparse();
		// } while (!feof(yyin));
}

