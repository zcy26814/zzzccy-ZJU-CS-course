#include "ast.h"
#include "type.h"
#include <fstream>
#include "code_gen.h"
#include "grammar.hpp"

extern Node *ROOT;
extern code_gen *generator;
extern int yyparse();

int main() {
    int flag = yyparse();
    #ifdef DEBUG
    if(flag){
        cout<< ">> parsing failed <<" << endl;
    }else{
        cout<< ">> parsing successfully <<" << endl;
    }
    #endif
    auto root = ROOT->jsonGen();

    string jsonFile = "./visualization/ast.json";
    std::ofstream ast_json(jsonFile);
    if(ast_json.is_open()){
        ast_json << root;
        ast_json.close();
    }

    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();

    generator = new code_gen();
    generator->generate(ROOT);

    return 0;
}