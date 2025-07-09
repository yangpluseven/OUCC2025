#include <iostream>
#include <fstream>
#include <unistd.h>
#include "define.h"
#include "ast.h"
#include "genIR.h"
#include "opt.h"
#include "LT_tree.h"
#include "mem2reg.h"
#include "backend.h"
#include "ConstantFolding.h"
#include "BasicOperation.h"
#include "SimplifyCFG.h"


extern unique_ptr<CompUnitAST> root;
extern int yyparse();
extern FILE *yyin;

int main(int argc, char **argv) {
    /******************************  Argument Parser  ******************************/
    if(argc < 2) {
        std::cout << "Compiler Usage: " << argv[0] << " [options] <filename>\n"
                  << "Options:\n"
                  << "  -S          Print assembly code\n"
                  << "  -I          Print intermediate representation (IR)\n"
                  << "  -o <file>   Output to specified file (default: stdout)\n"
                  << "  -O          Enable optimization (not implemented yet)\n";
        return -1;
    }
    // TODO: advanced argument parser
    char *filename = nullptr;
    int print_ir = false;
    int print_asm = false;
    std::string output = "-";
    int opt;
    bool isO1 = false;
    while((opt = getopt(argc, argv, "Sco:O::I")) != -1) {
        switch(opt) {
            case 'S': {
                print_asm = true;
                print_ir = false;
                break;
            }
            case 'I': {
                print_ir = true;
                print_asm = false;
                break;
            }
            case 'o': {
                output = optarg;
                break;
            }
            case 'O': {
                isO1 = true;
                break;
            }
            default: {
                break;
            }
        }
    }
    filename = argv[optind];
    yyin = fopen(filename, "r");
    if(yyin == nullptr) {
        std::cout << "yyin open" << filename << "failed" << std::endl;
        return -1;
    }

    /******************************  Front-end  ******************************/
    yyparse();
    // Generate IR from AST
    GenIR genIR;
    root->accept(genIR);
    std::unique_ptr<Module> m = genIR.getModule();

    /******************************  Middle-end  ******************************/
    // TODO Run IR optimization
    // if(isO1) {
    // std::vector<Optimization *> Opt;
    // Opt.push_back(new DeadCodeDeletion(m.get()));
    // Opt.push_back(new ConstSpread(m.get()));
    // Opt.push_back(new CombineInstr(m.get()));
    // Opt.push_back(new DomainTree(m.get()));
    // Opt.push_back(new SimplifyJump(m.get()));
    // Opt.push_back(new LoopInvariant(m.get()));
    // Opt.push_back(new SimplifyJump(m.get()));
    // for (auto x : Opt)
    //     x->execute();
    // }
    // // 
    LengauerTarjan domTree(m.get());
    domTree.execute();

    Mem2Reg mem2reg(m.get());
    mem2reg.execute();

    ConstFolding constantFolding(m.get());
    constantFolding.execute();

    SimplifyUnconditionalBranch simplifyCFG(m.get());
    simplifyCFG.execute();


    /******************************  Back-end  ******************************/
    // Open output file./
    std::ofstream fout;
    std::ostream *out;
    if(output == "-") {
        out = &std::cout;
    } else {
        fout.open(output);
        out = &fout;
    }

    // Print IR result
    const std::string IR = m->print();
    if(print_ir) {
        *out << IR << std::endl;
    }

    // Generate assembly file
    if(print_asm) {
        auto builder = new RiscvBuilder();
        const std::string RiscvCode = builder->buildRISCV(m.get());
        *out << RiscvCode << std::endl;
    }
    return 0;
}
