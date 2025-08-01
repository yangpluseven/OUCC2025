#include "CLI/CLI.hpp"
#include "parser/generate_ir.h"

extern int yyparse();
extern FILE *yyin;
extern unique_ptr<CompUnit> root;

enum class OutputTypeEnum { LLVM, MIR, ASM };

int main(int argc, const char *argv[]) {
  CLI::App app{"A compiler for SysY language", "compile2025-0"};
  app.require_subcommand(1);

  std::string sourceFile;
  app.add_option("sources", sourceFile, "Source file to compile")
      ->required()
      ->check(CLI::ExistingFile);

  std::string outputFile;
  app.add_option("-o,--output", outputFile, "Output file")
      ->default_str("a.out")
      ->check(CLI::NonexistentPath);
  std::ofstream ofs(outputFile);
  if (!ofs) {
    std::cerr << "Error opening output file: " << outputFile << std::endl;
    exit(1);
  }

  bool isOpt1 = false;
  app.add_flag("-O1", isOpt1, "Enable optimization level 1");

  bool emitLLVM = false, emitMIR = false, emitASM = false;
  app.add_flag("-emit-llvm", emitLLVM, "Emit LLVM IR as output");
  app.add_flag("-emit-mir", emitMIR, "Emit MIR as output");
  app.add_flag("-S,--assembly", emitASM, "Emit assembly code as output");

  try {
    app.parse(argc, argv);
  } catch (const CLI::ParseError &e) {
    return app.exit(e);
  }

  OutputTypeEnum outputType;
  if (emitLLVM)
    outputType = OutputTypeEnum::LLVM;
  else if (emitMIR)
    outputType = OutputTypeEnum::MIR;
  else
    outputType = OutputTypeEnum::ASM;

  std::cout << "compile2025-0 (C) OUCC. 2025" << std::endl;
  std::cout << "Compiling " << sourceFile << " to " << outputFile
            << " with optimization level " << (isOpt1 ? "1" : "0") << std::endl;

  yyparse();
  GenerateIR genIR;
  root->accept(genIR);
  auto mod = genIR.getModule();
  switch (outputType) {
  case OutputTypeEnum::LLVM:
    std::cout << "Generating LLVM IR..." << std::endl;

    for (const auto &glob : mod->getGlobals())
      ofs << glob->str() << "\n";
    if (mod->hasGlobal())
      ofs << "\n";

    auto funcs = mod->getFunctions();
    std::sort(funcs.begin(), funcs.end(), [](const auto &lhs, const auto &rhs) {
      if (lhs.empty() != rhs.empty())
        return lhs.empty() < rhs.empty();
      return lhs.getRawName() < rhs.getRawName();
    });

    for (const auto &func : funcs) {
      ofs << func->str() << "\n";
    }

    ofs.close();
    if (ofs.fail())
      std::cerr << "Error writing to output file: " << outputFile << std::endl;
    else
      std::cout << "LLVM IR written to " << outputFile << std::endl;
    break;

  case OutputTypeEnum::MIR:
    std::cout << "Generating MIR..." << std::endl;

    for (const auto &mFunc : mod->getMFuncs())
      ofs << mFunc->str() << "\n";

    ofs.close();
    if (ofs.fail())
      std::cerr << "Error writing to output file: " << outputFile << std::endl;
    else
      std::cout << "MIR written to " << outputFile << std::endl;
    break;
  case OutputTypeEnum::ASM:
    return 1; // Not implemented yet
  }

  return 0;
}
