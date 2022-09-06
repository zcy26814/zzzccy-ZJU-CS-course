#ifndef _AST_H_
#define _AST_H_

#include <json/json.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <vector>

#include "type.h"

using namespace std; 

class Node {
public:
  // Value or name of node, if type of node is int, the value of nodeName is the
  // value of the integer, float, bool, char are similar if type is var, the
  // value is the name of this variable
  string *node_name;
  // The type of the node
  string *node_type;
  // The type of exp, var or const
  int value_type;
  // The number of child of the node
  int child_num;
  // Child nodes of this node
  Node **children;
  // The number of rows of the node in the file
  int line_num;

  // ir-build functions for all non-terminals
  llvm::Value *ir_build();
  llvm::Value *ir_build_declaration();
  llvm::Value *ir_build_funct();
  llvm::Value *ir_build_statement();
  llvm::Value *ir_build_comp_statement();
  llvm::Value *ir_build_exp_statement();
  llvm::Value *ir_build_funct_call();
  llvm::Value *ir_build_println();
  llvm::Value *ir_build_printf();
  llvm::Value *ir_build_scan();
  llvm::Value *ir_build_addr();
  llvm::Value *ir_build_arithmetic_statement();
  llvm::Value *ir_build_elem();
  llvm::Value *ir_build_relop();
  llvm::Value *ir_build_declaration_statement();
  llvm::Value *ir_build_assignment();
  llvm::Value *ir_build_loop_statement();
  llvm::Value *ir_build_select_statement();
  llvm::Value *ir_build_ret_statement();

  // about type
  int get_value_type();
  int get_value_type(Node *node);
  void set_value_type(int type);

  llvm::Type *get_llvm_type(int type, int array_size);

  llvm::Value *type_cast(llvm::Value *src, llvm::Type *dst);
  llvm::Instruction::CastOps get_cast_instruction(llvm::Type *src,
                                                  llvm::Type *dst);

  // about list
  vector<llvm::Value *> *get_args();
  vector<llvm::Value *> *get_print_args();
  vector<llvm::Value *> *get_args_addr();

  vector<pair<string, llvm::Type *>> *get_para();

  vector<pair<string, int>> *get_name_list(int type);

  // constructor
  Node(char *node_name, string node_type, int line_num);
  Node(string node_name, string node_type, int child_num, ...);
  Json::Value jsonGen();

  void print_info();
  void deep_print_info(int n);

  // destructor
  ~Node();
};

llvm::AllocaInst *create_entry_block_allocation(llvm::Function *function,
                                                llvm::StringRef var_name,
                                                llvm::Type *type);

#endif