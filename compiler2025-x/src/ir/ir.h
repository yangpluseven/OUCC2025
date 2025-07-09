#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class Type;
class IntegerType;
class ArrayType;
class PointerType;
class FunctionType;
class Value;
class Constant;
class ConstantInt;
class ConstantFloat;
class ConstantArray;
class ConstantZero;
class Module;
class GlobalVariable;
class Function;
class BasicBlock;
class Argument;
class Instruction;
class BinaryInst;
class UnaryInst;
class ICmpInst;
class FCmpInst;
class CallInst;
class BranchInst;
class ReturnInst;
class GetElementPtrInst;
class StoreInst;
class LoadInst;
class AllocaInst;

struct Use {
    Value* val_;
    unsigned int arg_no_; // 操作数的序号，如func(a,b)中a的序号为0，b的序号为1

    Use(Value* val, unsigned int no): val_(val), arg_no_(no) {}
};

//-----------------------------------------------Type-----------------------------------------------
class Type {
public:
    enum TypeID {
        VoidTyID,     // Void
        LabelTyID,    // Labels, e.g., BasicBlock
        IntegerTyID,  // Integers, include 32 bits and 1 bit
        FloatTyID,    // Floats, only 32 bits
        FunctionTyID, // Functions
        ArrayTyID,    // Arrays
        PointerTyID,  // Pointer
    };
    TypeID tid_;

    explicit Type(TypeID tid): tid_(tid) {}
    ~Type() = default;
    virtual std::string print();
};

class IntegerType: public Type {
public:
    unsigned num_bits_; // only 1 or 32 in SysY2022

    // 调用Type构造函数并设置Type::tid_为IntegerTyID
    explicit IntegerType(unsigned num_bits): Type(Type::IntegerTyID), num_bits_(num_bits) {}
};

//[2 * [3 * i32]]: num_elements_ = 2, contained_ = [3 * i32]
class ArrayType: public Type {
public:
    Type* contained_;       // The element type of the array.
    unsigned num_elements_; // Number of elements in the array.

    ArrayType(Type* contained, unsigned num_elements): Type(Type::ArrayTyID), num_elements_(num_elements), contained_(contained) {}
};

//[2 * [3 * i32]]*
class PointerType: public Type {
public:
    Type* contained_; // The element type of the pointer.

    PointerType(Type* contained): Type(Type::PointerTyID), contained_(contained) {}
};

// declare i32 @putarray(i32, i32*)
class FunctionType: public Type {
public:
    Type* result_; // 函数返回值类型
    std::vector<Type*> args_; // 函数形参类型列表

    FunctionType(Type* result, std::vector<Type*> params): Type(Type::FunctionTyID) {
        result_ = result;
        for(Type* p: params) { // 深拷贝
            args_.push_back(p);
        }
    }
};

//-----------------------------------------------Value-----------------------------------------------
class Value {
public:
    Type* type_;
    std::string name_;
    std::list<Use> use_list_; // 所有引用该Value的Instruction的集合，以及该Value在该Instruction的第几个操作数位置被引用

    explicit Value(Type* ty, const std::string& name = ""): type_(ty), name_(name) {}
    ~Value() = default;
    virtual std::string print() = 0;
    bool is_constant() { return name_[0] == 0; } // 常量的名字均为""，即'\0'，因此name_[0] == 0
    std::list<Use>::iterator add_use(Value* val, unsigned arg_no) {
        use_list_.emplace_back(val, arg_no); // Use(Value*, unsigned int)
        std::list<Use>::iterator re = use_list_.end();
        return --re; // 返回最后一个元素的迭代器，方便操作
    }
    void remove_use(std::list<Use>::iterator it) { use_list_.erase(it); } // 删除迭代器指出的use
    void remove_use(Value* val) { // 删除所有与val相关的use
        auto is_val = [val](const Use& use) { return use.val_ == val; };
        use_list_.remove_if(is_val);
    }
    void replace_all_use_with(Value* new_val); // 替换原Value的所有引用为新Value
    bool remove_used(Instruction* user, unsigned int i); // user的第i个操作数准备不再使用this，因此删除this与user相关的use联系
};

class ValUndef : public Value {
public:
	explicit ValUndef(Type* ty, const std::string& name = "undef") :Value(ty, name) {}
	~ValUndef() = default;

	ValUndef* create(Type* ty, const std::string& name = "undef") {
		return new ValUndef(ty, name);
	}

	std::string print() {
		return name_;
	}
};


//-----------------------------------------------Constant-----------------------------------------------
// 常量都是无名的(name == "")
class Constant: public Value {
public:
    Constant(Type* ty, const std::string& name = ""): Value(ty, name) {}
    ~Constant() = default;
};

// i32 -23
class ConstantInt: public Constant {
public:
    int value_;

    ConstantInt(Type* ty, int val): Constant(ty, ""), value_(val) {}
    virtual std::string print() override;
};

// float 0x4057C21FC0000000
// float -3.300000e+04
class ConstantFloat: public Constant {
public:
    float value_;

    ConstantFloat(Type* ty, float val): Constant(ty, ""), value_(val) {}
    virtual std::string print() override; // 64位
    std::string print32(); // 32位
};

//[3 * i32] [i32 42, i32 11, i32 74]
class ConstantArray: public Constant {
public:
    std::vector<Constant*> const_array;

    ConstantArray(ArrayType* ty, const std::vector<Constant*>& val): Constant(ty, "") {
        this->const_array.assign(val.begin(), val.end());
    }
    ~ConstantArray() = default;
    virtual std::string print() override;
};

// i32 zeroinitializer
//[2 * [100 * float]] zeroinitializer
// 注意zeroinitializer是有类型的！
class ConstantZero: public Constant {
public:
    ConstantZero(Type* ty): Constant(ty, "") {}
    virtual std::string print() override;
};

//-----------------------------------------------Module-----------------------------------------------
class Module {
public:
    std::vector<GlobalVariable*> global_list_;
    std::vector<Function*> function_list_;
    IntegerType* int1_ty_;
    IntegerType* int32_ty_;
    Type* float32_ty_;
    Type* label_ty_;
    Type* void_ty_;
    std::map<Type* , PointerType*> pointer_map_;
    std::map<std::pair<Type* , int>, ArrayType*> array_map_;

    explicit Module() {
        void_ty_ = new Type(Type::VoidTyID);
        label_ty_ = new Type(Type::LabelTyID);
        int1_ty_ = new IntegerType(1);
        int32_ty_ = new IntegerType(32);
        float32_ty_ = new Type(Type::FloatTyID);
    }
    ~Module() {
        delete void_ty_;
        delete label_ty_;
        delete int1_ty_;
        delete int32_ty_;
        delete float32_ty_;
    }
    virtual std::string print();
    void add_global_variable(GlobalVariable* g) { global_list_.push_back(g); }
    void add_function(Function* f) { function_list_.push_back(f); }
    PointerType* get_pointer_type(Type* contained); // 给定数据类型，返回对应的指针类型
    ArrayType* get_array_type(Type* contained, unsigned num_elements); // 给定数据类型和数组元素个数，返回对应的数组类型
    Function* getMainFunc(); // 获取主函数main
};

//-----------------------------------------------GlobalVariable-----------------------------------------------
//@c = global [4 * i32] [i32 6, i32 7, i32 8, i32 9]
//@a = constant [5 * i32] [i32 0, i32 1, i32 2, i32 3, i32 4]
class GlobalVariable: public Value {
public:
    bool is_const_;
    Constant* init_val_;

    GlobalVariable(std::string name, Module* m, Type* ty, bool is_const, Constant* init = nullptr)
       : Value(m->get_pointer_type(ty), name), is_const_(is_const), init_val_(init) {
        m->add_global_variable(this);
    }
    virtual std::string print() override;
};

//-----------------------------------------------Function-----------------------------------------------
class Argument: public Value {
public:
    Function* parent_;
    unsigned arg_no_; // argument No.

    //!Argument的构造函数只由Function的构造函数调用，不单独调用！！
    explicit Argument(Type* ty, const std::string& name = "", Function* f = nullptr, unsigned arg_no = 0)
       : Value(ty, name), parent_(f), arg_no_(arg_no) {}
    ~Argument() {}
    virtual std::string print() override;
};

class Function: public Value {
public:
    std::vector<BasicBlock*> basic_blocks_; // basic blocks
    std::vector<Argument*> arguments_;      // argument
    Module* parent_;
    unsigned seq_cnt_;
    std::vector<std::set<Value*>> vreg_set_;
    int use_ret_cnt; // 程序中真正使用返回值的次数

    Function(FunctionType* ty, const std::string& name, Module* parent)
       : Value(ty, name), parent_(parent), seq_cnt_(0) {
        parent->add_function(this);
        size_t num_args = ty->args_.size();
        use_ret_cnt = 0;
        for(size_t i = 0; i < num_args; i++) {
            arguments_.push_back(new Argument(ty->args_[i], "", this, i));
        }
    }
    ~Function() = default;
    virtual std::string print() override;
    void add_basic_block(BasicBlock* bb) { basic_blocks_.push_back(bb); }
    Type* get_return_type() const { return static_cast<FunctionType*>(type_)->result_; }
    bool is_declaration() { return basic_blocks_.empty(); }
    void set_instr_name();
    void remove_bb(BasicBlock* bb);
    BasicBlock* getRetBB();
};

//-----------------------------------------------BasicBlock-----------------------------------------------
// 注：BasicBlock一定是LabelTyID
class BasicBlock: public Value {
public:
    std::list<Instruction*> instr_list_;
    Function* parent_;
    // API about cfg
    std::vector<BasicBlock*> pre_bbs_;  // 前驱基本块
    std::vector<BasicBlock*> succ_bbs_; // 后继基本块
    // API about dominate tree
    std::set<BasicBlock*> dom_frontier_;
    std::set<BasicBlock*> rdom_frontier_;
    std::set<BasicBlock*> rdoms_;
    BasicBlock* idom_;
    std::set<Value*> live_in;
    std::set<Value*> live_out;
    unsigned int dom_level_; // block编号

    explicit BasicBlock(Module* m, const std::string& name, Function* parent)
       : Value(m->label_ty_, name), parent_(parent) {
        parent_->add_basic_block(this);
    }
    virtual std::string print() override;
    bool add_instruction(Instruction* instr); // 尾部插入指令，返回成功与否
    bool add_instruction_front(Instruction* instr); // 头部插入指令，返回成功与否
    bool add_instruction_before_terminator(Instruction* instr); // 插入到BB倒数第二条指令，即br前
    bool add_instruction_before_inst(Instruction* new_inst, Instruction* inst); // 将新指令插入到原来指令前，返回成功与否，需要保证原指令在bb内
    void add_pre_basic_block(BasicBlock* bb) { pre_bbs_.push_back(bb); }
    void add_succ_basic_block(BasicBlock* bb) { succ_bbs_.push_back(bb); }
    void remove_pre_basic_block(BasicBlock* bb) { pre_bbs_.erase(std::remove(pre_bbs_.begin(), pre_bbs_.end(), bb), pre_bbs_.end()); }
    void remove_succ_basic_block(BasicBlock* bb) { succ_bbs_.erase(std::remove(succ_bbs_.begin(), succ_bbs_.end(), bb), succ_bbs_.end()); }
    // 返回1表示支配bb2，返回0表示不支配，返回-1输入的块出错
    int isDominate(BasicBlock* bb2) {
        if(!bb2 || this->parent_ != bb2->parent_) {
            return -1;
        }
        while(bb2->name_ != "label_entry") {
            if(bb2->idom_ == this) {
                return 1;
            }
            bb2 = bb2->idom_;
        }
        return 0;
    }
    Instruction* get_terminator();
    bool delete_instr(Instruction* instr); // 返回false则说明指令不能重复删除或者不属于这个bb，
    bool remove_instr(Instruction* instr); // 从bb移出一个指令，但是不删指令的use关系，因为还要插入其他bb
    bool is_dominated_by(BasicBlock *B) const {
        if (this == B)
            return true;
        BasicBlock *cur = this->idom_;
        while (cur) {
            if (cur == B)
                return true;
            cur = cur->idom_;
        }
        return false;
    }
    void set_dom_level(unsigned num) { dom_level_ = num; }
    unsigned get_dom_level() const { return dom_level_; }

};

//-----------------------------------------------Instruction-----------------------------------------------
class Instruction: public Value {
public:
    enum OpID {
        // Terminator Instructions
        Ret = 11,
        Br,
        // Standard unary operators
        FNeg,
        // Standard binary operators
        Add,
        Sub,
        Mul,
        SDiv,
        SRem,
        UDiv,
        URem,
        // Float binary opeartors
        FAdd,
        FSub,
        FMul,
        FDiv,
        // Logical operators
        Shl,
        LShr,
        AShr,
        And,
        Or,
        Xor,
        // Memory operators
        Alloca,
        Load,
        Store,
        GetElementPtr,
        // Cast operators
        ZExt,
        FPtoSI,
        SItoFP,
        BitCast,
        // Other operators
        ICmp,
        FCmp,
        PHI,
        Call,
    };
    OpID op_id_;
    unsigned num_ops_;
    BasicBlock* parent_;
    std::vector<Value*> operands_; // operands of this value
    std::vector<std::list<Use>::iterator> use_pos_; // 与操作数数组一一对应，是对应的操作数的uselist里面，与当前指令相关的use的迭代器
    std::vector<std::list<Instruction*>::iterator> pos_in_bb; // 在bb的指令list的位置迭代器,最多只能有一个

    // 创建指令并插入基本块（ty是指令返回值类型）
    Instruction(Type* ty, OpID id, unsigned num_ops, BasicBlock* parent, bool before = false)
       : Value(ty, ""), op_id_(id), num_ops_(num_ops), parent_(parent) {
        operands_.resize(num_ops_, nullptr); //!此句不能删去！否则operands_为空时无法用set_operand设置操作数，而只能用push_back设置操作数！
        use_pos_.resize(num_ops_);
        if(!before) { // 默认在基本块尾部插入指令
            parent_->add_instruction(this);
        } else { // 在基本块头部插入指令
            parent_->add_instruction_front(this);
        }
    }
    // 仅创建指令，不插入基本块（ty是指令返回值类型）
    Instruction(Type* ty, OpID id, unsigned num_ops)
       : Value(ty, ""), op_id_(id), num_ops_(num_ops), parent_(nullptr) {
        operands_.resize(num_ops_, nullptr);
        use_pos_.resize(num_ops_);
    }
    virtual std::string print() = 0;
    Value* get_operand(unsigned i) const { return operands_[i]; }
    // // 修改了一下这里的set_operand 使得使用replace_all_use_with时，会同时维护use情况
    void set_operand(unsigned i, Value* v) {
        operands_[i] = v; // 设置操作数
        use_pos_[i] = v->add_use(this, i); // 添加use
        // Value* old_val = operands_[i];
        // // 从 old_val 中删除 use（O(1)）
        // if(old_val) { // 如果原来有值，则删除use
        //     old_val->remove_use(use_pos_[i]);
        // }
        // operands_[i] = v;
        // // 添加新 use，并更新 use_pos_
        // if (v) {
        //     use_pos_[i] = v->add_use(this, i);
        // }
    }
    void add_operand(Value* v) { // 添加指令操作数，用于phi指令
        operands_.push_back(v);
        use_pos_.emplace_back(v->add_use(this, num_ops_));
        num_ops_++;
    }
    //增加一个替换操作数的操作，
    void replace_operand(unsigned int i, Value* newVal) {
        // 第一步：删除newVal对应的use_list_
        Value* oldValue = this->get_operand(i);
        oldValue->remove_use(this->use_pos_[i]);
        // 第二步：替换oldValue为对应的newVal
        this->operands_[i] = newVal;
        this->use_pos_[i] = newVal->add_use(this, i);
    }
    void remove_use_of_ops() { // 删除此指令所有操作数的uselist中，与此指令相关的use
        for(int i = 0; i < operands_.size(); i++) {
            operands_[i]->remove_use(use_pos_[i]);
        }
    }
    // 删除phi指令中的一对操作数
    void remove_operands(int index1, int index2) {
        for(int i = index1; i <= index2; i++) {
            operands_[i]->remove_use(use_pos_[i]);
        }
        // 后面操作数的位置要做相应修改
        for(int i = index2 + 1; i < operands_.size(); i++) {
            for(auto& use: operands_[i]->use_list_) {
                if(use.val_ == this) {
                    use.arg_no_ -= index2 - index1 + 1;
                    break;
                }
            }
        }
        operands_.erase(operands_.begin() + index1, operands_.begin() + index2 + 1);
        use_pos_.erase(use_pos_.begin() + index1, use_pos_.begin() + index2 + 1);
        num_ops_ = operands_.size();
    }
    // 快速类型判断
    bool is_void() {
        return ((op_id_ == Ret) || (op_id_ == Br) || (op_id_ == Store) ||
                (op_id_ == Call && this->type_->tid_ == Type::VoidTyID));
    }

    bool is_phi() { return op_id_ == PHI; }
    bool is_store() { return op_id_ == Store; }
    bool is_alloca() { return op_id_ == Alloca; }
    bool is_ret() { return op_id_ == Ret; }
    bool is_load() { return op_id_ == Load; }
    bool is_br() { return op_id_ == Br; }

    bool is_add() { return op_id_ == Add; }
    bool is_sub() { return op_id_ == Sub; }
    bool is_mul() { return op_id_ == Mul; }
    bool is_div() { return op_id_ == SDiv; }
    bool is_rem() { return op_id_ == SRem; }

    bool is_fadd() { return op_id_ == FAdd; }
    bool is_fsub() { return op_id_ == FSub; }
    bool is_fmul() { return op_id_ == FMul; }
    bool is_fdiv() { return op_id_ == FDiv; }

    bool is_cmp() { return op_id_ == ICmp; }
    bool is_fcmp() { return op_id_ == FCmp; }

    bool is_call() { return op_id_ == Call; }
    bool is_gep() { return op_id_ == GetElementPtr; }
    bool is_zext() { return op_id_ == ZExt; }
    bool is_fptosi() { return op_id_ == FPtoSI; }
    bool is_sitofp() { return op_id_ == SItoFP; }

    bool is_int_binary() { return (is_add() || is_sub() || is_mul() || is_div() || is_rem()) && (num_ops_ == 2); }
    bool is_float_binary() { return (is_fadd() || is_fsub() || is_fmul() || is_fdiv()) && (num_ops_ == 2); }
    bool is_binary() { return is_int_binary() || is_float_binary(); }

    bool isTerminator() { return is_br() || is_ret(); }
};

//%77 = add i32 %74, %76
//%10 = and i1 %7, %9
//%7 = xor i1 %6, true
//%13 = fmul float %12, 0x400921FB60000000
class BinaryInst: public Instruction {
public:
    BinaryInst(Type* ty, OpID op, Value* v1, Value* v2, BasicBlock* bb)
       : Instruction(ty, op, 2, bb) {
        set_operand(0, v1);
        set_operand(1, v2);
    }
    // 只创建，不加入基本块末尾
    BinaryInst(Type* ty, OpID op, Value* v1, Value* v2, BasicBlock* bb, bool flag)
       : Instruction(ty, op, 2) {
        set_operand(0, v1);
        set_operand(1, v2);
        this->parent_ = bb;
    }
    virtual std::string print() override;
};

//%8 = zext i1 %7 to i32
//%51 = fptosi float %50 to i32
//%4 = sitofp i32 %3 to float
//%8 = fneg float %7
//%3 = bitcast [4 * [2 * i32]]* %2 to i32*
class UnaryInst: public Instruction {
public:
    UnaryInst(Type* ty, OpID op, Value* val, BasicBlock* bb)
       : Instruction(ty, op, 1, bb) {
        set_operand(0, val);
    }
    virtual std::string print() override;
};

//%18 = icmp ne i32 %12, %17
class ICmpInst: public Instruction {
public:
    enum ICmpOp {
        ICMP_EQ = 32,  // equal
        ICMP_NE = 33,  // not equal
        //! SysY2022语言应该是不支持无符号数的
        ICMP_UGT = 34, // unsigned greater than
        ICMP_UGE = 35, // unsigned greater or equal
        ICMP_ULT = 36, // unsigned less than
        ICMP_ULE = 37, // unsigned less or equal
        ICMP_SGT = 38, // signed greater than
        ICMP_SGE = 39, // signed greater or equal
        ICMP_SLT = 40, // signed less than
        ICMP_SLE = 41  // signed less or equal
    };
    ICmpOp icmp_op_;

    ICmpInst(ICmpOp op, Value* v1, Value* v2, BasicBlock* bb)
       : Instruction(bb->parent_->parent_->int1_ty_, Instruction::ICmp, 2, bb), icmp_op_(op) {
        set_operand(0, v1);
        set_operand(1, v2);
    }
    virtual std::string print() override;
};

//%5 = fcmp olt float %4, 0.000000e+00
class FCmpInst: public Instruction {
public:
    enum FCmpOp {
        //! 不知为何print_fcmp_type时，完全不考虑O的情况，只考虑了后六种U的情况
        FCMP_FALSE = 10, // Always false (always folded)
        FCMP_OEQ = 11,   // True if ordered and equal
        FCMP_OGT = 12,   // True if ordered and greater than
        FCMP_OGE = 13,   // True if ordered and greater than or equal
        FCMP_OLT = 14,   // True if ordered and less than
        FCMP_OLE = 15,   // True if ordered and less than or equal
        FCMP_ONE = 16,   // True if ordered and operands are unequal
        FCMP_ORD = 17,   // True if ordered (no nans)
        FCMP_UNO = 18,   // True if unordered: isnan(X) | isnan(Y)
        FCMP_UEQ = 19,   // True if unordered or equal
        FCMP_UGT = 20,   // True if unordered or greater than
        FCMP_UGE = 21,   // True if unordered, greater than, or equal
        FCMP_ULT = 22,   // True if unordered or less than
        FCMP_ULE = 23,   // True if unordered, less than, or equal
        FCMP_UNE = 24,   // True if unordered or not equal
        FCMP_TRUE = 25   // Always true (always folded)
    };
    FCmpOp fcmp_op_;

    FCmpInst(FCmpOp op, Value* v1, Value* v2, BasicBlock* bb)
       : Instruction(bb->parent_->parent_->int1_ty_, Instruction::FCmp, 2, bb), fcmp_op_(op) {
        set_operand(0, v1);
        set_operand(1, v2);
    }
    virtual std::string print() override;
};

//%111 = call i32 @QuickSort(i32* %108, i32 %109, i32 %110)
class CallInst: public Instruction {
public:
    CallInst(Function* func, std::vector<Value*> args, BasicBlock* bb)
       : Instruction(static_cast<FunctionType*>(func->type_)->result_, Instruction::Call, args.size() + 1, bb) {
        int num_ops = args.size() + 1;
        for(int i = 0; i < num_ops - 1; i++) {
            set_operand(i, args[i]);
        }
        set_operand(num_ops - 1, func);
    }
    virtual std::string print() override;
};

class BranchInst: public Instruction {
public:
    // br i1 %7, label %8, label %9
    BranchInst(Value* cond, BasicBlock* if_true, BasicBlock* if_false, BasicBlock* bb)
       : Instruction(if_true->parent_->parent_->void_ty_, Instruction::Br, 3, bb) {
        if_true->add_pre_basic_block(bb);
        if_false->add_pre_basic_block(bb);
        bb->add_succ_basic_block(if_false);
        bb->add_succ_basic_block(if_true);
        set_operand(0, cond);
        set_operand(1, if_true);
        set_operand(2, if_false);
    }
    // br label %31
    BranchInst(BasicBlock* if_true, BasicBlock* bb)
       : Instruction(if_true->parent_->parent_->void_ty_, Instruction::Br, 1, bb) {
        if_true->add_pre_basic_block(bb);
        bb->add_succ_basic_block(if_true);
        set_operand(0, if_true);
    }
    virtual std::string print() override;
};

// ret i32 %4
// ret void
// 注：ret的返回值类型一定是VoidTyID
class ReturnInst: public Instruction {
public:
    ReturnInst(BasicBlock* bb) // 返回void
       : Instruction(bb->parent_->parent_->void_ty_, Instruction::Ret, 0, bb) {}
    ReturnInst(Value* val, BasicBlock* bb) // 返回Value
       : Instruction(bb->parent_->parent_->void_ty_, Instruction::Ret, 1, bb) {
        set_operand(0, val);
    }
    ReturnInst(Value* val, BasicBlock* bb, bool flag) // 返回Value但不插入到基本块
       : Instruction(bb->parent_->parent_->void_ty_, Instruction::Ret, 1) {
        set_operand(0, val);
        this->parent_ = bb;
    }
    virtual std::string print() override;
};

//%1 = getelementptr [5 * [4 * i32]], [5 * [4 * i32]]* @a, i32 0, i32 2, i32 3
class GetElementPtrInst: public Instruction {
public:
bool hasBasePtr = false;
GetElementPtrInst* basePtr = nullptr;
int offset = 0;

    GetElementPtrInst(Value* ptr, std::vector<Value*> idxs, BasicBlock* bb)
       : Instruction(bb->parent_->parent_->get_pointer_type(
                            get_GEP_return_type(ptr, idxs.size())),
                        Instruction::GetElementPtr, idxs.size() + 1, bb) {
        set_operand(0, ptr);
        for(size_t i = 0; i < idxs.size(); i++) {
            set_operand(i + 1, idxs[i]);
        }
    }
    Type* get_GEP_return_type(Value* ptr, size_t idxs_size) {
        Type* ty = static_cast<PointerType*>(ptr->type_)->contained_; //[5 * [4 * i32]]
        if(ty->tid_ == Type::ArrayTyID) {
            ArrayType* arr_ty = static_cast<ArrayType*>(ty);
            for(size_t i = 1; i < idxs_size; i++) {
                ty = arr_ty->contained_; //[4 * i32], i32
                if(ty->tid_ == Type::ArrayTyID) {
                    arr_ty = static_cast<ArrayType*>(ty);
                }
            }
        }
        return ty;
    }
    virtual std::string print() override;
};

// store <ty> <value>, <ty>* <pointer>
// store i32 %57, i32* %55
// 注：store的返回值类型一定是VoidTyID
class StoreInst: public Instruction {
public:
    StoreInst(Value* val, Value* ptr, BasicBlock* bb)
       : Instruction(bb->parent_->parent_->void_ty_, Instruction::Store, 2, bb) {
        assert(val->type_ == static_cast<PointerType*>(ptr->type_)->contained_);
        set_operand(0, val);
        set_operand(1, ptr);
    }

    // 创建store指令，不插入到基本块中，但是设定parent
    StoreInst(Value* val, Value* ptr, BasicBlock* bb, bool)
       : Instruction(bb->parent_->parent_->void_ty_, Instruction::Store, 2) {
        assert(val->type_ == static_cast<PointerType*>(ptr->type_)->contained_);
        set_operand(0, val);
        set_operand(1, ptr);
        this->parent_ = bb;
    }

    virtual std::string print() override;
};

//<result> = load <ty>, <ty>* <pointer>
//%60 = load i32, i32* %59
class LoadInst: public Instruction {
public:
    LoadInst(Value* ptr, BasicBlock* bb)
       : Instruction(static_cast<PointerType*>(ptr->type_)->contained_, Instruction::Load, 1, bb) {
        set_operand(0, ptr);
    }
    virtual std::string print() override;
};

//%8 = alloca i32
class AllocaInst: public Instruction {
public:
    Type* alloca_ty_;

    AllocaInst(Type* ty, BasicBlock* bb)
       : Instruction(bb->parent_->parent_->get_pointer_type(ty),
                        Instruction::Alloca, 0, bb, true),
            alloca_ty_(ty) {}

    // 创建指令，不插入到最后，但是会设定parent
    AllocaInst(Type* ty, BasicBlock* bb, bool)
       : Instruction(bb->parent_->parent_->get_pointer_type(ty),
                        Instruction::Alloca, 0),
            alloca_ty_(ty) {
        this->parent_ = bb;
    }

    virtual std::string print() override;
};

// Zero Extension（零扩展）将一个较小位宽的整数类型扩展成更大的位宽，且高位填充为0（zero）
class ZextInst: public Instruction {
public:
    Type* dest_ty_;

    ZextInst(OpID op, Value* val, Type* ty, BasicBlock* bb)
       : Instruction(ty, op, 1, bb), dest_ty_(ty) {
        set_operand(0, val);
    }
    virtual std::string print() override;
};

class FpToSiInst: public Instruction {
public:
    Type* dest_ty_;

    FpToSiInst(OpID op, Value* val, Type* ty, BasicBlock* bb)
       : Instruction(ty, op, 1, bb), dest_ty_(ty) {
        set_operand(0, val);
    }
    virtual std::string print() override;
};

class SiToFpInst: public Instruction {
public:
    Type* dest_ty_;

    SiToFpInst(OpID op, Value* val, Type* ty, BasicBlock* bb)
       : Instruction(ty, op, 1, bb), dest_ty_(ty) {
        set_operand(0, val);
    }
    virtual std::string print() override;
};

//%3 = bitcast [4 * [2 * i32]]* %2 to i32*
class Bitcast: public Instruction {
public:
    Type* dest_ty_;
    
    Bitcast(OpID op, Value* val, Type* ty, BasicBlock* bb)
       : Instruction(ty, op, 1, bb), dest_ty_(ty) {
        set_operand(0, val);
    }
    virtual std::string print() override;
};

//%4 = phi i32 [ 1, %2 ], [ %6, %5 ]
class PhiInst: public Instruction {
public:
    Value* l_val_;

    PhiInst(OpID op, std::vector<Value*> vals, std::vector<BasicBlock*> val_bbs,
            Type* ty, BasicBlock* bb)
       : Instruction(ty, op, 2*  vals.size()) {
        for(int i = 0; i < vals.size(); i++) {
        set_operand(2*  i, vals[i]);
        set_operand(2*  i + 1, val_bbs[i]);
        }
        this->parent_ = bb;
    }
    static PhiInst* create_phi(Type* ty, BasicBlock* bb) {
        std::vector<Value*> vals;
        std::vector<BasicBlock*> val_bbs;
        return new PhiInst(Instruction::PHI, vals, val_bbs, ty, bb);
    }
    void add_phi_pair_operand(Value* val, Value* pre_bb) {
        this->add_operand(val);
        this->add_operand(pre_bb);
    }
    virtual std::string print() override;
};

//-----------------------------------------------IRStmtBuilder-----------------------------------------------
class IRStmtBuilder {
public:
    BasicBlock* BB_;
    Module* m_;

    IRStmtBuilder(BasicBlock* bb, Module* m): BB_(bb), m_(m){};
    ~IRStmtBuilder() = default;
    Module* get_module() { return m_; }
    BasicBlock* get_insert_block() { return this->BB_; }
    void set_insert_point(BasicBlock* bb) { this->BB_ = bb; }
    // 整型算术指令
    BinaryInst* create_iadd(Value* v1, Value* v2) { // 整型加法
        return new BinaryInst(this->m_->int32_ty_, Instruction::Add, v1, v2, this->BB_);
    }
    BinaryInst* create_isub(Value* v1, Value* v2) { // 整型减法
        return new BinaryInst(this->m_->int32_ty_, Instruction::Sub, v1, v2, this->BB_);
    }
    BinaryInst* create_imul(Value* v1, Value* v2) { // 整型乘法
        return new BinaryInst(this->m_->int32_ty_, Instruction::Mul, v1, v2, this->BB_);
    }
    BinaryInst* create_isdiv(Value* v1, Value* v2) { // 整型除法
        return new BinaryInst(this->m_->int32_ty_, Instruction::SDiv, v1, v2, this->BB_);
    }
    BinaryInst* create_isrem(Value* v1, Value* v2) { // 整型取模
        return new BinaryInst(this->m_->int32_ty_, Instruction::SRem, v1, v2, this->BB_);
    }
    // 整型比较指令
    ICmpInst* create_icmp_eq(Value* v1, Value* v2) { // 整型等于
        return new ICmpInst(ICmpInst::ICMP_EQ, v1, v2, this->BB_);
    }
    ICmpInst* create_icmp_ne(Value* v1, Value* v2) { // 整型不等于
        return new ICmpInst(ICmpInst::ICMP_NE, v1, v2, this->BB_);
    }
    ICmpInst* create_icmp_gt(Value* v1, Value* v2) { // 整型大于
        return new ICmpInst(ICmpInst::ICMP_SGT, v1, v2, this->BB_);
    }
    ICmpInst* create_icmp_ge(Value* v1, Value* v2) { // 整型大于等于
        return new ICmpInst(ICmpInst::ICMP_SGE, v1, v2, this->BB_);
    }
    ICmpInst* create_icmp_lt(Value* v1, Value* v2) { // 整型小于
        return new ICmpInst(ICmpInst::ICMP_SLT, v1, v2, this->BB_);
    }
    ICmpInst* create_icmp_le(Value* v1, Value* v2) { // 整型小于等于
        return new ICmpInst(ICmpInst::ICMP_SLE, v1, v2, this->BB_);
    }
    // 浮点算术指令
    BinaryInst* create_fadd(Value* v1, Value* v2) { // 浮点加法
        return new BinaryInst(this->m_->float32_ty_, Instruction::FAdd, v1, v2, this->BB_);
    }
    BinaryInst* create_fsub(Value* v1, Value* v2) { // 浮点减法
        return new BinaryInst(this->m_->float32_ty_, Instruction::FSub, v1, v2, this->BB_);
    }
    BinaryInst* create_fmul(Value* v1, Value* v2) { // 浮点乘法
        return new BinaryInst(this->m_->float32_ty_, Instruction::FMul, v1, v2, this->BB_);
    }
    BinaryInst* create_fdiv(Value* v1, Value* v2) { // 浮点除法
        return new BinaryInst(this->m_->float32_ty_, Instruction::FDiv, v1, v2, this->BB_);
    }
    // 浮点比较指令
    FCmpInst* create_fcmp_eq(Value* v1, Value* v2) { // 浮点等于
        return new FCmpInst(FCmpInst::FCMP_UEQ, v1, v2, this->BB_);
    }
    FCmpInst* create_fcmp_ne(Value* v1, Value* v2) { // 浮点不等于
        return new FCmpInst(FCmpInst::FCMP_UNE, v1, v2, this->BB_);
    }
    FCmpInst* create_fcmp_gt(Value* v1, Value* v2) { // 浮点大于
        return new FCmpInst(FCmpInst::FCMP_UGT, v1, v2, this->BB_);
    }
    FCmpInst* create_fcmp_ge(Value* v1, Value* v2) { // 浮点大于等于
        return new FCmpInst(FCmpInst::FCMP_UGE, v1, v2, this->BB_);
    }
    FCmpInst* create_fcmp_lt(Value* v1, Value* v2) { // 浮点小于
        return new FCmpInst(FCmpInst::FCMP_ULT, v1, v2, this->BB_);
    }
    FCmpInst* create_fcmp_le(Value* v1, Value* v2) { // 浮点小于等于
        return new FCmpInst(FCmpInst::FCMP_ULE, v1, v2, this->BB_);
    }
    // 函数调用指令
    CallInst* create_call(Value* func, std::vector<Value*> args) {
        return new CallInst(static_cast<Function*>(func), args, this->BB_);
    }
    // 控制流指令
    BranchInst* create_br(BasicBlock* if_true) { // 无条件跳转
        return new BranchInst(if_true, this->BB_);
    }
    BranchInst* create_cond_br(Value* cond, BasicBlock* if_true, BasicBlock* if_false) { // 有条件跳转
        return new BranchInst(cond, if_true, if_false, this->BB_);
    }
    ReturnInst* create_ret(Value* val) { return new ReturnInst(val, this->BB_); } // 返回值指令
    ReturnInst* create_void_ret() { return new ReturnInst(this->BB_); } // 返回void指令
    // 内存操作指令
    GetElementPtrInst* create_gep(Value* ptr, std::vector<Value*> idxs) { // 创建GEP指令
        return new GetElementPtrInst(ptr, idxs, this->BB_);
    }
    StoreInst* create_store(Value* val, Value* ptr) { // 创建Store指令
        return new StoreInst(val, ptr, this->BB_);
    }
    LoadInst* create_load(Type* ty, Value* ptr) { // 创建Load指令
        return new LoadInst(ptr, this->BB_);
    }
    LoadInst* create_load(Value* ptr) { // 创建Load指令，自动推断类型
        return new LoadInst(ptr, this->BB_);
    }
    AllocaInst* create_alloca(Type* ty) { return new AllocaInst(ty, this->BB_); } // 栈上分配内存
    // 类型转换指令
    ZextInst* create_zext(Value* val, Type* ty) { return new ZextInst(Instruction::ZExt, val, ty, this->BB_); }
    FpToSiInst* create_fptosi(Value* val, Type* ty) { return new FpToSiInst(Instruction::FPtoSI, val, ty, this->BB_); }
    SiToFpInst* create_sitofp(Value* val, Type* ty) { return new SiToFpInst(Instruction::SItoFP, val, ty, this->BB_); }
    // bitcast和上面两条转换指令是有去别的，bitcast只改变类型视图，而sitofp将整数转换为浮点数
    Bitcast* create_bitcast(Value* val, Type* ty) { return new Bitcast(Instruction::BitCast, val, ty, this->BB_); }
};
