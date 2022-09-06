#ifndef _CODE_GEN_H_
#define _CODE_GEN_H_

#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/Interpreter.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/SectionMemoryManager.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/ValueSymbolTable.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/DynamicLibrary.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>

#include <iostream>
#include <map>
#include <stack>
#include <string>

#include "ast.h"
#include "type.h"

using namespace std;

static llvm::LLVMContext context;
static llvm::IRBuilder<> builder(context);

class code_gen {
 public:
  code_gen(/* args */);

  llvm::Module* module;
  llvm::Function *printf, *scanf;
  stack<llvm::Function*> function_stack;

  llvm::Function* get_current_function();
  void push_function(llvm::Function* func);
  void pop_function();
  llvm::Value* find_value(const std::string& name);
  llvm::Function* create_printf();
  llvm::Function* create_scanf();
  void generate(Node* root);
};

#endif
