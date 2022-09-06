#include "ast.h"

#include <cstdarg>

#include "code_gen.h"

Node *ROOT;
extern code_gen *generator;
stack<llvm::BasicBlock *> global_after_basic_block;

Node::Node(char *node_name, string node_type, int line_num) {
  this->node_name = new string(node_name);
  this->node_type = new string(node_type);
  this->line_num = line_num;
  this->child_num = 0;
}

Node::Node(string node_name, string node_type, int child_num, ...) {
  this->node_name = new string(node_name);
  this->node_type = new string(node_type);

  this->child_num = child_num;
  this->children = new Node *[child_num];

  va_list list;
  va_start(list, child_num);
  for (int i = 0; i < child_num; ++i) {
    Node *node = va_arg(list, Node *);
    this->children[i] = node;
  }
  this->line_num = this->children[0]->line_num;
  va_end(list);
}

void Node::print_info() {
  cout << "->basic node info:" << endl;
  cout << "  [node_name]: " << *this->node_name << endl;
  cout << "  [node_type]: " << *this->node_type << endl;
  cout << "  [child_num]: " << this->child_num << endl;
}

void Node::deep_print_info(int n) {
  string str = "";
  string line = "";
  for (int i = 0; i < 2 * n; i++) {
    str.append(" ");
    line.append("-");
  }
  cout << line << "->advanced node info:" << n << endl;
  cout << str << "  [node_name]:" << *this->node_name << endl;
  cout << str << "  [node_type]:" << *this->node_type << endl;
  cout << str << "  [child_num]:" << this->child_num << endl;
  for (int i = 0; i < this->child_num; ++i) {
    this->children[i]->deep_print_info(n + 1);
  }
}

void Node::set_value_type(int type) { this->value_type = type; }

int Node::get_value_type() { return get_value_type(this); }

int Node::get_value_type(Node *node) {
  if (node->node_type->compare("TYPE") == 0) {
    if (node->node_name->compare("int") == 0) {
      return TYPE_INTEGER;
    } else if (node->node_name->compare("float") == 0) {
      return TYPE_FLOAT;
    } else if (node->node_name->compare("char") == 0) {
      return TYPE_CHAR;
    } else if (node->node_name->compare("string") == 0) {
      return TYPE_STRING;
    } else if (node->node_name->compare("bollen") == 0) {
      return TYPE_BOOL;
    } else {
    }
  } else if (node->node_type->compare("expr_statement") == 0) {
    return node->value_type;
  }
  return -1;
}

llvm::Type *Node::get_llvm_type(int type, int array_size) {
  switch (type) {
    case TYPE_INTEGER:
      return llvm::Type::getInt32Ty(context);
    case TYPE_INTEGER_ARRAY:
      if (array_size > 0) {
        return llvm::ArrayType::get(llvm::Type::getInt32Ty(context),
                                    array_size);
      } else {
        return llvm::Type::getInt32PtrTy(context);
      }
    case TYPE_FLOAT:
      return llvm::Type::getFloatTy(context);
    case TYPE_FLOAT_ARRAY:
      if (array_size > 0) {
        return llvm::ArrayType::get(llvm::Type::getFloatTy(context),
                                    array_size);
      } else {
        return llvm::Type::getFloatPtrTy(context);
      }
    case TYPE_BOOL:
      return llvm::Type::getInt1Ty(context);
    case TYPE_BOOL_ARRAY:
      if (array_size > 0) {
        return llvm::ArrayType::get(llvm::Type::getInt1Ty(context), array_size);
      } else {
        return llvm::Type::getInt1PtrTy(context);
      }
    case TYPE_CHAR:
      return llvm::Type::getInt8Ty(context);
    case TYPE_CHAR_ARRAY:
      if (array_size > 0) {
        return llvm::ArrayType::get(llvm::Type::getInt8Ty(context), array_size);
      } else {
        return llvm::Type::getInt8PtrTy(context);
      }
    default:
      return llvm::Type::getVoidTy(context);
  }
}

// get all var_name of a node
// var_list: var COMMA var_list
//         | var
//           var: var LSB INTEGER RSB | ID
vector<pair<string, int>> *Node::get_name_list(int type) {
  if (this->node_type->compare("var_list") != 0) {
    throw logic_error("[ERROR]wrong function call : get_name_list.");
  }
  Node *temp = this;
  vector<pair<string, int>> *name_list = new vector<pair<string, int>>;
  while (true) {
    // var: var LSB INTEGER RSB
    if (temp->children[0]->child_num == 4) {
      int array_size = stoi(*temp->children[0]->children[2]->node_name);
      // to find the name of the var in the right expression
      Node *tmp = temp->children[0]->children[0];
      string name;
      while (true) {
        if (tmp->node_type->compare("var") == 0) {
          tmp = tmp->children[0];
        } else {
          name = *tmp->node_name;
          break;
        }
      }
      name_list->push_back(make_pair(name, IS_ARRAY + array_size));
      temp->children[0]->children[0]->set_value_type(type + IS_ARRAY);
    }
    // var: ID
    else if (temp->children[0]->child_num == 1) {
      name_list->push_back(
          make_pair(*temp->children[0]->children[0]->node_name, VAR));
      temp->children[0]->children[0]->set_value_type(type);
    }
    // else
    else {
      throw logic_error("[ERROR]wrong var declaration");
      return name_list;
    }
    // var_list: var COMMA var_list and make the 2nd val_list be cur_val_list
    if (temp->child_num == 3)
      temp = temp->children[2];
    else
      break;
  }
  return name_list;
}

// para_list: para COMMA para_list
// para: TYPE ID
vector<pair<string, llvm::Type *>> *Node::get_para() {
  if (this->node_type->compare("para_list") != 0) {
    throw logic_error("[ERROR]wrong function call -> get_para");
    return NULL;
  }
  Node *temp = this;
  // para_list: para
  //             ^
  Node *temp_1 = this->children[0];
  vector<pair<string, llvm::Type *>> *para_list =
      new vector<pair<string, llvm::Type *>>;
  while (true) {
    temp_1 = temp->children[0];
    // para_lsit: para COMMA para_list
    //              ^
    // para: TYPE ID
    //   ^
    // temp_1 is para now
    if (temp_1->child_num == 2) {
      para_list->push_back(make_pair(
          *temp_1->children[1]->node_name,
          get_llvm_type(VAR + get_value_type(temp_1->children[0]), 0)));
    }

    else {
      throw logic_error("[ERROR]wrong get_para.");
      return para_list;
    }
    // para_lsit: para COMMA para_list
    //                           ^
    if (temp->child_num == 3)
      temp = temp->children[2];
    else
      break;
  }
  return para_list;
}

// args: arithmetic_statement COMMA args
//     | arithmetic_statement
vector<llvm::Value *> *Node::get_args() {
  vector<llvm::Value *> *args = new vector<llvm::Value *>;
  Node *node = this;
  while (true) {
    llvm::Value *temp = node->children[0]->ir_build_arithmetic_statement();
    args->push_back(temp);
    if (node->child_num == 1)
      break;
    else {
      node = node->children[2];
    }
  }
  return args;
}

vector<llvm::Value *> *Node::get_print_args() {
#ifdef DEBUG
  cout << "[get_print_args]:" << endl;
  this->deep_print_info(0);
#endif
  vector<llvm::Value *> *args = new vector<llvm::Value *>;
  Node *node = this;
  while (true) {
    llvm::Value *temp = node->children[0]->ir_build_arithmetic_statement();
    if (temp->getType() == llvm::Type::getFloatTy(context))
      temp = builder.CreateFPExt(temp, llvm::Type::getDoubleTy(context),
                                 "temp_double");
    args->push_back(temp);
    if (node->child_num == 1) {
      break;
    } else {
      node = node->children[2];
    }
  }
  return args;
}

vector<llvm::Value *> *Node::get_args_addr() {
  vector<llvm::Value *> *args = new vector<llvm::Value *>;
  Node *node = this;
  while (true) {
    // the first child is always arithmetic_statement, and cur node is args, so
    Node *tmp = node->children[0]->children[0];
    // tmp is arithmetic_statement->elem
    // cout << "[get_args_addr] tmp is "<< endl; tmp->print_info();
    args->push_back(tmp->ir_build_addr());
    if (node->child_num == 1) {
      break;
    } else {
      node = node->children[2];
    }
  }
  return args;
}

// declaration_funct_list: declaration_funct declaration_funct_list
// declaration_funct: declaration | funct
llvm::Value *Node::ir_build() {
#ifdef DEBUG
  cout << "[ir_build ]" << endl;
  this->print_info();
#endif
  // declaration_funct: declaration | funct
  if (this->node_type->compare("declaration_funct") == 0) {
    if (this->children[0]->node_type->compare("declaration") == 0) {
      return this->children[0]->ir_build_declaration();
    } else {
      return this->children[0]->ir_build_funct();
    }
  }
  // declaration_funct -> declaration_funct[1]
  for (int i = 0; i < this->child_num; ++i) {
    if (this->children[i] != nullptr) this->children[i]->ir_build();
  }
  return NULL;
}

// elem: ID             #done
//     | ID [ arithmetic ]    #done
//     | funct_call     #to be done
llvm::Value *Node::ir_build_addr() {
#ifdef DEBUG
  cout << "[ir_build_addr ]" << endl;
  this->print_info();
#endif
  // elem: ID
  if (this->child_num == 1) {
    return generator->find_value(*this->children[0]->node_name);
    // elem: ID [ arithmetic_statement ]
  } else if (this->child_num == 4) {  // value: ID [x]
    // cout << "[ir_build_addr] "<<"array fetch"<<endl;
    llvm::Value *array_value =
        generator->find_value(*this->children[0]->node_name);
    // cout << "here" <<endl;
    llvm::Value *index_value = this->children[2]->ir_build_arithmetic_statement();
    vector<llvm::Value *> index_list;
    index_list.push_back(builder.getInt32(0));
    index_list.push_back(index_value);
    // var value
    return builder.CreateInBoundsGEP(
        array_value, llvm::ArrayRef<llvm::Value *>(index_list), "tmp_var");
  } else {
    // ERROR
  }
  // cout << "[ir_build_addr] here" << endl;
  return NULL;
}

llvm::Instruction::CastOps Node::get_cast_instruction(llvm::Type *src,
                                                      llvm::Type *dst) {
  if (src == llvm::Type::getFloatTy(context) &&
      dst == llvm::Type::getInt32Ty(context)) {
    return llvm::Instruction::FPToSI;
  } else if (src == llvm::Type::getInt32Ty(context) &&
             dst == llvm::Type::getFloatTy(context)) {
    return llvm::Instruction::SIToFP;
  } else if (src == llvm::Type::getInt8Ty(context) &&
             dst == llvm::Type::getFloatTy(context)) {
    return llvm::Instruction::UIToFP;
  } else if (src == llvm::Type::getInt8Ty(context) &&
             dst == llvm::Type::getInt32Ty(context)) {
    return llvm::Instruction::ZExt;
  } else if (src == llvm::Type::getInt32Ty(context) &&
             dst == llvm::Type::getInt8Ty(context)) {
    return llvm::Instruction::Trunc;
  } else {
    throw logic_error("[ERROR] wrong type_cast");
  }
}

llvm::Value *Node::type_cast(llvm::Value *src, llvm::Type *dst) {
  llvm::Instruction::CastOps op = get_cast_instruction(src->getType(), dst);
  return builder.CreateCast(op, src, dst, "tmp_type_cast");
}

// expr_statement: declaration_statement
//          | arithmetic_statement
//          | assignment
//          | funct_call
llvm::Value *Node::ir_build_exp_statement() {
#ifdef DEBUG
  cout << "[ir_build_exp_statement] " << endl;
  this->print_info();
#endif
  if (this->children[0]->node_type->compare("declaration_statement") == 0) {
    return this->children[0]->ir_build_declaration_statement();
  } else if (this->children[0]->node_type->compare("arithmetic_statement") == 0) {
    return this->children[0]->ir_build_arithmetic_statement();
  } else if (this->children[0]->node_type->compare("assignment") == 0) {
    return this->children[0]->ir_build_assignment();
  } else if (this->children[0]->node_type->compare("funct_call") == 0) {
    return this->children[0]->ir_build_funct_call();
  } else {
    return NULL;
  }
}
// declaration_statement: var_declaration                      #done
//          | var_declaration ASSIGNOP arithmetic_statement   #doing
//            var_declaration: TYPE var_list
//                           var_list: var COMMA varlist
//
llvm::Value *Node::ir_build_declaration_statement() {
#ifdef DEBUG
  cout << "[ir_build_declaration_statement] " << endl;
  this->print_info();
#endif
  this->ir_build_declaration();
  if (this->child_num == 3) {
    if (this->children[1]->node_type->compare("ASSIGNOP") == 0) {
#ifdef DEBUG
      cout << "[ir_build_declaration_statement] var should be: " << endl;
      this->children[0]->deep_print_info(0);
#endif
      // make tmp be: var_declaration-> TYPE varlist, be the var_list
      //                                 ^
      Node *tmp = this->children[0]->children[1];
      while (true) {
        if (tmp->child_num == 3) {
          tmp = tmp->children[2];
        } else {
          tmp = tmp->children[0];
          break;
        }
      }
#ifdef DEBUG
      cout << "[ir_build_declaration_statement] finally tmp should be: " << endl;
      tmp->deep_print_info(0);
#endif
      llvm::Value *left = tmp->ir_build_addr();
      llvm::Value *right = this->children[2]->ir_build_arithmetic_statement();
      if (right->getType() != left->getType()->getPointerElementType()) {
        right =
            this->type_cast(right, left->getType()->getPointerElementType());
      }
      return builder.CreateStore(right, left);
    } else {
      // error
      return NULL;
    }
  } else {
    return NULL;
  }
}

// arithmetic_statement: elem AND arithmetic_statement
//          | elem OR arithmetic_statement
//          | NOT arithmetic_statement
//          | elem RELOP arithmetic_statement
//          | elem PLUS arithmetic_statement
//          | elem MINUS arithmetic_statement
//          | elem STAR arithmetic_statement
//          | elem DIV arithmetic_statement
//          | elem MODULO arithmetic_statement
//          | MINUS arithmetic_statement
//          | LBRACKET arithmetic_statement RBRACKET
//          | elem
llvm::Value *Node::ir_build_arithmetic_statement() {
#ifdef DEBUG
  cout << "[ir_build_arithmetic_statement] " << endl;
  this->print_info();
#endif
  // arithmetic_statement: elem
  if (this->child_num == 1) {
    return this->children[0]->ir_build_elem();
  } else if (this->child_num == 4 &&
             this->children[1]->node_type->compare("LSB") == 0) {
    return this->children[0]->ir_build_elem();
  }

  //~:NOT ~ | MINUS ~
  else if (this->child_num == 2) {
    if (this->children[0]->node_type->compare("MINUS") == 0) {
      return builder.CreateNeg(this->children[1]->ir_build_arithmetic_statement(),
                               "tmp_neg");
    } else if (this->children[0]->node_type->compare("NOT") == 0) {
      llvm::Value *tmp = this->children[1]->ir_build_arithmetic_statement();
      if (tmp->getType() != llvm::Type::getInt1Ty(context)) {
        throw logic_error("cannot use types other than bool in ! Exp");
      }
      return builder.CreateNot(tmp, "tmp_not");
    }
  }
  // else situations, include logical calculation and arithmetichematic calculation
  else if (this->child_num == 3) {
    //~: ( ~ )
    if (this->children[0]->node_type->compare("LBRACKET") == 0) {
      return this->children[1]->ir_build_arithmetic_statement();
      // arithmetic: arithmetic AND arithmetic
    } else if (this->children[1]->node_type->compare("AND") == 0) {
      llvm::Value *left = this->children[0]->ir_build_arithmetic_statement();
      llvm::Value *right = this->children[2]->ir_build_arithmetic_statement();
      return builder.CreateAnd(left, right, "tmp_and");
      // arithmetic: arithmetic OR arithmetic
    } else if (this->children[1]->node_type->compare("OR") == 0) {
      llvm::Value *left = this->children[0]->ir_build_arithmetic_statement();
      llvm::Value *right = this->children[2]->ir_build_arithmetic_statement();
      // cout << "in arithmetic OR operation:" << endl;
      // this->children[0]->deep_print_info(0);
      // this->children[2]->deep_print_info(0);
      return builder.CreateOr(left, right, "tmp_or");
    } else {
      llvm::Value *left = this->children[0]->ir_build_arithmetic_statement();
      llvm::Value *right = this->children[2]->ir_build_arithmetic_statement();
      // arithmetic: elem RELOP arithmetic
      if (this->children[1]->node_type->compare("RELOP") == 0) {
        return this->ir_build_relop();
      } else {
        if (left->getType() != right->getType()) {
          if (left->getType() == llvm::Type::getFloatTy(context)) {
            right = this->type_cast(right, llvm::Type::getFloatTy(context));
          } else {
            if (right->getType() == llvm::Type::getFloatTy(context)) {
              left = this->type_cast(left, llvm::Type::getFloatTy(context));
            } else {
              if (left->getType() == llvm::Type::getInt32Ty(context)) {
                right = this->type_cast(right, llvm::Type::getInt32Ty(context));
              } else if (right->getType() == llvm::Type::getInt32Ty(context)) {
                left = this->type_cast(left, llvm::Type::getInt32Ty(context));
              } else {
                throw logic_error("cann't use bool in +-*/");
              }
            }
          }
        }
        if (this->children[1]->node_type->compare("PLUS") == 0) {
          return (left->getType() == llvm::Type::getFloatTy(context))
                     ? builder.CreateFAdd(left, right, "tmp_add_f")
                     : builder.CreateAdd(left, right, "tmp_add_i");
        } else if (this->children[1]->node_type->compare("MINUS") == 0) {
          return (left->getType() == llvm::Type::getFloatTy(context))
                     ? builder.CreateFSub(left, right, "tmp_sub_f")
                     : builder.CreateSub(left, right, "tmp_sub_i");
        } else if (this->children[1]->node_type->compare("STAR") == 0) {
          return (left->getType() == llvm::Type::getFloatTy(context))
                     ? builder.CreateFMul(left, right, "tmp_mul_f")
                     : builder.CreateMul(left, right, "tmp_mul_i");
        } else if (this->children[1]->node_type->compare("DIV") == 0) {
          return (left->getType() == llvm::Type::getFloatTy(context))
                     ? builder.CreateFDiv(left, right, "tmp_div_f")
                     : builder.CreateSDiv(left, right, "tmp_mul_f");
        } else if (this->children[1]->node_type->compare("MODULO") == 0) {
          return builder.CreateURem(left, right, "tmp_rem_f");
        } else {
          return NULL;
        }
      }
    }
  }
  return NULL;
}

// assignment : elem ASSIGNOP arithmetic_statement
llvm::Value *Node::ir_build_assignment() {
#ifdef DEBUG
  cout << "[ir_build_assignment] " << endl;
  this->print_info();
#endif

  llvm::Value *left = this->children[0]->ir_build_addr();
  llvm::Value *right = this->children[2]->ir_build_arithmetic_statement();

  if (this->children[1]->node_type->compare("ASSIGNOP") == 0) {
    if (right == NULL || left == NULL) {
      cout << " NULL in ASSIGNOP " << endl;
    }
    if (right->getType() != left->getType()->getPointerElementType()) {
      right = this->type_cast(right, left->getType()->getPointerElementType());
    }
    return builder.CreateStore(right, left);
  }
  // assignment: elem ACOP arithmetic_statement, like a += 3+1
  else if (this->children[1]->node_type->compare("ACOP") == 0) {
    llvm::Value *left_tmp = this->children[0]->ir_build_elem();

    if (right == NULL || left == NULL) {
      cout << " NULL in ACOP " << endl;
    }
    if (this->children[1]->node_name->compare("+=") == 0) {
      // cout << "here" << endl;
      right = (right->getType() == llvm::Type::getFloatTy(context))
                  ? builder.CreateFAdd(left_tmp, right, "acop_add_f")
                  : builder.CreateAdd(left_tmp, right, "acop_add_i");
    } else if (this->children[1]->node_name->compare("-=") == 0) {
      right = (right->getType() == llvm::Type::getFloatTy(context))
                  ? builder.CreateFSub(left_tmp, right, "acop_sub_f")
                  : builder.CreateSub(left_tmp, right, "acop_sub_i");
    } else if (this->children[1]->node_name->compare("*=") == 0) {
      right = (right->getType() == llvm::Type::getFloatTy(context))
                  ? builder.CreateFMul(left_tmp, right, "acop_mul_f")
                  : builder.CreateMul(left_tmp, right, "acop_mul_i");
    } else if (this->children[1]->node_name->compare("/=") == 0) {
      right = (right->getType() == llvm::Type::getFloatTy(context))
                  ? builder.CreateFDiv(left_tmp, right, "acop_div_f")
                  : builder.CreateSDiv(left_tmp, right, "acop_mul_f");
    } else if (this->children[1]->node_name->compare("%=") == 0) {
      right = builder.CreateURem(left_tmp, right, "acop_rem_f");
    }
    if (right->getType() != left->getType()->getPointerElementType()) {
      right = this->type_cast(right, left->getType()->getPointerElementType());
    }
    return builder.CreateStore(right, left);
  } else {
    return NULL;
  }
}

// funct: funct_declaration comp_statement
llvm::Value *Node::ir_build_funct() {
#ifdef DEBUG
  cout << "[ir_build_funct] " << endl;
  this->print_info();
#endif
  vector<pair<string, llvm::Type *>> *params = nullptr;
  vector<llvm::Type *> arg_types;
  // funct_declaration: TYPE ID ( para_list )
  // if funct_declaration has no para, arg_typed will be empty
  if (this->children[0]->child_num == 5) {
    params = this->children[0]->children[3]->get_para();
    for (auto it : *params) {
      arg_types.push_back(it.second);
    }
  }

  llvm::FunctionType *funct_type = llvm::FunctionType::get(
      get_llvm_type(get_value_type(this->children[0]->children[0]), 0),
      arg_types, false);
  llvm::Function *function = llvm::Function::Create(
      funct_type, llvm::GlobalValue::ExternalLinkage,
      *this->children[0]->children[1]->node_name, generator->module);
  generator->push_function(function);

  // block
  llvm::BasicBlock *new_block =
      llvm::BasicBlock::Create(context, "entry_point", function);
  builder.SetInsertPoint(new_block);

  // parameters
  if (params != nullptr) {
    int index = 0;
    for (auto &Arg : function->args()) {
      Arg.setName(params->at(index++).first);
    }
  }

  // sub routine
  this->children[1]->ir_build_comp_statement();

  // pop back
  generator->pop_function();
  return function;
}

llvm::Value *Node::ir_build_funct_call() {
#ifdef DEBUG
  cout << "[ir_build_funct_call] " << endl;
  this->print_info();
#endif
  if (this->child_num == 3) {
    llvm::Function *func =
        generator->module->getFunction(*this->children[0]->node_name);
    if (func == nullptr) {
      throw logic_error("[ERROR] Funtion not defined: " +
                        *this->children[0]->node_name);
    }
    return builder.CreateCall(func, nullptr, "calltmp");
  }
  if (this->child_num == 4) {
    if (this->children[0]->node_name->compare("printf") == 0) {
      return this->ir_build_printf();
    }
    if (this->children[0]->node_name->compare("println") == 0) {
      return this->ir_build_println();
    }
    if (this->children[0]->node_name->compare("scan") == 0) {
      return this->ir_build_scan();
    }
    llvm::Function *func =
        generator->module->getFunction(*this->children[0]->node_name);
    if (func == nullptr) {
      throw logic_error("[ERROR] Funtion not defined: " +
                        *this->children[0]->node_name);
    }
    vector<llvm::Value *> *args = this->children[2]->get_args();
    return builder.CreateCall(func, *args, "call_tmp");
  }
  return NULL;
}

// elem: INTEGER    #done
//     | FLOAT      #done
//     | CHAR       #done
//     | STRING     #done
//     | ID         #done
//     | ID [arithmetic]  #done
//     | BOOL       #done
//     | funct_call #doing
//     | arithmetic_statement  #deleted cuz it is wrong

llvm::Value *Node::ir_build_elem() {
#ifdef DEBUG
  cout << "[ir_build_elem] " << endl;
  this->print_info();
  cout << "[ir_build_elem] this->child_0 is " << endl;
  this->children[0]->print_info();
#endif

  if (this->children[0]->node_type->compare("INTEGER") == 0) {
    return builder.getInt32(stoi(*this->children[0]->node_name));
  } else if (this->children[0]->node_type->compare("FLOAT") == 0) {
    return llvm::ConstantFP::get(
        builder.getFloatTy(),
        llvm::APFloat(stof(*this->children[0]->node_name)));
  } else if (this->children[0]->node_type->compare("BOOLEAN") == 0) {
    if (this->children[0]->node_name->compare("true") == 0 ||
        this->children[0]->node_name->compare("True") == 0) {
      return builder.getInt1(true);
    } else {
      return builder.getInt1(false);
    }
  } else if (this->children[0]->node_type->compare("CHAR") == 0) {
    // char
    if (this->children[0]->node_name->size() == 3)
      return builder.getInt8(this->children[0]->node_name->at(1));
    else {
      if (this->children[0]->node_name->compare("'\\n'") == 0) {
        return builder.getInt8('\n');
      } else if (this->children[0]->node_name->compare("'\\\\'") == 0) {
        return builder.getInt8('\\');
      } else if (this->children[0]->node_name->compare("'\\a'") == 0) {
        return builder.getInt8('\a');
      } else if (this->children[0]->node_name->compare("'\\b'") == 0) {
        return builder.getInt8('\b');
      } else if (this->children[0]->node_name->compare("'\\f'") == 0) {
        return builder.getInt8('\f');
      } else if (this->children[0]->node_name->compare("'\\t'") == 0) {
        return builder.getInt8('\t');
      } else if (this->children[0]->node_name->compare("'\\v'") == 0) {
        return builder.getInt8('\v');
      } else if (this->children[0]->node_name->compare("'\\''") == 0) {
        return builder.getInt8('\'');
      } else if (this->children[0]->node_name->compare("'\\\"'") == 0) {
        return builder.getInt8('\"');
      } else if (this->children[0]->node_name->compare("'\\0'") == 0) {
        return builder.getInt8('\0');
      } else {
        throw logic_error("[ERROR] char not defined: " +
                          *this->children[0]->node_name);
      }
    }
  } else if (this->children[0]->node_type->compare("STRING") == 0) {
    // string
    string str = this->children[0]->node_name->substr(
        1, this->children[0]->node_name->length() - 2);
    llvm::Constant *str_const =
        llvm::ConstantDataArray::getString(context, str);
    llvm::Value *globalVar = new llvm::GlobalVariable(
        *generator->module, str_const->getType(), true,
        llvm::GlobalValue::PrivateLinkage, str_const, "_Const_String_");
    vector<llvm::Value *> index_list;
    index_list.push_back(builder.getInt32(0));
    index_list.push_back(builder.getInt32(0));
    // var value
    llvm::Value *var_ptr = builder.CreateInBoundsGEP(
        globalVar, llvm::ArrayRef<llvm::Value *>(index_list), "tmpvar");
    return var_ptr;
  }
  // elem: ID
  else if (this->children[0]->node_type->compare("ID") == 0 &&
           this->child_num == 1) {
    // always return var value
    llvm::Value *var_ptr = generator->find_value(*this->children[0]->node_name);
    if (var_ptr->getType()->isPointerTy() &&
        !(var_ptr->getType()->getPointerElementType()->isArrayTy())) {
      return builder.CreateLoad(var_ptr->getType()->getPointerElementType(),
                                var_ptr, "tmpvar");
    } else {
      return var_ptr;
    }
    // elem: ID [ arithmetic_statement ]
  } else if (this->children[0]->node_type->compare("ID") == 0 &&
             this->child_num == 4) {
    llvm::Value *array_value =
        generator->find_value(*this->children[0]->node_name);
    llvm::Value *index_value = this->children[2]->ir_build_arithmetic_statement();
    if (index_value->getType() != llvm::Type::getInt32Ty(context)) {
      index_value =
          this->type_cast(index_value, llvm::Type::getInt32Ty(context));
    }
    vector<llvm::Value *> index_list;
    index_list.push_back(builder.getInt32(0));
    index_list.push_back(index_value);
    // var value
    llvm::Value *varPtr = builder.CreateInBoundsGEP(
        array_value, llvm::ArrayRef<llvm::Value *>(index_list), "tmpvar");
    return builder.CreateLoad(varPtr->getType()->getPointerElementType(),
                              varPtr, "tmpvar");
    // elem: funct_call
  } else if (this->children[0]->node_type->compare("funct_call") == 0) {
    // cout << "question here" << endl;
    // this->children[0]->print_info();
    return this->children[0]->ir_build_funct_call();
  }
  return NULL;
}

// arithmetic_statement: arithmetic_statement RELOP arithmetic_statement
llvm::Value *Node::ir_build_relop() {
#ifdef DEBUG
  cout << "[ir_build_relop] " << endl;
  this->print_info();
#endif
  llvm::Value *left = this->children[0]->ir_build_arithmetic_statement();
  llvm::Value *right = this->children[2]->ir_build_arithmetic_statement();
  if (left->getType() != right->getType()) {
    if (left->getType() == llvm::Type::getFloatTy(context)) {
      right = this->type_cast(right, llvm::Type::getFloatTy(context));
    } else {
      if (right->getType() == llvm::Type::getFloatTy(context)) {
        left = this->type_cast(left, llvm::Type::getFloatTy(context));
      } else {
        if (left->getType() == llvm::Type::getInt32Ty(context)) {
          right = this->type_cast(right, llvm::Type::getInt32Ty(context));
        } else if (right->getType() == llvm::Type::getInt32Ty(context)) {
          left = this->type_cast(left, llvm::Type::getInt32Ty(context));
        } else {
          throw logic_error("cann't use bool in == != >= <= < >");
        }
      }
    }
  }
  if (this->children[1]->node_name->compare("==") == 0) {
    return (left->getType() == llvm::Type::getFloatTy(context))
               ? builder.CreateFCmpOEQ(left, right, "fcmptmp")
               : builder.CreateICmpEQ(left, right, "icmptmp");
  } else if (this->children[1]->node_name->compare(">=") == 0) {
    return (left->getType() == llvm::Type::getFloatTy(context))
               ? builder.CreateFCmpOGE(left, right, "fcmptmp")
               : builder.CreateICmpSGE(left, right, "icmptmp");
  } else if (this->children[1]->node_name->compare("<=") == 0) {
    return (left->getType() == llvm::Type::getFloatTy(context))
               ? builder.CreateFCmpOLE(left, right, "fcmptmp")
               : builder.CreateICmpSLE(left, right, "icmptmp");
  } else if (this->children[1]->node_name->compare(">") == 0) {
    return (left->getType() == llvm::Type::getFloatTy(context))
               ? builder.CreateFCmpOGT(left, right, "fcmptmp")
               : builder.CreateICmpSGT(left, right, "icmptmp");
  } else if (this->children[1]->node_name->compare("<") == 0) {
    return (left->getType() == llvm::Type::getFloatTy(context))
               ? builder.CreateFCmpOLT(left, right, "fcmptmp")
               : builder.CreateICmpSLT(left, right, "icmptmp");
  } else if (this->children[1]->node_name->compare("!=") == 0) {
    return (left->getType() == llvm::Type::getFloatTy(context))
               ? builder.CreateFCmpONE(left, right, "fcmptmp")
               : builder.CreateICmpNE(left, right, "icmptmp");
  }
  return NULL;
}

// 1. declaration: var_declaration SEMI | funct_declaration SEMI
//    var_declaration: TYPE var_list
//    funct_declaration: TYPE ID LBRACKET para_list RBRACKET | TYPE ID LBRACKET
//    RBRACKET
//
// 2. declaration_statement: var_declaration | var_declaration ASSIGNOP arithmetic_statement
//    var_declaration: TYPE var_list
llvm::Value *Node::ir_build_declaration() {
#ifdef DEBUG
  cout << "[ir_build_declaration] " << endl;
  this->print_info();
#endif
  // get the type of the declarationaration
  int type = this->children[0]->children[0]->get_value_type();
  // int a,b,c...;
  if (this->children[0]->node_type->compare("var_declaration") == 0) {
    vector<pair<string, int>> *name_list =
        this->children[0]->children[1]->get_name_list(type);
    llvm::Type *llvm_type;
    for (auto it : *name_list) {
      if (it.second == VAR) {
        llvm_type = get_llvm_type(type, 0);
      } else {
        llvm_type = get_llvm_type(type + IS_ARRAY, it.second - IS_ARRAY);
      }
      if (generator->function_stack.empty()) {
        llvm::Value *tmp = generator->module->getGlobalVariable(it.first, true);
        if (tmp != nullptr) {
          throw logic_error("Redefined Variable: " + it.first);
        }
        llvm::GlobalVariable *global_var = new llvm::GlobalVariable(
            *generator->module, llvm_type, false,
            llvm::GlobalValue::PrivateLinkage, 0, it.first);
        if (llvm_type->isArrayTy()) {
          std::vector<llvm::Constant *> const_array_elem;
          llvm::Constant *constElem =
              llvm::ConstantInt::get(llvm_type->getArrayElementType(), 0);
          for (int i = 0; i < llvm_type->getArrayNumElements(); i++) {
            const_array_elem.push_back(constElem);
          }
          llvm::Constant *const_array = llvm::ConstantArray::get(
              llvm::ArrayType::get(llvm_type->getArrayElementType(),
                                   llvm_type->getArrayNumElements()),
              const_array_elem);
          global_var->setInitializer(const_array);
        } else {
          global_var->setInitializer(llvm::ConstantInt::get(llvm_type, 0));
        }
      } else {
        llvm::Value *tmp =
            generator->function_stack.top()->getValueSymbolTable()->lookup(
                it.first);
        if (tmp != nullptr) {
          throw logic_error("Redefined Variable: " + it.first);
        }
        llvm::Value *alloc = create_entry_block_allocation(
            generator->get_current_function(), it.first, llvm_type);
      }
    }
  }
  // idk whether deleting or not
  // else if(this->children[0]->node_type->compare("funct_declaration") == 0) {
  //     cout << "dwewrrew here" << endl;
  // }
  return NULL;
}

// comp_statement: LBRACE statements RBRACE
//     statements: statement statements | empty
//      statement: ...
llvm::Value *Node::ir_build_comp_statement() {
#ifdef DEBUG
  cout << "[ir_build_comp_statement] " << endl;
  this->print_info();
#endif
  Node *statements = this->children[1];
  while (true) {
    if (statements != nullptr && statements->child_num == 2) {
      statements->children[0]->ir_build_statement();
      statements = statements->children[1];
    } else {
      break;
    }
  }
  return NULL;
}

// statement: ret_statement
//     | expr_statement
//     | comp_statement
//     | loop_statement
//     | select_statement
llvm::Value *Node::ir_build_statement() {
#ifdef DEBUG
  cout << "[ir_build_statement] " << endl;
  this->print_info();
#endif
  if (this->children[0]->node_type->compare("expr_statement") == 0) {
    return this->children[0]->ir_build_exp_statement();

  } else if (this->children[0]->node_type->compare("select_statement") == 0) {
    return this->children[0]->ir_build_select_statement();

  } else if (this->children[0]->node_type->compare("loop_statement") == 0) {
    return this->children[0]->ir_build_loop_statement();

  } else if (this->children[0]->node_type->compare("ret_statement") == 0) {
    return this->children[0]->ir_build_ret_statement();

  } else if (this->children[0]->node_type->compare("comp_statement") == 0) {
    return this->children[0]->ir_build_comp_statement();
  }
  return NULL;
}

// loop_statement: WHILE LBRACKET arithmetic_statement RBRACKET statement
llvm::Value *Node::ir_build_loop_statement() {
#ifdef DEBUG
  cout << "[ir_build_loop_statement] " << endl;
  this->print_info();
#endif
  // this->print_info();
  // this->forward(generator);
  llvm::Function *function = generator->get_current_function();
  llvm::BasicBlock *condBB =
      llvm::BasicBlock::Create(context, "cond", function);
  llvm::BasicBlock *loopBB =
      llvm::BasicBlock::Create(context, "loop", function);
  llvm::BasicBlock *afterBB =
      llvm::BasicBlock::Create(context, "after_loop", function);

  global_after_basic_block.push(afterBB);

  // cond
  builder.CreateBr(condBB);
  builder.SetInsertPoint(condBB);
  // WHILE LBRACKET arithmetic_statement RBRACKET statement
  llvm::Value *cond_value = this->children[2]->ir_build_arithmetic_statement();
  cond_value = builder.CreateICmpNE(
      cond_value,
      llvm::ConstantInt::get(llvm::Type::getInt1Ty(context), 0, true),
      "whileCond");
  auto branch = builder.CreateCondBr(cond_value, loopBB, afterBB);
  condBB = builder.GetInsertBlock();

  // loop
  builder.SetInsertPoint(loopBB);
  this->children[4]->ir_build_statement();
  builder.CreateBr(condBB);

  // after
  builder.SetInsertPoint(afterBB);
  // this->backward(generator);
  global_after_basic_block.pop();
  return branch;
}

// select_statement: IF LBRACKET arithmetic_statement RBRACKET statement
//            | IF LBRACKET arithmetic_statement RBRACKET statement ELSE statement
llvm::Value *Node::ir_build_select_statement() {
#ifdef DEBUG
  cout << "[ir_build_select_statement] " << endl;
  this->print_info();
#endif
  llvm::Value *cond_value = this->children[2]->ir_build_arithmetic_statement(),
              *thenValue = nullptr, *elseValue = nullptr;
  cond_value = builder.CreateICmpNE(
      cond_value,
      llvm::ConstantInt::get(llvm::Type::getInt1Ty(context), 0, true),
      "ifCond");

  llvm::Function *function = generator->get_current_function();
  llvm::BasicBlock *thenBB =
      llvm::BasicBlock::Create(context, "then", function);
  llvm::BasicBlock *elseBB =
      llvm::BasicBlock::Create(context, "else", function);
  llvm::BasicBlock *mergeBB =
      llvm::BasicBlock::Create(context, "merge", function);

  // Then
  auto branch = builder.CreateCondBr(cond_value, thenBB, elseBB);
  builder.SetInsertPoint(thenBB);
  thenValue = this->children[4]->ir_build_statement();
  builder.CreateBr(mergeBB);
  thenBB = builder.GetInsertBlock();

  // else
  builder.SetInsertPoint(elseBB);
  if (this->child_num == 7) {
    elseValue = this->children[6]->ir_build_statement();
  }
  builder.CreateBr(mergeBB);
  elseBB = builder.GetInsertBlock();

  builder.SetInsertPoint(mergeBB);
  return branch;
}

// ret_statement: RETURN arithmetic_statement SEMI
llvm::Value *Node::ir_build_ret_statement() {
#ifdef DEBUG
  cout << "[ir_build_ret_statement] " << endl;
  this->print_info();
#endif
  auto ret_instr = this->children[1]->ir_build_arithmetic_statement();
  return builder.CreateRet(ret_instr);
}

llvm::Value *Node::ir_build_printf() {
  vector<llvm::Value *> *args = this->children[2]->get_print_args();
  return builder.CreateCall(generator->printf, *args, "print_str");
}

llvm::Value *Node::ir_build_println() {
  vector<llvm::Value *> *args = this->children[2]->get_print_args();
  llvm::Value *ret = builder.CreateCall(generator->printf, *args, "print_str");
  builder.CreateCall(generator->printf, builder.CreateGlobalStringPtr("\n"),
                     "println_token");
  return ret;
}

// funct_call: scan ( para_list )
llvm::Value *Node::ir_build_scan() {
#ifdef DEBUG
  cout << "[ir_build_scan]" << endl;
  this->print_info();
#endif
  string formatStr = "";

  // cout << "funct_call -> child_2 is :" << endl;
  // this->children[2]->print_info();
  vector<llvm::Value *> *args = this->children[2]->get_args_addr();
  // cout << "[build_scan] here after get args_addr" << endl;
  // Just common variable
  for (auto arg : *args) {
    if (arg->getType()->getPointerElementType() == builder.getInt32Ty()) {
      formatStr += "%d";
    } else if (arg->getType()->getPointerElementType() == builder.getInt8Ty()) {
      formatStr += "%c";
    } else if (arg->getType()->getPointerElementType() == builder.getInt1Ty()) {
      cout << "here" << endl;
      formatStr += "%d";
    } else if (arg->getType()->getPointerElementType() ==
               builder.getFloatTy()) {
      formatStr += "%f";
    } else if (arg->getType()->getPointerElementType()->isArrayTy() &&
               arg->getType()->getPointerElementType()->getArrayElementType() ==
                   builder.getInt8Ty()) {
      formatStr += "%s";
    } else {
      throw logic_error("[ERROR]Invalid type to read.");
    }
  }
  args->insert(args->begin(), builder.CreateGlobalStringPtr(formatStr));
  return builder.CreateCall(generator->scanf, *args, "scanf");
}

llvm::AllocaInst *create_entry_block_allocation(llvm::Function *function,
                                                llvm::StringRef var_name,
                                                llvm::Type *type) {
  llvm::IRBuilder<> TmpB(&function->getEntryBlock(),
                         function->getEntryBlock().begin());
  return TmpB.CreateAlloca(type, nullptr, var_name);
}

Json::Value Node::jsonGen() {
  Json::Value root;
  string padding = "";
  if (this->node_type->compare("TYPE") == 0 ||
      this->node_type->compare("arithmetic_statement") == 0) {
    int valueType = this->get_value_type();
    switch (valueType) {
      case VOID:
        padding = "void";
        break;
      case VAR:
        padding = "var";
        break;
      case IS_ARRAY:
        padding = "array";
        break;
      case FUN:
        padding = "func";
        break;
      case TYPE_INTEGER:
        padding = "int";
        break;
      case TYPE_INTEGER_ARRAY:
        padding = "int array";
        break;
      case TYPE_FLOAT:
        padding = "float";
        break;
      case TYPE_FLOAT_ARRAY:
        padding = "float array";
        break;
      case TYPE_CHAR:
        padding = "char";
        break;
      case TYPE_CHAR_ARRAY:
        padding = "char array";
        break;
      case TYPE_BOOL:
        padding = "bool";
        break;
      case TYPE_BOOL_ARRAY:
        padding = "bool array";
        break;
      default:
        break;
    }
  }
  root["name"] = *this->node_type + (padding == "" ? "" : ": " + padding);
  for (int i = 0; i < this->child_num; i++) {
    if (this->children[i]) {
      root["children"].append(this->children[i]->jsonGen());
    }
  }
  return root;
}
