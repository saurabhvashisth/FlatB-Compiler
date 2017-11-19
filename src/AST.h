#ifndef _AST_H
#define _AST_H
#include "llvm/IR/Function.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/IRPrintingPasses.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Bitcode/BitstreamReader.h"
#include "llvm/Bitcode/BitstreamWriter.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/Support/raw_ostream.h"
#include <bits/stdc++.h>
using namespace std;
using namespace llvm;


vector<llvm::Type*> argTypes;
llvm::FunctionType *ftype = FunctionType::get(Type::getVoidTy(getGlobalContext()), makeArrayRef(argTypes), false);
Module *module = new Module("main", getGlobalContext());
Function *mainfunc = Function::Create(ftype, GlobalValue::InternalLinkage, "main", module);
BasicBlock *mainblock = BasicBlock::Create(getGlobalContext(), "entry", mainfunc, 0);
stack<BasicBlock*> BLOCKS;
IRBuilder<> Builder(mainblock);
map<std::string, Value*> VARS;
enum ARITH_OP { _PLUS, _MINUS, _MUL, _DIV, _MOD};
enum REL_OP { _NE, _EQEQ, _LE, _LT, _GT, _GE};


class C_PROGRAM; 
class C_DECL;
class C_DECLARATIONLIST;
class C_INPUT;
class C_OUTPUT ;
class C_CONTROL;
class C_LOOPS;
class C_LABEL;
class C_FOR ;
class C_WHILE;
class C_TERM;
class C_IDENTIFIERLIST;
class C_ASSIGNMENT;
class C_PROGRAM;
class C_DECL;
class C_NUMEXP;
class C_CODESTATEMENT ;
class C_BLOCK;
class C_IDS;
class C_BOOLEXP;
class C_VARIABLES;
class C_EXPRESSION;
class C_BINEXP;
class C_GOTO;
class C_INTERPRETER;
class C_VISITOR;
class C_NUM;
C_PROGRAM * ROOT;

class C_VISITOR {
  public:
    virtual int accept (C_NUMEXP *var) = 0;
    virtual bool accept (C_BOOLEXP *var) = 0;
    virtual void accept (C_PROGRAM *var) = 0;
    virtual string getId (C_IDS *var) = 0;
    virtual void accept (C_ASSIGNMENT *var) = 0;
    virtual void accept (C_IDS *var) = 0;
    virtual void accept (C_INPUT *var) = 0;
    virtual void accept (C_BLOCK *var) = 0;
    virtual void accept (C_VARIABLES *var) = 0;
    virtual void accept (C_WHILE *var) = 0;
    virtual void accept (C_CONTROL *var) = 0;
    virtual void accept (C_LABEL *var) = 0;
    virtual void accept (C_FOR *var) = 0;
    virtual void accept (C_OUTPUT *var) = 0;
    virtual void accept (C_GOTO *var) = 0;
    virtual void accept(C_CODESTATEMENT *var) = 0;
    virtual int accept(C_EXPRESSION *var) = 0;
    virtual void accept (C_DECLARATIONLIST *var) = 0;
    virtual int accept (C_TERM *var) = 0;
};

class AST_Node{
  public :
    virtual Value *Codegen(){
    }
};

class C_PROGRAM : public AST_Node {
  public :
    vector <C_VARIABLES*>* decl;
    C_BLOCK * block;
    C_PROGRAM(vector <C_VARIABLES*> *decl, C_BLOCK *block){
      this->decl = decl; this->block = block;
    }
    void visit(C_VISITOR *V){ V->accept(this);}
    virtual Value *Codegen();
};

class C_VARIABLES : public AST_Node {
  public :
    string name;
    int size;
    C_VARIABLES(string _name, int _size = INT_MAX){
      name = _name; size = _size;
    }
    void visit(C_VISITOR *V){ V->accept(this);}
    virtual Value *Codegen();
};

class C_BLOCK : public AST_Node {
  public :
    vector <C_CODESTATEMENT*> *cstatement;
    C_BLOCK(vector <C_CODESTATEMENT*> *var = NULL){
      this->cstatement = var;
    }
    void visit(C_VISITOR *V){ V->accept(this);}
    virtual Value *Codegen();
};

class C_DECLARATIONLIST : public AST_Node {
  public :
    vector <C_VARIABLES*> *variables;
    C_DECLARATIONLIST(vector <C_VARIABLES*> *var){
      this->variables = var;
    }
    void visit(C_VISITOR *V){ V->accept(this);}
    virtual Value *Codegen();
};


class C_CODESTATEMENT : public AST_Node {
  public :
    virtual ~C_CODESTATEMENT() {}
    void visit(C_VISITOR *V){ V->accept(this);}
    virtual Value *Codegen(){
    }
};

class C_ASSIGNMENT : public C_CODESTATEMENT {
  public :
    C_IDS *ids; 
    C_NUMEXP *exp;
    C_ASSIGNMENT(C_IDS *_ids, C_NUMEXP *_exp){
      ids = _ids; exp = _exp; 
    }
    void visit(C_VISITOR *V){ V->accept(this);}
    virtual Value *Codegen();
};

class C_INPUT : public C_CODESTATEMENT {
  public :
    vector <C_IDS *> *ids;
    C_INPUT(vector <C_IDS *> *_ids){
      ids = _ids;
    }
    void visit(C_VISITOR *V){ V->accept(this);}
};

class C_OUTPUT : public C_CODESTATEMENT {
  public :
    vector <C_NUMEXP*> *exp;
    int ln;
    string txt;
    C_OUTPUT(vector<C_NUMEXP*> *_exp, int _ln, string _txt){
      ln = _ln;
      exp = _exp;
      txt = _txt;
    }
    void visit(C_VISITOR *V){ V->accept(this);}
};

class C_CONTROL : public C_CODESTATEMENT {
  public :
    C_BOOLEXP *boolexp;
    C_BLOCK *block1, *block2;
    C_CONTROL(C_BOOLEXP *_exp, C_BLOCK *_b1, C_BLOCK *_b2 = NULL){
      boolexp = _exp; block1 = _b1; block2 = _b2;
    }
    void visit(C_VISITOR *V){ V->accept(this);}
    /* virtual Value *Codegen(); */
};

class C_LOOPS : public C_CODESTATEMENT {
  public :
    virtual ~C_LOOPS(){}
    void visit(C_VISITOR *V){ V->accept(this);}
    /* virtual Value *Codegen(); */
};

class C_LABEL : public C_CODESTATEMENT {
  public :
    string name;
    C_LABEL(string _name){
      name = _name;
    }
    void visit(C_VISITOR *V){ V->accept(this);}
    /* virtual Value *Codegen(); */
};

class C_GOTO: public C_CODESTATEMENT {
  public:
    string name;
    C_BOOLEXP * exp;
    C_GOTO(string _name, C_BOOLEXP * _exp = NULL){
      name = _name; exp = _exp;
    }
    void visit(C_VISITOR *V){ V->accept(this);}
    /* virtual Value *Codegen(); */
};

class C_FOR : public C_LOOPS {
  public :
    C_IDS * id; 
    C_BLOCK * block;
    int l, r, st;
    C_FOR(C_IDS * _id, int _l, int _st, int _r, C_BLOCK * _blk){
      id = _id; l = _l; r = _r; block = _blk; st = _st;
    }
    void visit(C_VISITOR *V){ V->accept(this);}
    virtual Value *Codegen();
};

class C_WHILE : public C_LOOPS {
  public :
    C_BOOLEXP *exp;
    C_BLOCK * block;
    C_WHILE(C_BOOLEXP *_exp, C_BLOCK *_block){
      exp = _exp; block = _block;
    }
    void visit(C_VISITOR *V){ V->accept(this);}
    /* virtual Value *Codegen(); */
};

class C_EXPRESSION : public AST_Node {
  public :
    virtual ~C_EXPRESSION() {}
    int visit(C_VISITOR *V){ return V->accept(this);}
    /* virtual Value *Codegen(); */
};

class C_NUMEXP : public C_EXPRESSION {
  public :
    virtual ~C_NUMEXP() {}
    /* virtual Value *Codegen() = 0; */
};

class C_BINEXP : public C_NUMEXP {
  public :
    C_NUMEXP *lft, *rt;
    ARITH_OP op;
    C_BINEXP(C_NUMEXP *_lft, ARITH_OP _op, C_NUMEXP * _rt){
      lft = _lft; op = _op; rt = _rt;
    }
    int visit(C_VISITOR *V){ return V->accept(this);}
    virtual Value *Codegen();
};


class C_NUM: public C_NUMEXP {
  public :
    int num;
    C_NUM(int _num){
      num = _num;
    }
    virtual Value* Codegen();
};



class C_TERM : public C_NUMEXP {
  public :
    C_IDS *ids;
    C_NUM *num;
    int number;
    C_TERM(C_IDS * _id, int _num){
      ids = _id; number = _num;
      if (number != INT_MAX) num = new C_NUM(number);
      else num = NULL;
    }
    int visit(C_VISITOR *V){ return V->accept(this);}
    virtual Value *Codegen();
};



class C_IDS : public AST_Node {
  public :
    string name;
    C_NUMEXP * numexp;
    C_IDS(string _id, C_NUMEXP *tmp = NULL){
      name = _id; numexp = tmp;
    }
    void visit(C_VISITOR *V){ V->accept(this);}
    virtual string getId (C_VISITOR *V) {return V->getId(this);}
    virtual Value *Codegen();
};

class C_BOOLEXP: public C_EXPRESSION {
  public :
    C_NUMEXP *lft, *rt;
    Value *L, *R;
    REL_OP op;
    C_BOOLEXP(C_NUMEXP *_lft, REL_OP _op, C_NUMEXP *_rt){
      lft = _lft; rt = _rt; op = _op;
      L = NULL, R = NULL;
    }
    C_BOOLEXP(Value *_L, REL_OP _op, Value *_R){
      L = _L, R = _R;
      lft = NULL, rt = NULL;
    }
    bool visit(C_VISITOR *V){ return V->accept(this);}
    virtual Value *Codegen();
};

Value* C_PROGRAM::Codegen(){
  Value* ret;
  for (auto it: *(this->decl)) ret = it->Codegen();
  ret = this->block->Codegen();
  return ret;
}

Value* C_DECLARATIONLIST::Codegen(){
  Value *ret;
  for (auto it: *(this->variables)) ret = it->Codegen();
  return ret;
}

Value* C_BLOCK::Codegen(){
  Value * ret;	
  for (auto it : *(this->cstatement)) ret = it->Codegen();
  return ret;
}

Value* C_ASSIGNMENT::Codegen(){
  return new llvm::StoreInst(exp->Codegen(), VARS[ids->name], false, BLOCKS.top());
}

Value* C_NUM::Codegen(){
  return ConstantInt::get(Type::getInt32Ty(getGlobalContext()), this->num, true);
}

Value* C_BOOLEXP::Codegen(){
  Value *tL; 
  Value *tR; 
  if (this->L == NULL && this->R == NULL){
    tL = this->lft->Codegen();
    tR = this->rt->Codegen();
  } else {
    tL = L, tR = R;
  }
  if (tL == 0 || tR == 0) return 0;
  if (this->op == REL_OP::_NE) tL = Builder.CreateFCmpUNE(tL, tR, "cmpnetmp");
  if (this->op == REL_OP::_EQEQ) tL = Builder.CreateFCmpUEQ(tL, tR, "cmpeqtmp");
  if (this->op == REL_OP::_LE) tL = Builder.CreateFCmpULE(tL, tR, "cmpletmp");
  if (this->op == REL_OP::_GE) tL = Builder.CreateFCmpUGE(tL, tR, "cmpgetmp");
  if (this->op == REL_OP::_LT) tL = Builder.CreateFCmpULT(tL, tR, "cmpltmp");
  if (this->op == REL_OP::_GT) tL = Builder.CreateFCmpUGT(tL, tR, "cmpgtmp");
  return Builder.CreateUIToFP(tL, Type::getDoubleTy(getGlobalContext()), "booltmp");
}

Value* C_BINEXP::Codegen(){
  Value* L = this->lft->Codegen();
  Value* R = this->rt->Codegen();
  if (this->op == ARITH_OP::_PLUS) return Builder.CreateFAdd(L, R, "addtmp");
  if (this->op == ARITH_OP::_MINUS) return Builder.CreateFSub(L, R, "subtmp");
  if (this->op == ARITH_OP::_DIV) return Builder.CreateFDiv(L, R, "divtmp");
  if (this->op == ARITH_OP::_MUL) return Builder.CreateFMul(L, R, "multmp");
}

Value* C_IDS::Codegen(){
  cout << "Declaration for " << this->name << '\n';
  AllocaInst *alloc = new AllocaInst(IntegerType::get(getGlobalContext(), 32), this->name.c_str(), BLOCKS.top());
  VARS[this->name] = alloc;
  if(this->numexp != NULL){
    C_ASSIGNMENT* asn = new C_ASSIGNMENT(new C_IDS(this->name),this->numexp);
    cout << name << '\n';
    asn->Codegen();
  }
  return alloc;
}

Value* C_TERM::Codegen(){
  if (this->ids == NULL) return this->num->Codegen();
  else return this->ids->Codegen();
}
// see this
Value *C_VARIABLES::Codegen(){
  AllocaInst *alloc = new AllocaInst(IntegerType::get(getGlobalContext(), 32), this->name.c_str(), BLOCKS.top());
  VARS[name] = alloc;
  return alloc;
}

void pushBlock(BasicBlock *block){
  BLOCKS.push(block);
}

Value* C_FOR::Codegen(){
  C_ASSIGNMENT *asn = new C_ASSIGNMENT(id, new C_TERM(NULL,this->l));
  asn->Codegen();

  Function *TheFunction = mainfunc;
  BasicBlock *PreheaderBB = Builder.GetInsertBlock();
  BasicBlock *LoopBB = BasicBlock::Create(getGlobalContext(), "FOR LOOP", TheFunction);

  Builder.CreateBr(LoopBB);
  Builder.SetInsertPoint(LoopBB);
  pushBlock(LoopBB);

  this->block->Codegen();

  C_NUM* cnum = new C_NUM(this->st);
  Value *step = cnum->Codegen();


  Value *right = BinaryOperator::Create(Instruction::Add, VARS[this->id->name], step, "Next Iteration", BLOCKS.top());
  VARS[this->id->name] = right;
  
  cnum = new C_NUM(this->r);
  Value* limit = cnum->Codegen();


  C_BOOLEXP *lastexp = new C_BOOLEXP(VARS[this->id->name],REL_OP::_LT, limit); 
  Value *lastval = lastexp->Codegen();

  FCmpInst *comparison = new FCmpInst(*BLOCKS.top(), FCmpInst::FCMP_UNE, lastval, ConstantFP::get(getGlobalContext(), APFloat(0.0)), "CMP");

  BLOCKS.pop();

  BasicBlock *LoopEndBB = Builder.GetInsertBlock();
  BasicBlock *AfterBB =
    BasicBlock::Create(getGlobalContext(), "FOR LOOP END", TheFunction);

  Builder.CreateCondBr(comparison, LoopBB, AfterBB);

  Builder.SetInsertPoint(AfterBB);
  pushBlock(AfterBB);

  return Constant::getNullValue(Type::getDoubleTy(getGlobalContext()));
}


class C_INTERPRETER : public C_VISITOR {
  public :
    unordered_map <string, int> symbolT;
    unordered_map <string, vector <C_CODESTATEMENT*> > labelT;	

    /* ACCEPT FUNCTIONS */
    void accept (C_PROGRAM *var){
      // cout << "program" << endl;
      for (auto it: *(var->decl)) it->visit(this);
      var->block->visit(this);
    }

    void accept (C_DECLARATIONLIST *var){
      for (auto it: *(var->variables)) it->visit(this);
    }

    void accept (C_BLOCK *var){
      for (auto it : *(var->cstatement)) it->visit(this);
    }

    void accept (C_ASSIGNMENT *var){
      int rvalue = var->exp->visit(this);
      // cout << "rvalue " << endl;
      symbolT[getId(var->ids)] = rvalue;
    }

    void accept (C_VARIABLES *var){
      // cout << "Cvariables" << endl;
      if (var->size == INT_MAX) symbolT[var->name] = 0;
      else {
        symbolT[var->name] = 0;
        if (var->size < 0) {cout << "Error: Negative size of array" << var->name << endl; exit(-1);}
        for (int j = 0; j < var->size; j++){ 
          // cout << var->name << " " << j << endl;
          symbolT[var->name + "[" + to_string(j) + "]"] = 0;
        }
      }
    }

    void accept (C_IDS *var){
      if (var->numexp == NULL) symbolT[var->name] = 0;
      else {
        int size = var->numexp->visit(this);
        if (size < 0) {cout << "Error: Negative size of array" << var->name << endl; exit(-1);}
        for (int j = 0; j < size; j++)  symbolT[var->name + "[" + to_string(j) + "]"] = 0;
      }
    }

    string getId (C_IDS *var){
      // cout << "getid" << endl;
      // cout << var->name << " name" << endl;
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
      // cout << "for loop" << endl;
      string it = var->id->getId(this);
      symbolT[it] = var->l;
      int EN = var->r, STP = var->st;
      if (STP == INT_MAX) STP = 1;
      for (;symbolT[it] < EN; ){
        // cout << it << " " << symbolT[it] << endl;
        symbolT[it] += STP;
        var->block->visit(this);
      }
    }

    void accept (C_OUTPUT *var){
      if (var->txt.size()) cout << var->txt << " ";
      for (auto it: *(var->exp)){
        cout << it->visit(this) << " " ;
      }
      if (var->ln) putchar(10);
    }

    int accept (C_TERM *var){
      if (var->ids == NULL) return var->number;
      else return symbolT[var->ids->getId(this)];
    }

    int accept (C_NUMEXP *var){	
      // cout << "numexp" << endl;
      C_BINEXP * binexp = dynamic_cast<C_BINEXP*> (var);
      C_TERM *term = dynamic_cast<C_TERM*> (var);
      if (term) {return term->visit(this);}
      int o1 = binexp->lft->visit(this), o2 = binexp->rt->visit(this);
      ARITH_OP _op = binexp->op;
      if (_op == ARITH_OP::_PLUS) return o1 + o2;
      if (_op == ARITH_OP::_MINUS) return o1 - o2;
      if (_op == ARITH_OP::_DIV) return o1 / o2;
      if (_op == ARITH_OP::_MUL) return o1 * o2;
      cout << "Error: Undefined operation on operands" << endl; exit(-1);
    }

    bool accept (C_BOOLEXP *var){
      int o1 = var->lft->visit(this), o2 = var->rt->visit(this);
      if (var->op == REL_OP::_NE) return o1 != o2;
      if (var->op == REL_OP::_EQEQ) return o1 != o2;
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
      C_LOOPS * loops = dynamic_cast<C_LOOPS*>(var);
      C_LABEL *label = dynamic_cast<C_LABEL*>(var);
      C_GOTO *go2 = dynamic_cast<C_GOTO*>(var);
      if (asg != NULL) {asg->visit(this);}
      else if (inp != NULL) {inp->visit(this);}
      else if (cont != NULL) {cont->visit(this);}
      else if (loops != NULL) {
        C_FOR *_for = dynamic_cast<C_FOR*>(loops);
        C_WHILE *_while = dynamic_cast<C_WHILE*>(loops);
        if (_for != NULL) _for->visit(this);
        else if (_while != NULL) _while->visit(this);
        else {cout <<"Error: Undefined loops" << endl; exit(-1);}
      }
      else if (out != NULL) {out->visit(this);}
      else if (label != NULL) label->visit(this);
      else if (go2 != NULL) go2->visit(this);
      else {cout << "Error: Invalid Flat B expression" << endl; exit(-1); }
    }

    void accept (C_GOTO *var){
      if (!labelT.count(var->name)) {cout << "Error: goto label '"<< var->name << "' undeclared" << endl; exit(-1);}
      if (var->exp == NULL || var->exp->visit(this)){
        for (auto it: labelT[var->name]) it->visit(this);
        exit(0);
      }
    }

    int accept(C_EXPRESSION *var){
      C_NUMEXP *numexp = dynamic_cast<C_NUMEXP*> (var);
      C_BOOLEXP *boolexp = dynamic_cast<C_BOOLEXP*> (var);
      if (numexp) return accept(numexp);
      else if (boolexp) return accept(boolexp);
      else {cout << "Error: Invalid Flat B expression" << endl; exit(-1);}
    }
};

C_INTERPRETER *INTP_VISITOR = new C_INTERPRETER;
#endif
