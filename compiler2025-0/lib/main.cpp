#include "parser/ast.h"
#include "parser/define.h"
#include "parser/generate_ir.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>

extern unique_ptr<CompUnit> root;
extern int yyparse();
extern FILE *yyin;

ir::Module *_module;

void emitLLVM(std::string filename) {
  std::ofstream ofs(filename);
  if (!ofs.is_open()) {
    std::cout << "Open " << filename << " failed" << std::endl;
  }

  for (const auto &global : _module->getGlobals()) {
    ofs << global->str() << "\n";
  }

  if (_module->hasGlobal()) {
    ofs << "\n";
  }

  auto functions = _module->getFunctions();
  sort(functions.begin(), functions.end(),
       [](const ir::Function *func1, const ir::Function *func2) {
         if (func1->empty() != func2->empty()) {
           return func1->empty() < func2->empty();
         }
         return func1->getRawName() < func2->getRawName();
       });

  for (const auto &func : functions) {
    ofs << func->str() << "\n";
  }

  ofs.close();
  if (ofs.fail()) {
    std::cout << "Write " << filename << " failed" << std::endl;
  }
}

int main(int argc, char *argv[]) {
  char *filename = argv[1];
  yyin = fopen(filename, "r");
  if (!yyin) {
    std::cout << "Open " << filename << " failed" << std::endl;
    return -1;
  }

  yyparse();
  GenerateIR genIR;
  root->accept(genIR);
  _module = genIR.getModule();
  emitLLVM("./ctest/default_output.ll");
}