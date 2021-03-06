
//**************************************************************
//
// Code generator SKELETON
//
//
//**************************************************************

#include <ctype.h>
#include <stdio.h>
#include "cgen.h"
#include "cgen_gc.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <sstream>
#include "symtab.h"

using namespace std;

extern void emit_string_constant(ostream& str, char *s);
extern int cgen_debug;

static char *CALL_REGS[] = {RDI, RSI, RDX, RCX, R8, R9};
static char *CALL_XMM[] = {XMM0, XMM1, XMM2, XMM3};

void cgen_helper(Decls decls, ostream& s);
void code(Decls decls, ostream& s);

//////////////////////////////////////////////////////////////////
//
//
//    Helper Functions
//  
//
//////////////////////////////////////////////////////////////////

// you can add any helper functions here


//////////////////////////////////////////////////////////////////////
//
// Symbols
//
// For convenience, a large number of symbols are predefined here.
// These symbols include the primitive type and method names, as well
// as fixed names used by the runtime system.
//
//////////////////////////////////////////////////////////////////////
Symbol 
    Int,
    Float,
    String,
    Bool,
    Void,
    Main,
    print
    ;
//
// Initializing the predefined symbols.
//
static void initialize_constants(void)
{
    // 4 basic types and Void type
    Bool        = idtable.add_string("Bool");
    Int         = idtable.add_string("Int");
    String      = idtable.add_string("String");
    Float       = idtable.add_string("Float");
    Void        = idtable.add_string("Void");  
    // main function
    Main        = idtable.add_string("main");

    // classical function to print things, so defined here for call.
    print        = idtable.add_string("printf");
}


//*********************************************************
//
// Define method for code generation
//
//
//*********************************************************

void Program_class::cgen(ostream &os) 
{
  // spim wants comments to start with '#'
  os << "# start of generated code\n";

  initialize_constants();
  cgen_helper(decls,os);

  os << "\n# end of generated code\n";
}


//////////////////////////////////////////////////////////////////////////////
//
//  emit_* procedures
//
//  emit_X  writes code for operation "X" to the output stream.
//  There is an emit_X for each opcode X, as well as emit_ functions
//  for generating names according to the naming conventions (see emit.h)
//  and calls to support functions defined in the trap handler.
//
//  Register names and addresses are passed as strings.  See `emit.h'
//  for symbolic names you can use to refer to the strings.
//
//////////////////////////////////////////////////////////////////////////////

static void emit_mov(const char *source, const char *dest, ostream& s)
{
  s << MOV << source << COMMA << dest << endl;
}

static void emit_rmmov(const char *source_reg, int offset, const char *base_reg, ostream& s)
{
  s << MOV << source_reg << COMMA << offset << "(" << base_reg << ")"
      << endl;
}

static void emit_mrmov(const char *base_reg, int offset, const char *dest_reg, ostream& s)
{
  s << MOV << offset << "(" << base_reg << ")" << COMMA << dest_reg  
      << endl;
}

static void emit_irmov(const char *immidiate, const char *dest_reg, ostream& s)
{
  s << MOV << "$" << immidiate << COMMA << dest_reg  
      << endl;
}

static void emit_irmovl(const char *immidiate, const char *dest_reg, ostream& s)
{
  s << MOVL << "$" << immidiate << COMMA << dest_reg  
      << endl;
}

static void emit_immov(const char *immidiate, int offset, const char *base_reg, ostream& s)
{
  s << MOV << "$" << immidiate << COMMA << "(" << offset << ")" << base_reg  
      << endl;
}

static void emit_add(const char *source_reg, const char *dest_reg, ostream& s)
{
  s << ADD << source_reg << COMMA << dest_reg << endl;
}

static void emit_sub(const char *source_reg, const char *dest_reg, ostream& s)
{
  s << SUB << source_reg << COMMA << dest_reg << endl;
}

static void emit_mul(const char *source_reg, const char *dest_reg, ostream& s)
{
  s << MUL << source_reg << COMMA << dest_reg << endl;
}

static void emit_div(const char *dest_reg, ostream& s)
{
  s << DIV << dest_reg << endl;
}

static void emit_cqto(ostream &s)
{
  s << CQTO << endl;
}

static void emit_neg(const char *dest_reg, ostream& s)
{
  s << NEG << dest_reg << endl;
}

static void emit_and(const char *source_reg, const char *dest_reg, ostream& s)
{
  s << AND << source_reg << COMMA << dest_reg << endl;
}

static void emit_or(const char *source_reg, const char *dest_reg, ostream& s)
{
  s << OR << source_reg << COMMA << dest_reg << endl;
}

static void emit_xor(const char *source_reg, const char *dest_reg, ostream& s)
{
  s << XOR << source_reg << COMMA << dest_reg << endl;
}

static void emit_not(const char *dest_reg, ostream& s)
{
  s << NOT << " " << dest_reg << endl;
}

static void emit_movsd(const char *source, const char *dest, ostream& s)
{
  s << MOVSD << source << COMMA << dest << endl;
}

static void emit_movaps(const char *source, const char *dest, ostream& s)
{
  s << MOVAPS << source << COMMA << dest << endl;
}

static void emit_addsd(const char *source_reg, const char *dest_reg, ostream& s)
{
  s << ADDSD << source_reg << COMMA << dest_reg << endl;
}

static void emit_subsd(const char *source_reg, const char *dest_reg, ostream& s)
{
  s << SUBSD << source_reg << COMMA << dest_reg << endl;
}

static void emit_mulsd(const char *source_reg, const char *dest_reg, ostream& s)
{
  s << MULSD << source_reg << COMMA << dest_reg << endl;
}

static void emit_divsd(const char *source_reg, const char *dest_reg, ostream& s)
{
  s << DIVSD << source_reg << COMMA << dest_reg << endl;
}

static void emit_cmp(const char *source_reg, const char *dest_reg, ostream& s)
{
  s << CMP << source_reg << COMMA << dest_reg << endl;
}

static void emit_test(const char *source_reg, const char *dest_reg, ostream& s)
{
  s << TEST << source_reg << COMMA << dest_reg << endl;
}

static void emit_ucompisd(const char *source_reg, const char *dest_reg, ostream& s)
{
  s << UCOMPISD << source_reg << COMMA << dest_reg << endl;
}

static void emit_xorpd(const char *source_reg, const char *dest_reg, ostream& s)
{
  s << XORPD << source_reg << COMMA << dest_reg << endl;
}
static void emit_jmp(const char *dest, ostream& s)
{
  s << JMP << " " << dest << endl;
}

static void emit_jl(const char *dest, ostream& s)
{
  s << JL << " " << dest << endl;
}

static void emit_jle(const char *dest, ostream& s)
{
  s << JLE << " " << dest << endl;
}

static void emit_je(const char *dest, ostream& s)
{
  s << JE << " " << dest << endl;
}

static void emit_jne(const char *dest, ostream& s)
{
  s << JNE << " " << dest << endl;
}

static void emit_jg(const char *dest, ostream& s)
{
  s << JG << " " << dest << endl;
}

static void emit_jge(const char *dest, ostream& s)
{
  s << JGE << " " << dest << endl;
}

static void emit_jb(const char *dest, ostream& s)
{
  s << JB << " " << dest << endl;
}

static void emit_jbe(const char *dest, ostream& s)
{
  s << JBE << " " << dest << endl;
}

static void emit_ja(const char *dest, ostream& s)
{
  s << JA << " " << dest << endl;
}

static void emit_jae(const char *dest, ostream& s)
{
  s << JAE << " " << dest << endl;
}

static void emit_jp(const char *dest, ostream& s)
{
  s << JP << " " << dest << endl;
}

static void emit_jz(const char *dest, ostream& s)
{
  s << JZ << " " << dest << endl;
}

static void emit_jnz(const char *dest, ostream& s)
{
  s << JNZ << " " << dest << endl;
}

static void emit_call(const char *dest, ostream& s)
{
  s << CALL << " " << dest << endl;
}

static void emit_ret(ostream& s)
{
  s << RET << endl;
}

static void emit_push(const char *reg, ostream& s)
{
  s << PUSH << " " << reg << endl;
}

static void emit_pop(const char *reg, ostream& s)
{
  s << POP << " " << reg << endl;
}

static void emit_leave(ostream& s)
{
  s << LEAVE << endl;
}

static void emit_position(const char *p, ostream& s)
{
  s << p << ":" << endl;
}

static void emit_float_to_int(const char *float_mmx, const char *int_reg, ostream& s)
{
  s << CVTTSD2SIQ << float_mmx << COMMA << int_reg << endl;
}

static void emit_int_to_float(const char *int_reg, const char *float_mmx, ostream& s)
{
  s << CVTSI2SDQ << int_reg << COMMA << float_mmx << endl;
}
///////////////////////////////////////////////////////////////////////////////
//
// coding strings, ints, and booleans
//
// Seal has four kinds of constants: strings, ints, and booleans.
// This section defines code generation for each type.
//
// If you like, you can add any ***Entry::code_def() and ***Entry::code_ref()
// functions to help.
//
///////////////////////////////////////////////////////////////////////////////

//
// Strings
//
void StringEntry::code_ref(ostream& s)
{
  s << "$" << STRINGCONST_PREFIX << index;
}

//
// Emit code for a constant String.
//

void StringEntry::code_def(ostream& s)
{
  s << STRINGCONST_PREFIX << index << ":" << endl;
  s  << STRINGTAG ; emit_string_constant(s,str);                                                // align to word
}

//
// StrTable::code_string
// Generate a string object definition for every string constant in the 
// stringtable.
//
void StrTable::code_string_table(ostream& s)
{  
  for (List<StringEntry> *l = tbl; l; l = l->tl())
    l->hd()->code_def(s);
}

// the following 2 functions are useless, please DO NOT care about them
void FloatEntry::code_ref(ostream &s)
{
  s << FLOATTAG << index;
}

void IntEntry::code_def(ostream &s)
{
  s << GLOBAL;
}

//***************************************************
//
//  Emit global var and functions.
//
//***************************************************

static void emit_global_int(Symbol name, ostream& s) {
  s << GLOBAL << name << endl << 
  ALIGN << 8 << endl << 
  SYMBOL_TYPE << name << COMMA << OBJECT << endl <<
  SIZE << name << COMMA << 8 << endl << 
  name << ":" << endl << 
  INTTAG << 0 << endl;
}

static void emit_global_float(Symbol name, ostream& s) {
  s << GLOBAL << name << endl << 
  ALIGN << 8 << endl << 
  SYMBOL_TYPE << name << COMMA << OBJECT << endl <<
  SIZE << name << COMMA << 8 << endl << 
  name << ":" << endl <<
  FLOATTAG << 0 << endl <<
  FLOATTAG << 0 << endl;
}

static void emit_global_bool(Symbol name, ostream& s) {
  s << GLOBAL << name << endl << 
  ALIGN << 8 << endl << 
  SYMBOL_TYPE << name << COMMA << OBJECT << endl <<
  SIZE << name << COMMA << 8 << endl << 
  name << ":" << endl << 
  BOOLTAG << 0 << endl;
}

// StrTable str_table;
int rbp_top = -56;  //当前栈指针的位置
bool is_float_calulate=0; //区别浮点数运算和整数运算
bool is_e1 = true; //算数表达式里的第一个操作数
int e1_shift = 0; //算数表达式里第一个操作数的偏移量
int e2_shift = 0;
int position_num = 0; //POS的标识
int position_num_current =0; //已经定义的POS
Symbol globalVar;
SymbolTable<char *,int> *var_shift = new SymbolTable<char *, int>();
SymbolTable<char *,int> *global_var = new SymbolTable<char *, int>();
int global_var_num=0;
// SymbolTable<int ,int> *int_shift = new SymbolTable<int, int>();

void code_global_data(Decls decls, ostream &str)
{
  // 初始化变量-偏移表
  var_shift->enterscope();
}

void code_calls(Decls decls, ostream &str) {

}

//***************************************************
//
//  Emit code to start the .text segment and to
//  declare the global names.
//
//***************************************************



//********************************************************
//
// Cgen helper helps to initialize and call code() function.
// You can do any initializing operations here
//
//********************************************************

void cgen_helper(Decls decls, ostream& s)
{
  code(decls, s);
}


void code(Decls decls, ostream& s)
{
  if (cgen_debug) cout << "Coding global data" << endl;
  bool have_global_var=false;
  code_global_data(decls, s);
  global_var->enterscope();
  for(int i=decls->first();decls->more(i); i=decls->next(i))
  {
    if(!decls->nth(i)->isCallDecl())
    {
      if(!have_global_var) s << DATA<<endl;
      have_global_var=true;
      s << GLOBAL << decls->nth(i)->getName()->get_string()<<endl;
      s << ALIGN << 8 << endl;
      s << SYMBOL_TYPE << decls->nth(i)->getName()->get_string() << COMMA << OBJECT<<endl;
      s << SIZE << decls->nth(i)->getName()->get_string()<< COMMA << 8 <<endl;
      s << decls->nth(i)->getName()->get_string()<<':'<<endl;
      if(decls->nth(i)->getType()==Int) s << INTTAG << 0 <<endl;
      else if(decls->nth(i)->getType()==Bool)
      {
        s << FLOATTAG << 0<<endl;
      }
      else
      {
        s << FLOATTAG << 0<<endl;
        s << FLOATTAG << 0<<endl;
      }
      
      int* shift=new int(global_var_num++);
      global_var->addid(decls->nth(i)->getName()->get_string(),shift);      
    }
  }

  s << SECTION << RODATA << endl; // 是否始终只有一个？
  stringtable.code_string_table(s);
  s<< TEXT<<endl;

  if (cgen_debug) cout << "Coding calls" << endl;
  code_calls(decls, s);
  for(int i=decls->first();decls->more(i); i=decls->next(i))
  {
    rbp_top = -56;  //printf偏移量
    if(decls->nth(i)->isCallDecl())
    {
      decls->nth(i)->code(s);
    }
  }
}

//******************************************************************
//
//   Fill in the following methods to produce code for the
//   appropriate expression.  You may add or remove parameters
//   as you wish, but if you do, remember to change the parameters
//   of the declarations in `seal-decl.h', `seal-expr.h' and `seal-stmt.h'
//   Sample code for constant integers, strings, and booleans are provided.
//   
//*****************************************************************

void CallDecl_class::code(ostream &s) {
  var_shift->enterscope();
  s<<GLOBAL<<name<<endl;
  s<<SYMBOL_TYPE<<name<<COMMA<<FUNCTION<<endl;
  s <<name<<':'<<endl;
  emit_push(RBP,s);
  emit_mov(RSP, RBP,s);
  emit_push(RBX,s);
  emit_push(R10,s);
  emit_push(R11,s);
  emit_push(R12,s);
  emit_push(R13,s);
  emit_push(R14,s);
  emit_push(R15,s);

  // if(name==Main)  rbp_top+=56;
  int paras_num=0;
  for(int i=paras->first(); paras->more(i); i=paras->next(i))
  {
    // paras->nth(i)
    paras_num++;
    emit_sub("$8",RSP,s);
    rbp_top -= 8;    
    if(global_var->lookup(paras->nth(i)->getName()->get_string()))
    {
      switch (paras_num)
      {
      case 1: {if(paras->nth(i)->getType()==Int)  {s << MOV << RDI << COMMA <<  paras->nth(i)->getName()->get_string() << '(' << RIP << ')'<<endl;break;}
              else {s << MOV << XMM0 << COMMA <<  rbp_top << '(' << RBP << ')'<<endl;break;}}
      case 2: {if(paras->nth(i)->getType()==Int)  {s << MOV << RSI << COMMA <<  paras->nth(i)->getName()->get_string() << '(' << RIP << ')'<<endl;break;}
              else {s << MOV << XMM1 << COMMA <<  rbp_top << '(' << RBP << ')'<<endl;break;}}
      case 3: {if(paras->nth(i)->getType()==Int)  {s << MOV << RDX << COMMA <<  paras->nth(i)->getName()->get_string() << '(' << RIP << ')'<<endl;break;}
              else {s << MOV << XMM2 << COMMA <<  rbp_top << '(' << RBP << ')'<<endl;break;}}
      case 4: {if(paras->nth(i)->getType()==Int)  {s << MOV << RCX << COMMA <<  paras->nth(i)->getName()->get_string() << '(' << RIP << ')'<<endl;break;}
              else {s << MOV << XMM3 << COMMA <<  rbp_top << '(' << RBP << ')'<<endl;break;}}
      case 5: {if(paras->nth(i)->getType()==Int)  {s << MOV << R8 << COMMA <<  paras->nth(i)->getName()->get_string() << '(' << RIP << ')'<<endl;break;}
              else {s << MOV << XMM4 << COMMA <<  rbp_top << '(' << RBP << ')'<<endl;break;}}
      case 6: {if(paras->nth(i)->getType()==Int)  {s << MOV << R9 << COMMA <<  paras->nth(i)->getName()->get_string() << '(' << RIP << ')'<<endl;break;}
              else {s << MOV << XMM5 << COMMA <<  rbp_top << '(' << RBP << ')'<<endl;break;}}
      default:  break;
      }
    }
    else
    {
      switch (paras_num)
      {
      case 1: {if(paras->nth(i)->getType()==Int)  {s << MOV << RDI << COMMA <<  rbp_top << '(' << RBP << ')'<<endl;break;}
              else {s << MOV << XMM0 << COMMA <<  rbp_top << '(' << RBP << ')'<<endl;break;}}
      case 2: {if(paras->nth(i)->getType()==Int)  {s << MOV << RSI << COMMA <<  rbp_top << '(' << RBP << ')'<<endl;break;}
              else {s << MOV << XMM1 << COMMA <<  rbp_top << '(' << RBP << ')'<<endl;break;}}
      case 3: {if(paras->nth(i)->getType()==Int)  {s << MOV << RDX << COMMA <<  rbp_top << '(' << RBP << ')'<<endl;break;}
              else {s << MOV << XMM2 << COMMA <<  rbp_top << '(' << RBP << ')'<<endl;break;}}
      case 4: {if(paras->nth(i)->getType()==Int)  {s << MOV << RCX << COMMA <<  rbp_top << '(' << RBP << ')'<<endl;break;}
              else {s << MOV << XMM3 << COMMA <<  rbp_top << '(' << RBP << ')'<<endl;break;}}
      case 5: {if(paras->nth(i)->getType()==Int)  {s << MOV << R8 << COMMA <<  rbp_top << '(' << RBP << ')'<<endl;break;}
              else {s << MOV << XMM4 << COMMA <<  rbp_top << '(' << RBP << ')'<<endl;break;}}
      case 6: {if(paras->nth(i)->getType()==Int)  {s << MOV << R9 << COMMA <<  rbp_top << '(' << RBP << ')'<<endl;break;}
              else {s << MOV << XMM5 << COMMA <<  rbp_top << '(' << RBP << ')'<<endl;break;}}
      default:  break;      
      }
    }

    int* shift=new int(rbp_top);
    var_shift->addid(paras->nth(i)->getName()->get_string(),shift);
    
  }
  for(int i=getBody()->getVariableDecls()->first();getBody()->getVariableDecls()->more(i); i=getBody()->getVariableDecls()->next(i))  
  {
      getBody()->getVariableDecls()->nth(i)->code(s);
  }

  for(int i=getBody()->getStmts()->first();getBody()->getStmts()->more(i); i=getBody()->getStmts()->next(i))
  {
    getBody()->getStmts()->nth(i)->code(s);
  }

  s<<SIZE<<name<<COMMA<<".-"<<name<<endl;
  var_shift->exitscope();

}

void StmtBlock_class::code(ostream &s){
  for(int i=getVariableDecls()->first();getVariableDecls()->more(i); i=getVariableDecls()->next(i))
  {
    getVariableDecls()->nth(i)->code(s);
  }

  for(int i=getStmts()->first();getStmts()->more(i); i=getStmts()->next(i))
  {
    getStmts()->nth(i)->code(s);
  }
}

void VariableDecl_class::code(ostream &s) {
  emit_sub("$8",RSP,s);
  rbp_top -= 8;
  int* shift=new int(rbp_top);

  var_shift->addid(variable->getName()->get_string(),shift);
}

void IfStmt_class::code(ostream &s) {
  int if_position = position_num;
  int if_position_current = position_num_current;
  position_num+=2;
  position_num_current+=2;
  condition->code(s);

  s << MOV <<  rbp_top << '(' << RBP << ')'<< COMMA << RAX <<endl;
  s << TEST << RAX << COMMA << RAX <<endl;
  s << JZ << ' ' << POSITION << if_position <<endl;
  if_position++;

  // then_expr
  thenexpr->code(s);
  s << JMP << ' ' << POSITION << if_position <<endl;
  if_position++;

  //else_expr
  s << POSITION << if_position_current << ':' <<endl;
  if_position_current++;
  elseexpr->code(s);

  //after if statement
  s << POSITION << if_position_current << ':' <<endl;
  if_position_current++;

}

void WhileStmt_class::code(ostream &s) {
  int start_position = position_num;
  s << POSITION << start_position << ':'<<endl;
  position_num_current++; position_num++;
  int while_position = position_num;
  position_num++;
  position_num_current++;
  
  condition->code(s);

  s << MOV <<  rbp_top << '(' << RBP << ')'<< COMMA << RAX <<endl;
  s << TEST << RAX << COMMA << RAX <<endl;
  s << JZ << ' ' << POSITION << while_position <<endl;
  body->code(s);
  s << JMP << ' ' << POSITION << start_position <<endl;

  s << POSITION << while_position << ':' <<endl;
}

void ForStmt_class::code(ostream &s) {
  initexpr->code(s);

  // for circle start
  int start_position = position_num;
  s << POSITION << position_num << ':' << endl;
  position_num++; position_num_current++;
  int for_position = position_num;
  int after_for_position = position_num+1;

  // condition expr
  position_num+=2;  position_num_current+=2;
  condition->code(s);
 
  // compare
  s << MOV <<  rbp_top << '(' << RBP << ')'<< COMMA << RAX <<endl;
  s << TEST << RAX << COMMA << RAX <<endl;
  s << JZ << ' ' << POSITION << after_for_position <<endl;

  // for body
  body->code(s);

  // loopact expr
  s << POSITION << for_position << ':' <<endl;
  loopact->code(s);
  s << JMP << ' ' << POSITION << start_position <<endl;

  // after for
  s << POSITION << after_for_position << ':' <<endl;


}

void ReturnStmt_class::code(ostream &s) {
  if(!value->is_empty_Expr())
  {
    if(value->get_is_global())
    {
      value->code(s);
      s << MOV<< globalVar->get_string() << '(' << RIP << ')'<< COMMA << RAX <<endl;
    }
    else
    {
      value->code(s);
      if(value->getType()==Int) s << MOV <<  value->get_result_shift() << '(' << RBP << ')'<< COMMA << RAX <<endl;
      else s << MOVAPS <<  value->get_result_shift() << '(' << RBP << ')'<< COMMA << XMM0 <<endl;      
    }
    // value->code(s);
    // if(value->getType()==Int) s << MOV <<  value->get_result_shift() << '(' << RBP << ')'<< COMMA << RAX <<endl;
    // else s << MOVAPS <<  value->get_result_shift() << '(' << RBP << ')'<< COMMA << XMM0 <<endl;      

  }
  emit_pop(R15,s);
  emit_pop(R14,s);
  emit_pop(R13,s);
  emit_pop(R12,s);
  emit_pop(R11,s);
  emit_pop(R10,s);
  emit_pop(RBX,s);
  emit_leave(s);
  emit_ret(s);
}

void ContinueStmt_class::code(ostream &s) {
 
}

void BreakStmt_class::code(ostream &s) {
}

void Call_class::code(ostream &s) {
  int paras_num=0; //参数序号

  if (name == print)
  {
    int float_num=0; //计数printf里的浮点数个数

    rbp_top -=8;
    emit_sub("$8", RSP, s);

    if(getActuals()->more(getActuals()->first()))
    {
      for(int i=getActuals()->first();getActuals()->more(i); i=getActuals()->next(i)) getActuals()->nth(i)->code(s);
      for(int i=getActuals()->first();getActuals()->more(i); i=getActuals()->next(i))
      {
        paras_num++;
        switch (paras_num)
        {
        case 2: {s << MOV << getActuals()->nth(getActuals()->first())->get_result_shift() << '(' << RBP << ')' << COMMA << RDI <<endl;
                 if(getActuals()->nth(i)->getType()==Int) {s << MOV << getActuals()->nth(i)->get_result_shift() << '(' << RBP << ')' << COMMA << RSI <<endl;break;}
                 else {if(getActuals()->nth(i)->getType()==Float) float_num++; s << MOVSD << getActuals()->nth(i)->get_result_shift() << '(' << RBP << ')' << COMMA << XMM0 <<endl;break;}}
        case 3: {if(getActuals()->nth(i)->getType()==Int) {s << MOV << getActuals()->nth(i)->get_result_shift() << '(' << RBP << ')' << COMMA << RDX <<endl;break;}
                 else {if(getActuals()->nth(i)->getType()==Float) float_num++; s << MOVSD << getActuals()->nth(i)->get_result_shift() << '(' << RBP << ')' << COMMA << XMM1 <<endl;break;}}
        case 4: {if(getActuals()->nth(i)->getType()==Int) {s << MOV << getActuals()->nth(i)->get_result_shift() << '(' << RBP << ')' << COMMA << RCX <<endl;break;}
                 else {if(getActuals()->nth(i)->getType()==Float) float_num++; s << MOVSD << getActuals()->nth(i)->get_result_shift() << '(' << RBP << ')' << COMMA << XMM2 <<endl;break;}}
        case 5: {if(getActuals()->nth(i)->getType()==Int) {s << MOV << getActuals()->nth(i)->get_result_shift() << '(' << RBP << ')' << COMMA << R8 <<endl;break;}
                 else {if(getActuals()->nth(i)->getType()==Float) float_num++; s << MOVSD << getActuals()->nth(i)->get_result_shift() << '(' << RBP << ')' << COMMA << XMM3 <<endl;break;}}
        case 6: {if(getActuals()->nth(i)->getType()==Int) {s << MOV << getActuals()->nth(i)->get_result_shift() << '(' << RBP << ')' << COMMA << R9 <<endl;break;}
                 else {if(getActuals()->nth(i)->getType()==Float) float_num++; s << MOVSD << getActuals()->nth(i)->get_result_shift() << '(' << RBP << ')' << COMMA << XMM4 <<endl;break;}}
        default:  break;
        } 
      }
      if(paras_num<2) s << MOV << getActuals()->nth(getActuals()->first())->get_result_shift() << '(' << RBP << ')' << COMMA << RDI <<endl;
      emit_sub("$8",RSP,s);
      rbp_top-=8;
      s << MOVL << "$" << float_num << COMMA << EAX<<endl;
      float_num=0;
    }
    else
    {
      emit_sub("$8",RSP,s);
      emit_irmovl("0", EAX, s);
    }
    emit_call("printf", s);


    return;
  }


  for(int i=getActuals()->first();getActuals()->more(i); i=getActuals()->next(i))
  {
    getActuals()->nth(i)->code(s);
    paras_num++;
    switch (paras_num)
    {
    case 1: {if(getActuals()->nth(i)->getType()==Int) {s << MOV << getActuals()->nth(i)->get_result_shift() << '(' << RBP << ')' << COMMA << RDI <<endl;break;}
             else {s << MOVSD << getActuals()->nth(i)->get_result_shift() << '(' << RBP << ')' << COMMA << XMM0 <<endl;break;}}
    case 2: {if(getActuals()->nth(i)->getType()==Int) {s << MOV << getActuals()->nth(i)->get_result_shift() << '(' << RBP << ')' << COMMA << RSI <<endl;break;}
             else {s << MOVSD << getActuals()->nth(i)->get_result_shift() << '(' << RBP << ')' << COMMA << XMM1 <<endl;break;}}
    case 3: {if(getActuals()->nth(i)->getType()==Int) {s << MOV << getActuals()->nth(i)->get_result_shift() << '(' << RBP << ')' << COMMA << RDX <<endl;break;}
             else {s << MOVSD << getActuals()->nth(i)->get_result_shift() << '(' << RBP << ')' << COMMA << XMM2 <<endl;break;}}
    case 4: {if(getActuals()->nth(i)->getType()==Int) {s << MOV << getActuals()->nth(i)->get_result_shift() << '(' << RBP << ')' << COMMA << RCX <<endl;break;}
             else {s << MOVSD << getActuals()->nth(i)->get_result_shift() << '(' << RBP << ')' << COMMA << XMM3 <<endl;break;}}
    case 5: {if(getActuals()->nth(i)->getType()==Int) {s << MOV << getActuals()->nth(i)->get_result_shift() << '(' << RBP << ')' << COMMA << R8 <<endl;break;}
             else {s << MOVSD << getActuals()->nth(i)->get_result_shift() << '(' << RBP << ')' << COMMA << XMM4 <<endl;break;}}
    case 6: {if(getActuals()->nth(i)->getType()==Int) {s << MOV << getActuals()->nth(i)->get_result_shift() << '(' << RBP << ')' << COMMA << R9 <<endl;break;}
             else {s << MOVSD << getActuals()->nth(i)->get_result_shift() << '(' << RBP << ')' << COMMA << XMM4 <<endl;break;}}
    default:  break;
    }  


  }
  emit_call(name->get_string(),s);
  rbp_top -= 8;
  emit_sub("$8",RSP,s);
  if(getType()==Int)  s << MOV << RAX << COMMA << rbp_top << '(' << RBP << ')'<< endl;
  else s << MOVSD << XMM0 << COMMA << rbp_top << '(' << RBP << ')'<< endl;
  result_shift=rbp_top;

}

void Actual_class::code(ostream &s) {
  // get the const string
  expr->code(s);
  result_shift=expr->get_result_shift();
}

void Assign_class::code(ostream &s) {
  value->code(s);
  if(value->get_is_global())
  {
    s << MOV << globalVar->get_string() << '(' << RIP << ')'<< COMMA << RAX <<endl;
  }
  else
  {
    s << MOV <<  value->get_result_shift() << '(' << RBP << ')'<< COMMA << RAX <<endl;
  }
  
  // value->code(s);
  // s << MOV <<  value->get_result_shift() << '(' << RBP << ')'<< COMMA << RAX <<endl;
  int lvalue_shift=0;
  if(var_shift->lookup(lvalue->get_string()))
  {
    lvalue_shift=*(var_shift->lookup(lvalue->get_string()));
    s << MOV << RAX << COMMA << lvalue_shift << '(' << RBP << ')'<< endl;
  }
  else
  {
    s << MOV << RAX << COMMA << lvalue->get_string() << '(' << RIP << ')'<<endl;
  }
}

void Add_class::code(ostream &s) {
  
  e1->code(s);
  e2->code(s);

  rbp_top -= 8;
  emit_sub("$8",RSP,s);

  if(e1->getType()==Int && e2->getType()==Int)
  {
    if(!e1->get_is_global())  s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RBX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RBX << endl;
    if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << R10 << endl;
    else  s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << R10 << endl;
    emit_add(RBX, R10, s);
    s << MOV << R10 << COMMA << rbp_top << '(' << RBP << ')' <<endl;
  }
  else if(e1->getType()==Float && e2->getType()==Float)
  {
    if(!e1->get_is_global()) s << MOVSD << e1->get_result_shift() << '(' << RBP << ')' << COMMA << XMM4 << endl;
    else  s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM4 << endl;
    if(!e2->get_is_global()) s << MOVSD << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM5 << endl;
    else  s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM5 << endl;
    emit_addsd(XMM4,XMM5,s);
    s << MOVSD << XMM5 << COMMA << rbp_top << '(' << RBP << ')' <<endl;
  }
  else if(e1->getType()==Int && e2->getType()==Float)
  {
    if(!e1->get_is_global())  s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RBX << endl;
    else  s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RBX << endl;
    s << CVTSI2SDQ << RBX << COMMA << XMM4 << endl; //cvtsi2sdq	%rbx, %xmm4
    if(!e2->get_is_global())  s << MOVSD << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM5 << endl;
    else  s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM5 << endl;
    emit_addsd(XMM4,XMM5,s);
    s << MOVSD << XMM5 << COMMA << rbp_top << '(' << RBP << ')' <<endl;

  }
  else  //(e1->getType()==Float && e2->getType()==Int)
  {
    if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << RBX << endl;
    else  s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RBX << endl;
    s << CVTSI2SDQ << RBX << COMMA << XMM5 << endl; //cvtsi2sdq	%rbx, %xmm4
    if(!e1->get_is_global())  s << MOVSD << e1->get_result_shift() << '(' << RBP << ')' << COMMA << XMM4 << endl;
    else  s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM4 << endl;

    emit_addsd(XMM4,XMM5,s);
    s << MOVSD << XMM5 << COMMA << rbp_top << '(' << RBP << ')' <<endl;

  }
  result_shift=rbp_top;
}

void Minus_class::code(ostream &s) {
  e1->code(s);
  e2->code(s);

  rbp_top -= 8;
  emit_sub("$8",RSP,s);
  
  if(e1->getType()==Int && e2->getType()==Int)
  {
    if(!e1->get_is_global())  s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RBX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RBX << endl;
    if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << R10 << endl;
    else  s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << R10 << endl;
    emit_sub(R10, RBX, s);
    s << MOV << RBX << COMMA << rbp_top << '(' << RBP << ')' <<endl;
  }
  else if(e1->getType()==Float && e2->getType()==Float)
  {
    if(!e1->get_is_global()) s << MOVSD << e1->get_result_shift() << '(' << RBP << ')' << COMMA << XMM4 << endl;
    else  s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM4 << endl;
    if(!e2->get_is_global()) s << MOVSD << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM5 << endl;
    else  s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM5 << endl;
    emit_subsd(XMM5,XMM4,s);
    s << MOVSD << XMM4 << COMMA << rbp_top << '(' << RBP << ')' <<endl;
  }
  else if(e1->getType()==Int && e2->getType()==Float)
  {
    if(!e1->get_is_global())  s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RBX << endl;
    else  s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RBX << endl;
    s << CVTSI2SDQ << RBX << COMMA << XMM4 << endl; //cvtsi2sdq	%rbx, %xmm4
    if(!e2->get_is_global())  s << MOVSD << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM5 << endl;
    else  s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM5 << endl;
    emit_subsd(XMM5,XMM4,s);
    s << MOVSD << XMM4 << COMMA << rbp_top << '(' << RBP << ')' <<endl;

  }
  else  //(e1->getType()==Float && e2->getType()==Int)
  {
    if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << RBX << endl;
    else  s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RBX << endl;
    s << CVTSI2SDQ << RBX << COMMA << XMM5 << endl; //cvtsi2sdq	%rbx, %xmm4
    if(!e1->get_is_global())  s << MOVSD << e1->get_result_shift() << '(' << RBP << ')' << COMMA << XMM4 << endl;
    else  s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM4 << endl;

    emit_subsd(XMM5,XMM4,s);
    s << MOVSD << XMM4 << COMMA << rbp_top << '(' << RBP << ')' <<endl;

  }
  result_shift=rbp_top;
}

void Multi_class::code(ostream &s) {
  e1->code(s);
  e2->code(s);

  rbp_top -= 8;
  emit_sub("$8",RSP,s);
  
  if(e1->getType()==Int && e2->getType()==Int)
  {
    if(!e1->get_is_global())  s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RBX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RBX << endl;
    if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << R10 << endl;
    else  s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << R10 << endl;
    emit_mul(R10, RBX, s);
    s << MOV << RBX << COMMA << rbp_top << '(' << RBP << ')' <<endl;
  }
  else if(e1->getType()==Float && e2->getType()==Float)
  {
    if(!e1->get_is_global()) s << MOVSD << e1->get_result_shift() << '(' << RBP << ')' << COMMA << XMM4 << endl;
    else  s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM4 << endl;
    if(!e2->get_is_global()) s << MOVSD << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM5 << endl;
    else  s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM5 << endl;
    emit_mulsd(XMM5,XMM4,s);
    s << MOVSD << XMM4 << COMMA << rbp_top << '(' << RBP << ')' <<endl;
  }
  else if(e1->getType()==Int && e2->getType()==Float)
  {
    if(!e1->get_is_global())  s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RBX << endl;
    else  s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RBX << endl;
    s << CVTSI2SDQ << RBX << COMMA << XMM4 << endl; //cvtsi2sdq	%rbx, %xmm4
    if(!e2->get_is_global())  s << MOVSD << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM5 << endl;
    else  s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM5 << endl;
    emit_mulsd(XMM5,XMM4,s);
    s << MOVSD << XMM4 << COMMA << rbp_top << '(' << RBP << ')' <<endl;

  }
  else  //(e1->getType()==Float && e2->getType()==Int)
  {
    if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << RBX << endl;
    else  s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RBX << endl;
    s << CVTSI2SDQ << RBX << COMMA << XMM5 << endl; //cvtsi2sdq	%rbx, %xmm4
    if(!e1->get_is_global())  s << MOVSD << e1->get_result_shift() << '(' << RBP << ')' << COMMA << XMM4 << endl;
    else  s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM4 << endl;

    emit_mulsd(XMM5,XMM4,s);
    s << MOVSD << XMM4 << COMMA << rbp_top << '(' << RBP << ')' <<endl;

  }
  result_shift=rbp_top; 
}

void Divide_class::code(ostream &s) {
  e1->code(s);
  e2->code(s);

  rbp_top -= 8;
  emit_sub("$8",RSP,s);
  
  if(e1->getType()==Int && e2->getType()==Int)
  {
    if(!e1->get_is_global())  s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
    emit_cqto(s);
    
    if(!e1->get_is_global())  s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << RBX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
    emit_div(RBX,s);
    s << MOV << RAX << COMMA << rbp_top << '(' << RBP << ')' <<endl;
  }
  else if(e1->getType()==Float && e2->getType()==Float)
  {
    if(!e1->get_is_global())  s << MOVSD << e1->get_result_shift() << '(' << RBP << ')' << COMMA << XMM4 << endl;
    else s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM4 << endl;
    if(!e2->get_is_global()) s << MOVSD << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM5 << endl;
    else s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM5 << endl;
    emit_divsd(XMM5,XMM4,s);
    s << MOVSD << XMM4 << COMMA << rbp_top << '(' << RBP << ')' <<endl;
  }
  else if(e1->getType()==Int && e2->getType()==Float)
  {
    if(!e1->get_is_global()) s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RBX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RBX << endl;
    s << CVTSI2SDQ << RBX << COMMA << XMM4 << endl; //cvtsi2sdq	%rbx, %xmm4
    if(!e2->get_is_global()) s << MOVSD << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM5 << endl;
    else s << MOVSD << e2->get_result_shift() << '(' << RIP << ')' << COMMA << XMM5 << endl;
    emit_divsd(XMM5,XMM4,s);
    s << MOVSD << XMM4 << COMMA << rbp_top << '(' << RBP << ')' <<endl;

  }
  else  //(e1->getType()==Float && e2->getType()==Int)
  {
    if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << RBX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RBX << endl;
    s << CVTSI2SDQ << RBX << COMMA << XMM5 << endl; //cvtsi2sdq	%rbx, %xmm4
    if(!e1->get_is_global()) s << MOVSD << e1->get_result_shift() << '(' << RBP << ')' << COMMA << XMM4 << endl;
    else s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM4 << endl;

    emit_divsd(XMM5,XMM4,s);
    s << MOVSD << XMM4 << COMMA << rbp_top << '(' << RBP << ')' <<endl;

  }
  result_shift=rbp_top; 
}

void Mod_class::code(ostream &s) {
  e1->code(s);
  e2->code(s);

  rbp_top -= 8;
  emit_sub("$8",RSP,s);
  if(!e1->get_is_global())  s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
  else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
  emit_cqto(s);
  if(!e2->get_is_global())  s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << RBX << endl;
  else  s << MOV << globalVar << '(' << RIP << ')' << COMMA << RBX << endl;
  emit_div(RBX,s);
  s << MOV << RDX << COMMA << rbp_top << '(' << RBP << ')' <<endl;
  result_shift=rbp_top; 

}

void Neg_class::code(ostream &s) {
 e1->code(s);
 rbp_top -= 8;
 result_shift=rbp_top; 
 emit_sub("$8",RSP,s);
 if(e1->getType()==Int)
 {
  if(!e1->get_is_global())  s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
  else s << MOV << globalVar->get_string() << '(' << RBP << ')' << COMMA << RAX << endl;
  emit_neg(RAX,s);
  s << MOV << RAX << COMMA << rbp_top << '(' << RBP << ')' <<endl;
 }
 else
 {
  emit_sub("$8",RSP,s);
  emit_mov("$0x8000000000000000",RAX,s);
  if(!e1->get_is_global())  s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RDX << endl;
  else s << MOV << globalVar->get_string() << '(' << RBP << ')' << COMMA << RDX << endl;
  emit_xor(RAX,RDX,s);
  s << MOV << RDX << COMMA << rbp_top << '(' << RBP << ')' <<endl;
  rbp_top -= 8;

 }
 
}

void Lt_class::code(ostream &s) {
  e1->code(s);
  e2->code(s);
  emit_sub("$8",RSP,s);
  rbp_top -= 8;
  if(e1->getType()==Int && e2->getType()==Int)
  {
    if(!e1->get_is_global()) s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
    if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << RDX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RDX << endl;
    emit_cmp(RDX, RAX, s);
  }
  else if(e1->getType()==Float && e2->getType()==Int)
  {
    if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
    s << CVTSI2SDQ <<RAX <<COMMA << XMM0 <<endl;
    if(!e1->get_is_global()) s << MOVSD << e1->get_result_shift() << '(' << RBP << ')' << COMMA << XMM1 << endl;
    else s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM1 << endl;
    emit_ucompisd(XMM0,XMM1,s);
  }
  else if(e1->getType()==Int && e2->getType()==Float)
  {
    if(!e1->get_is_global()) s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
    s << CVTSI2SDQ <<RAX << COMMA << XMM0 << endl;
    if(!e2->get_is_global()) s << MOVSD << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM1 << endl;
    else s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM1 << endl;
    emit_ucompisd(XMM1,XMM0,s);
  }
  else
  {
    if(!e1->get_is_global()) s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << XMM1 << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM1 << endl;
    if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM0 << endl;
    else s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM0 << endl;
    emit_ucompisd(XMM0,XMM1,s);
  }
  if(e1->getType()==Int && e2->getType()==Int)  s << JL <<' '<< POSITION << position_num <<endl;
  else  s << JB <<' '<< POSITION << position_num <<endl;
  position_num++;
  emit_mov("$0",RAX,s);
  s << JMP <<' '<< POSITION << position_num << endl;
  position_num++;
  s << POSITION << position_num_current<<':' << endl;
  position_num_current++;
  emit_mov("$1",RAX,s);
  s << POSITION << position_num_current<<':' << endl;
  position_num_current++;
  s << MOV << RAX << COMMA << rbp_top << '(' << RBP << ')' <<endl;
  result_shift=rbp_top;
}

void Le_class::code(ostream &s) {
  e1->code(s);
  e2->code(s);
  emit_sub("$8",RSP,s);
  rbp_top -= 8;
  if(e1->getType()==Int && e2->getType()==Int)
  {
    if(!e1->get_is_global()) s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
    if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << RDX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RDX << endl;
    emit_cmp(RDX, RAX, s);
  }
  else if(e1->getType()==Float && e2->getType()==Int)
  {
   if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
   else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
   s << CVTSI2SDQ <<RAX <<COMMA << XMM0 <<endl;
   if(!e1->get_is_global()) s << MOVSD << e1->get_result_shift() << '(' << RBP << ')' << COMMA << XMM1 << endl;
   else s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM1 << endl;
   emit_ucompisd(XMM0,XMM1,s);
  }
  else if(e1->getType()==Int && e2->getType()==Float)
  {
    if(!e1->get_is_global()) s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
    s << CVTSI2SDQ <<RAX << COMMA << XMM0 << endl;
    if(!e2->get_is_global()) s << MOVSD << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM1 << endl;
    else s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM1 << endl;
    emit_ucompisd(XMM1,XMM0,s);
  }
  else
  {
    if(!e1->get_is_global()) s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << XMM1 << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM1 << endl;
    if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM0 << endl;
    else s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM0 << endl;
    emit_ucompisd(XMM0,XMM1,s);
  }
  if(e1->getType()==Int && e2->getType()==Int)  s << JLE <<' '<< POSITION << position_num <<endl;
  else  s << JBE <<' '<< POSITION << position_num <<endl;
  position_num++;
  emit_mov("$0",RAX,s);
  s << JMP <<' '<< POSITION << position_num << endl;
  position_num++;
  s << POSITION << position_num_current<<':' << endl;
  position_num_current++;
  emit_mov("$1",RAX,s);
  s << POSITION << position_num_current<<':' << endl;
  position_num_current++;
  s << MOV << RAX << COMMA << rbp_top << '(' << RBP << ')' <<endl;
  result_shift=rbp_top; 
}

void Equ_class::code(ostream &s) {
  e1->code(s);
  e2->code(s);
  emit_sub("$8",RSP,s);
  rbp_top -= 8;
  if(e1->getType()==Int && e2->getType()==Int)
  {
    if(!e1->get_is_global()) s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
    if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << RDX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RDX << endl;
    emit_cmp(RDX, RAX, s);
  }
  else if(e1->getType()==Float && e2->getType()==Int)
  {
   if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
   else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
   s << CVTSI2SDQ <<RAX <<COMMA << XMM0 <<endl;
   if(!e1->get_is_global()) s << MOVSD << e1->get_result_shift() << '(' << RBP << ')' << COMMA << XMM1 << endl;
   else s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM1 << endl;
   emit_ucompisd(XMM0,XMM1,s);
  }
  else if(e1->getType()==Int && e2->getType()==Float)
  {
    if(!e1->get_is_global()) s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
    s << CVTSI2SDQ <<RAX << COMMA << XMM0 << endl;
    if(!e2->get_is_global()) s << MOVSD << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM1 << endl;
    else s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM1 << endl;
    emit_ucompisd(XMM1,XMM0,s);
  }
  else
  {
    if(!e1->get_is_global()) s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << XMM1 << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM1 << endl;
    if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM0 << endl;
    else s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM0 << endl;
    emit_ucompisd(XMM0,XMM1,s);
  }
  s << JE <<' '<< POSITION << position_num <<endl;
  position_num++;
  emit_mov("$0",RAX,s);
  s << JMP <<' '<< POSITION << position_num << endl;
  position_num++;
  s << POSITION << position_num_current<<':' << endl;
  position_num_current++;
  emit_mov("$1",RAX,s);
  s << POSITION << position_num_current<<':' << endl;
  position_num_current++;
  s << MOV << RAX << COMMA << rbp_top << '(' << RBP << ')' <<endl;
  result_shift=rbp_top;  
}

void Neq_class::code(ostream &s) {
  e1->code(s);
  e2->code(s);
  emit_sub("$8",RSP,s);
  rbp_top -= 8;

  if(e1->getType()==Int && e2->getType()==Int)
  {
  if(!e1->get_is_global()) s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
  else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
  if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << RDX << endl;
  else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RDX << endl;
  emit_cmp(RDX, RAX, s);
  }
  else if(e1->getType()==Float && e2->getType()==Int)
  {
    if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
    s << CVTSI2SDQ <<RAX <<COMMA << XMM0 <<endl;
    if(!e1->get_is_global()) s << MOVSD << e1->get_result_shift() << '(' << RBP << ')' << COMMA << XMM1 << endl;
    else s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM1 << endl;
    emit_ucompisd(XMM0,XMM1,s);
  }
  else if(e1->getType()==Int && e2->getType()==Float)
  {
    if(!e1->get_is_global()) s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
    s << CVTSI2SDQ <<RAX << COMMA << XMM0 << endl;
    if(!e2->get_is_global()) s << MOVSD << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM1 << endl;
    else s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM1 << endl;
    emit_ucompisd(XMM1,XMM0,s);
  }
  else
  {
    if(!e1->get_is_global()) s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << XMM1 << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM1 << endl;
    if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM0 << endl;
    else s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM0 << endl;
    emit_ucompisd(XMM0,XMM1,s);
  }
  

  s << JNE <<' '<< POSITION << position_num <<endl;
  position_num++;
  emit_mov("$0",RAX,s);
  s << JMP <<' '<< POSITION << position_num << endl;
  position_num++;
  s << POSITION << position_num_current<<':' << endl;
  position_num_current++;
  emit_mov("$1",RAX,s);
  s << POSITION << position_num_current<<':' << endl;
  position_num_current++;
  s << MOV << RAX << COMMA << rbp_top << '(' << RBP << ')' <<endl;
  result_shift=rbp_top;   
}

void Ge_class::code(ostream &s) {
  e1->code(s);
  e2->code(s);
  emit_sub("$8",RSP,s);
  rbp_top -= 8;
  if(e1->getType()==Int && e2->getType()==Int)
  {
    if(!e1->get_is_global()) s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
    if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << RDX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RDX << endl;
    emit_cmp(RDX, RAX, s);
  }
  else if(e1->getType()==Float && e2->getType()==Int)
  {
   if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
   else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
   s << CVTSI2SDQ <<RAX <<COMMA << XMM0 <<endl;
   if(!e1->get_is_global()) s << MOVSD << e1->get_result_shift() << '(' << RBP << ')' << COMMA << XMM1 << endl;
   else s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM1 << endl;
   emit_ucompisd(XMM0,XMM1,s);
  }
  else if(e1->getType()==Int && e2->getType()==Float)
  {
    if(!e1->get_is_global()) s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
    s << CVTSI2SDQ <<RAX << COMMA << XMM0 << endl;
    if(!e2->get_is_global()) s << MOVSD << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM1 << endl;
    else s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM1 << endl;
    emit_ucompisd(XMM1,XMM0,s);
  }
  else
  {
    if(!e1->get_is_global()) s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << XMM1 << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM1 << endl;
    if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM0 << endl;
    else s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM0 << endl;
    emit_ucompisd(XMM0,XMM1,s);
  }
  if(e1->getType()==Int && e2->getType()==Int)  s << JGE <<' '<< POSITION << position_num <<endl;
  else  s << JAE <<' '<< POSITION << position_num <<endl;
  position_num++;
  emit_mov("$0",RAX,s);
  s << JMP <<' '<< POSITION << position_num << endl;
  position_num++;
  s << POSITION << position_num_current<<':' << endl;
  position_num_current++;
  emit_mov("$1",RAX,s);
  s << POSITION << position_num_current<<':' << endl;
  position_num_current++;
  s << MOV << RAX << COMMA << rbp_top << '(' << RBP << ')' <<endl;
  result_shift=rbp_top; 
}

void Gt_class::code(ostream &s) {
  e1->code(s);
  e2->code(s);
  emit_sub("$8",RSP,s);
  rbp_top -= 8;
  if(e1->getType()==Int && e2->getType()==Int)
  {
    if(!e1->get_is_global()) s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
    if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << RDX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RDX << endl;
    emit_cmp(RDX, RAX, s);
  }
  else if(e1->getType()==Float && e2->getType()==Int)
  {
   if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
   else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
   s << CVTSI2SDQ <<RAX <<COMMA << XMM0 <<endl;
   if(!e1->get_is_global()) s << MOVSD << e1->get_result_shift() << '(' << RBP << ')' << COMMA << XMM1 << endl;
   else s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM1 << endl;
   emit_ucompisd(XMM0,XMM1,s);
  }
  else if(e1->getType()==Int && e2->getType()==Float)
  {
    if(!e1->get_is_global()) s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
    s << CVTSI2SDQ <<RAX << COMMA << XMM0 << endl;
    if(!e2->get_is_global()) s << MOVSD << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM1 << endl;
    else s << MOVSD << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM1 << endl;
    emit_ucompisd(XMM1,XMM0,s);
  }
  else
  {
    if(!e1->get_is_global()) s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << XMM1 << endl;
    else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << XMM1 << endl;
    if(!e2->get_is_global()) s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM0 << endl;
    else s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << XMM0 << endl;
    emit_ucompisd(XMM0,XMM1,s);
  }
  if(e1->getType()==Int && e2->getType()==Int)  s << JG <<' '<< POSITION << position_num <<endl;
  else  s << JA <<' '<< POSITION << position_num <<endl;
  position_num++;
  emit_mov("$0",RAX,s);
  s << JMP <<' '<< POSITION << position_num << endl;
  position_num++;
  s << POSITION << position_num_current<<':' << endl;
  position_num_current++;
  emit_mov("$1",RAX,s);
  s << POSITION << position_num_current<<':' << endl;
  position_num_current++;
  s << MOV << RAX << COMMA << rbp_top << '(' << RBP << ')' <<endl;
  result_shift=rbp_top; 
}

void And_class::code(ostream &s) {
  e1->code(s);
  e2->code(s);
  emit_sub("$8",RSP,s);
  rbp_top -= 8;
  if(!e1->get_is_global())  s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
  else  s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
  if(!e2->get_is_global())  s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << RDX << endl; 
  else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RDX << endl; 
  emit_and(RAX,RDX,s);
  s << MOV << RDX << COMMA << rbp_top << '(' << RBP << ')' <<endl;
  result_shift=rbp_top;
}

void Or_class::code(ostream &s) {
  e1->code(s);
  e2->code(s);
  emit_sub("$8",RSP,s);
  rbp_top -= 8;
  if(!e1->get_is_global())  s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
  else  s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
  if(!e2->get_is_global())  s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << RDX << endl; 
  else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RDX << endl; 
  emit_or(RAX,RDX,s);
  s << MOV << RDX << COMMA << rbp_top << '(' << RBP << ')' <<endl;
  result_shift=rbp_top; 
}

void Xor_class::code(ostream &s) {
  e1->code(s);
  e2->code(s);
  emit_sub("$8",RSP,s);
  rbp_top -= 8;
  if(!e1->get_is_global())  s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
  else  s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
  if(!e2->get_is_global())  s << MOV << e2->get_result_shift() << '(' << RBP << ')' << COMMA << RDX << endl; 
  else s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RDX << endl; 
  emit_xor(RAX,RDX,s);
  s << MOV << RDX << COMMA << rbp_top << '(' << RBP << ')' <<endl;
  result_shift=rbp_top;  
}

void Not_class::code(ostream &s) {
  e1->code(s);
  emit_sub("$8",RSP,s);
  rbp_top -= 8;
  if(!e1->get_is_global())  s << MOV << e1->get_result_shift() << '(' << RBP << ')' << COMMA << RAX << endl;
  else  s << MOV << globalVar->get_string() << '(' << RIP << ')' << COMMA << RAX << endl;
  emit_not(RAX,s);
  s << MOV << RDX << COMMA << rbp_top << '(' << RBP << ')' <<endl;
  result_shift=rbp_top; 
}

void Bitnot_class::code(ostream &s) {

}

void Bitand_class::code(ostream &s) {

}

void Bitor_class::code(ostream &s) {
 
}

void Const_int_class::code(ostream &s) {
  rbp_top-=8;
  stringstream ss;
  ss<<value;
  int num;
  ss>>num;
  emit_sub("$8", RSP,s);
  s << MOV << '$' << num <<COMMA << RAX << endl;
  s << MOV << RAX << COMMA << rbp_top << '(' << RBP << ')'<< endl;
  set_result_shift(rbp_top);
}

void Const_string_class::code(ostream &s) {
  //返回
  s << MOV;
  stringtable.lookup_string(value->get_string())->code_ref(s);
  s << COMMA << RAX << endl;
  s << MOV << RAX << COMMA << rbp_top << '(' << RBP << ')'<< endl;
  result_shift = rbp_top;

}

void Const_float_class::code(ostream &s) {
 stringstream ss;
 ss<<value;
 double res;
 ss>>res;
 double d=*( unsigned long int*)&res;
 emit_sub("$8", RSP,s);
 long int d0=d;
 s << MOV <<'$' <<d0 <<COMMA <<RAX<<endl;
 rbp_top-=8;
 s << MOV << RAX << COMMA << rbp_top << '(' << RBP << ')'<< endl;
 set_result_shift(rbp_top);
}

void Const_bool_class::code(ostream &s) {
  rbp_top-=8;
  emit_sub("$8", RSP,s);
  s << MOV <<'$' << value <<COMMA <<RAX<<endl;
  s << MOV << RAX << COMMA << rbp_top << '(' << RBP << ')'<< endl;

  result_shift = rbp_top;
  
}

void Object_class::code(ostream &s) {
 // 输出变量对应的偏移量，如-96(%rbp)
 if(!var_shift->lookup(var->get_string()))
 {
   is_global_variable=true;
   globalVar=var;
 }
 else result_shift=*(var_shift->lookup(var->get_string())); 
}

void No_expr_class::code(ostream &s) {

}