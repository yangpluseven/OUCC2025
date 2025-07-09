#pragma once

#include <map>
#include "ast.h"
#include "ir.h"

// 作用域，符号表管理器
class Scope {
public:
    // 创建新的作用域，初始化为空，栈式结构，最新作用域在最后一层
    void enter() { symbol.push_back({}); }
    // 退出当前作用域
    void exit() { symbol.pop_back(); }
    // 是否在全局作用域，判断很简单，只需要看符号表的层数即可，未嵌套的为全局作用域
    bool in_global() { return symbol.size() == 1; }
    /* 插入新符号到当前作用域（数组最后一个元素）
     * 如果当前作用域已经存在该符号，则返回false
     * 如果当前作用域不存在该符号，则插入成功，返回true
     * 注意：函数名和变量名可以同名，但是//!不懂这样插入是否会有问题
    */
    bool push(std::string name, Value* val) {
        return (symbol[symbol.size() - 1].insert({name, val})).second;
    }
    // 
    Value* find(std::string name) {
        for(auto s = symbol.rbegin(); s != symbol.rend(); s++) {
            auto iter = s->find(name);
            if(iter != s->end()) {
                return iter->second;
            }
        }
        return nullptr;
    }

private:
    std::vector<std::map<std::string, Value*>> symbol;
};

// 中间代码生成器
class GenIR: public Visitor {
public:
    Scope scope;
    IRStmtBuilder* builder;
    std::unique_ptr<Module> module; // 将生成的中间代码存储在Module中

    GenIR() {
        module = std::unique_ptr<Module>(new Module());
        builder = new IRStmtBuilder(nullptr, module.get());
        auto TyVoid = module->void_ty_;
        auto TyInt32 = module->int32_ty_;
        auto TyInt32Ptr = module->get_pointer_type(module->int32_ty_);
        auto TyFloat = module->float32_ty_;
        auto TyFloatPtr = module->get_pointer_type(module->float32_ty_);
        // SysY2022标准库函数，具体含义见文件"SysY2022运行时库-V1.pdf"
        // int getint();
        auto input_type = new FunctionType(TyInt32, {});
        auto get_int = new Function(input_type, "getint", module.get());
        // char getch();
        input_type = new FunctionType(TyInt32, {});
        auto get_char = new Function(input_type, "getch", module.get());
        // float getfloat();
        input_type = new FunctionType(TyFloat, {});
        auto get_float = new Function(input_type, "getfloat", module.get());
        // int getarray(int[]);
        std::vector<Type*> input_params;
        std::vector<Type*>().swap(input_params); //swap用于清空input_params，同时将值放入临时vector中
        input_params.push_back(TyInt32Ptr);
        input_type = new FunctionType(TyInt32, input_params);
        auto get_int_array = new Function(input_type, "getarray", module.get());
        // float getfarray(float[]);
        std::vector<Type*>().swap(input_params);
        input_params.push_back(TyFloatPtr);
        input_type = new FunctionType(TyInt32, input_params);
        auto get_float_array = new Function(input_type, "getfarray", module.get());
        // void putint(int);
        std::vector<Type*> output_params;
        std::vector<Type*>().swap(output_params);
        output_params.push_back(TyInt32);
        auto output_type = new FunctionType(TyVoid, output_params);
        auto put_int = new Function(output_type, "putint", module.get());
        // void putfloat(float);
        std::vector<Type*>().swap(output_params);
        output_params.push_back(TyFloat);
        output_type = new FunctionType(TyVoid, output_params);
        auto put_float = new Function(output_type, "putfloat", module.get());
        // void putch(int);
        std::vector<Type*>().swap(output_params);
        output_params.push_back(TyInt32);
        output_type = new FunctionType(TyVoid, output_params);
        auto put_char = new Function(output_type, "putch", module.get());
        // void putarray(int[], int);
        std::vector<Type*>().swap(output_params);
        output_params.push_back(TyInt32);
        output_params.push_back(TyInt32Ptr);
        output_type = new FunctionType(TyVoid, output_params);
        auto put_int_array = new Function(output_type, "putarray", module.get());
        // void putfarray(float[], int);
        std::vector<Type*>().swap(output_params);
        output_params.push_back(TyInt32);
        output_params.push_back(TyFloatPtr);
        output_type = new FunctionType(TyVoid, output_params);
        auto put_float_array = new Function(output_type, "putfarray", module.get());
        // 剩余void putf(<格式串>, <参数列表>);
        // TODO
        // 计时函数：_sysy_starttime()和_sysy_stoptime()
        output_params.clear();
        auto time_type = new FunctionType(TyVoid, output_params);
        auto sysy_start_time = new Function(time_type, "_sysy_starttime", module.get());
        auto sysy_stop_time = new Function(time_type, "_sysy_stoptime", module.get());
        //!内存操作函数存疑~
        // ARM Embedded Application Binary Interface（EABI） 是arm的？好像risc-V不能直接用
        // 在riscv.cpp中好像有转换
        // memcpy：内存拷贝
        output_params.clear();
        output_params.push_back(TyInt32Ptr);
        output_params.push_back(TyInt32Ptr);
        output_params.push_back(TyInt32);
        output_type = new FunctionType(TyVoid, output_params);
        auto memcpy = new Function(output_type, "__aeabi_memcpy4", module.get());
        // memclr：内存清零
        output_params.clear();
        output_params.push_back(TyInt32Ptr);
        output_params.push_back(TyInt32);
        output_type = new FunctionType(TyVoid, output_params);
        auto memclr = new Function(output_type, "__aeabi_memclr4", module.get());
        // memset：内存设置
        output_params.push_back(TyInt32);
        output_type = new FunctionType(TyVoid, output_params);
        auto memset = new Function(output_type, "__aeabi_memset4", module.get());
        // llvm.memset.p0.i32：LLVM内存设置函数，相当于C语言中的memset
        output_params.clear();
        output_type = new FunctionType(TyVoid, output_params);
        auto llvm_memset = new Function(output_type, "llvm.memset.p0.i32", module.get());
        // 将所有函数添加到符号表中
        scope.enter();
        scope.push("getint", get_int);
        scope.push("getfloat", get_float);
        scope.push("getch", get_char);
        scope.push("getarray", get_int_array);
        scope.push("getfarray", get_float_array);
        scope.push("putint", put_int);
        scope.push("putfloat", put_float);
        scope.push("putch", put_char);
        scope.push("putarray", put_int_array);
        scope.push("putfarray", put_float_array);
        scope.push("starttime", sysy_start_time);
        scope.push("stoptime", sysy_stop_time);
        scope.push("memcpy", memcpy);
        scope.push("memclr", memclr);
        scope.push("memset", memset);
        scope.push("llvm.memset.p0.i32", llvm_memset);
    }
    std::unique_ptr<Module> getModule() { return std::move(module); }

    void checkInitType() const;

    static int getNextDim(vector<int> &dimensionsCnt, int up, int cnt);

    void localInit(Value* ptr, vector<unique_ptr<InitValAST>> &list, vector<int> &dimensionsCnt, int up);

    static int getNextDim(vector<int> &elementsCnts, int up);

    ConstantArray* globalInit(vector<int> &dimensions, vector<ArrayType*> &arrayTys, int up, vector<unique_ptr<InitValAST>> &list);

    static void mergeElements(vector<int> &dimensions, vector<ArrayType*> &arrayTys, int up, int dimAdd,
                                vector<Constant*> &elements, vector<int> &elementsCnts);

    void finalMerge(vector<int> &dimensions, vector<ArrayType*> &arrayTys, int up, vector<Constant*> &elements, vector<int> &elementsCnts) const;

    bool checkCalType(Value* *val, int* intVal, float* floatVal);

    void checkCalType(Value* *val);

    void visit(CompUnitAST &ast) override;
    void visit(DeclDefAST &ast) override;
    void visit(DeclAST &ast) override;
    void visit(DefAST &ast) override;
    void visit(InitValAST &ast) override;
    void visit(FuncDefAST &ast) override;
    void visit(FuncFParamAST &ast) override;
    void visit(BlockAST &ast) override;
    void visit(BlockItemAST &ast) override;
    void visit(StmtAST &ast) override;
    void visit(ReturnStmtAST &ast) override;
    void visit(SelectStmtAST &ast) override;
    void visit(IterationStmtAST &ast) override;
    void visit(AddExpAST &ast) override;
    void visit(LValAST &ast) override;
    void visit(MulExpAST &ast) override;
    void visit(UnaryExpAST &ast) override;
    void visit(PrimaryExpAST &ast) override;
    void visit(CallAST &ast) override;
    void visit(NumberAST &ast) override;
    void visit(RelExpAST &ast) override;
    void visit(EqExpAST &ast) override;
    void visit(LAndExpAST &ast) override;
    void visit(LOrExpAST &ast) override;
};
