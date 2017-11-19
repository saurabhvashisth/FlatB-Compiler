#include "AST.h"
#include <bits/stdc++.h>
using namespace std;

class C_VISITOR {
	public:
	// 	virtual void go(AstProgram* node) = 0;
	// 	virtual void go(AstEmptyD* node) = 0; 
	// 	virtual void go(AstEmptyC* node) = 0;
	// 	virtual void go(AstIdentifier* node) = 0;
	// 	virtual void go(AstCStatement* node) = 0;
	// 	virtual void go(AstAssignment* node) = 0;
	// 	virtual void go(AstPrinting* node) = 0;
	// 	virtual void go(AstForLoop* node) = 0;
	// 	virtual void go(AstIfElse* node) = 0;
	// 	virtual void go(AstWhileLoop* node) = 0;
	// 	virtual void go(AstReading* node) = 0;
	// 	virtual void go(AstPrintVals* node)=0;
	// 	virtual int go(AstExp* node) = 0;
	// 	virtual bool go(AstBoolExp* node) = 0;
	// 	virtual int go(AstBinaryExp* node) = 0;
	// 	virtual int go(AstTerm* node) = 0;
	// 	virtual void go(AstLabel *node)=0;
	// 	virtual string evaluate(AstIdentifier * node)=0;
};


class C_INTERPRETER : public C_VISITOR {
	public :
	unordered_map <string, int> symbolT;
	unordered_map <string, vector <C_CODESTATEMENTS*>> labelT;	

	/* ACCEPT FUNCTIONS */
	void accept (C_PROGRAM *var){
		var->block->visit(this);
	}

	void accept (C_BLOCK *var){
		for (auto it : *(var->cstatement)) it.visit(this);
	}
	
	void accept (C_VARIABLES *var){
		if (var->size == INT_MAX) symbolT[var->name] = 0;
		else {
			if (var->size < 0) {cout << "Error: Negative size of array" << var->name << endl; exit(-1);}
			for (int j = 0; j < var->size; j++)  symbolT[var->name + "[" + to_string(j) + "]"] = 0;
		}
	}

	void accept (C_ASSIGNMENT *var){
		int rvalue = var->exp->visit(this);
		symbolT[getId(var->ids)] = rvalue;
	}

	string getId (C_IDS *var){
		if (!symbolT.count(var->name)){ cout << "Error: Use of undeclared variable " << var->name << endl; exit(-1);} 
		if (var->numexp == NULL) return var->name;
		int index = var->numexp->visit(this);
		if (!symbolT.count(var->name + "[" + to_string(index) + "]")) { cout << "Error: Array out of bounds" << endl; exit(-1);}
		return var->name + "[" + to_string(index) + "]";
	}

	void accept (C_INPUT *var){
		for (auto it : *(var->ids)){
			int in; cin >> in;
			symbolT[it->getId(this)] = in;
		}
	}

	void accept (C_WHILE *var){
		while (var->exp->visit(this)) var->block->visit(this);
	}

	void accept (C_CONTROL *var){
		if (var->boolexp->visit(this)) var->block1->visit(this);
		else if (var->block2 != NULL)  var->block2->visit(this);
	}

	void accept (C_LABEL *var){
		if (symbolT.count(var->name)) {cout << "Error: variable with same name already declared" << endl; exit(-1);}
		if (labelT.count(var->name)) {cout << "Error: label with same name already declared" << endl; exit(-1);}
		labelT[var->name];
	}

	void accept (C_FOR *var){
		string it = var->id->getId(this);
		symbolT[it] = var->l;
		int EN = var->r, STP = var->st;
		if (STP == INT_MAX) STP = 1;
		for (;symbolT[it] < EN; symbolT[it] += STP);	
	}

	void accept (C_OUTPUT *var){
		for (auto it: *(var->exp)){
			cout << it->visit(this) << " " ;
		}
		if (ln) putchar(10);
	}

	int accept (C_TERM *var){
		if (var->ids == NULL) return var->number;
		else return symbolT[var->ids->getId(this)];
	}

	void accept (C_GOTO *var){
		if (!labelT.count(var->name)) {cout << "Error: goto label '"<< var->name << "' undeclared" << endl; exit(-1);}
		if (var->exp == NULL || var->exp->visit(this)){
			for (auto it: labelT[var->name]) it->visit(this);
			exit(0);
		}
	}

	int accept (C_NUMEXP *var){
		int o1 = var->left->visit(this), o2 = var->right->visit(this);
		if (var->op == ARITH_OP::_PLUS) return o1 + o2;
		if (var->op == ARITH_OP::_MINUS) return o1 - o2;
		if (var->op == ARITH_OP::_DIV) return o1 / o2;
		if (var->op == ARITH_OP::_MUL) return o1 * o2;
		cout << "Error: Undefined operation on operands" << endl; exit(-1);
	}

	bool accept (C_BOOLEXP *var){
		int o1 = var->left->visit(this), o2 = var->right->visit(this);
		if (var->op == REL_OP::_NE) return o1 != o2;
		if (var->op == REL_OP::_EQEQ) return o1 != o2;=
		if (var->op == REL_OP::_LE) return o1 <= o2;
		if (var->op == REL_OP::_GE) return o1 >= o2;
		if (var->op == REL_OP::_LT) return o1 < o2;
		if (var->op == REL_OP::_GT) return o1 > o2;
		cout << "Error: Undefined operation on operands" << endl; exit(-1);
	}

	void accept(C_CODESTATEMENT *var){
		C_ASSIGNMENT *asg = dynamic_cast<C_ASSIGNMENT*>(var);
		C_INPUT *inp = dynamic_cast<C_INPUT*>(var);
		C_OUTPUT *out = dynamic_cast<C_OUTPUT*>(var);
		C_CONTROL *cont = dynamic_cast<C_CONTROL*>(var);
		C_FOR *_for = dynamic_cast<C_FOR*>(var);
		C_WHILE *_while = dynamic_cast<C_WHILE*>(var);
		C_LABEL *label = dynamic_cast<C_LABEL*>(var);
		C_GOTO *go2 = dynamic_cast<C_GOTO*>(var);
		if (asg) asg->visit(this);
		else if (inp) inp->visit(this);
		else if (out) out->visit(this);
		else if (cont) cont->visit(this);
		else if (_for) _for->visit(this);
		else if (_while) _while->visit(this);
		else if (label) label->visit(this);
		else if (go2) go2->go(this);
		else {cout << "Error: Invalid Flat B expression" << endl; exit(-1); }
	}

	int accept(C_EXPRESSION *var){
		C_NUMEXP *numexp = dynamic_cast<C_NUMEXP*> (var);
		C_BOOLEXP *boolexp = dynamic_cast<C_BOOLEXP*> (var);
		C_TERM *someshitterm = dynamic_cast<C_TERM*> (var);
		if (numexp) return numexp->visit(this);
		else if (boolexp) return boolexp->visit(this);
		else if (someshitterm) someshitterm->visit(this);
		else {cout << "Error: Invalid Flat B expression" << endl; exit(-1);}
	}
};
