#include "code_gen.h"

code_gen* generator;

code_gen::code_gen(/* args */) {
  this->module = new llvm::Module("main", context);
  this->printf = this->create_printf();
  this->scanf = this->create_scanf();
}

llvm::Function* code_gen::get_current_function() {
  return function_stack.top();
}

void code_gen::push_function(llvm::Function* func) {
  function_stack.push(func);
}

void code_gen::pop_function() { function_stack.pop(); }

llvm::Value* code_gen::find_value(const std::string& name) {
  llvm::Value* result =
      function_stack.top()->getValueSymbolTable()->lookup(name);
  if (result != nullptr) {
    return result;
  }
  result = module->getGlobalVariable(name, true);
  if (result == nullptr) {
    cout << "[ERROR]Undeclarationared variable: " << name << endl;
  }
  return result;
  // return NULL;
}

llvm::Function* code_gen::create_printf() {
  std::vector<llvm::Type*> arg_types;
  arg_types.push_back(builder.getInt8PtrTy());
  auto printf_type = llvm::FunctionType::get(
      builder.getInt32Ty(), llvm::makeArrayRef(arg_types), true);
  auto func = llvm::Function::Create(printf_type, llvm::Function::ExternalLinkage,
                                                  llvm::Twine("printf"), this->module);
  func->setCallingConv(llvm::CallingConv::C);
  return func;
}

llvm::Function* code_gen::create_scanf() {
  auto scanf_type = llvm::FunctionType::get(builder.getInt32Ty(), true);
  auto func =
      llvm::Function::Create(scanf_type, llvm::Function::ExternalLinkage,
                             llvm::Twine("scanf"), this->module);
  func->setCallingConv(llvm::CallingConv::C);
  return func;
}

void code_gen::generate(Node* root) {
  root->ir_build();
  this->module->print(llvm::outs(), nullptr);
}