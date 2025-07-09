## ir

### Description

中端：中间代码生成，基于LLVM IR构造

### 文件内容说明

#### ir.h

---

##### Use
引用的变量的值以及该变量在引用处的操作数序号

---

##### Type
+ TypeID tid_：类型种类ID（void, label, integer, float, function, array, pointer）
+ string print()：根据tid_进行类型的打印

继承类
1. IntergerType
+ unsigned int num_bits_：位数，1或32
1. ArrayType
+ Type* contained_：数组中的数据类型
+ unsigned int num_elements_：数组长度
1. PointerType
+ Type* contained_：指针指向的数据类型
1. FunctionType
+ Type* result_：函数返回值的类型
+ vector\<Type*\> args_：函数形参的类型
+ PS：构造函数针对args_的构造为深拷贝方式

---

##### Value
+ Type* type_：数据指的类型
+ string name_：数据名（变量名）
+ list\<Use\> use_list_：所有引用该数据值的指令的集合，以及该数据值在该指令的操作数的位序
+ string print()：基类方法，为0
+ bool is_constant()：判断是否为常量
+ list\<Use\>::iterator add_use(Value*, unsigned)：插入数据值的引用到use_list_并返回指向刚插入的元素的迭代器
+ void remove_use(list\<Use>::iterator)：删除迭代器指向的元素
+ void remove_use(Value*)：删除所有与给定Value相关的Use
+ void replace_all_use_with(Value*)：将所有引用当前Value的Instruction中的Value都替换为给定的Value
+ bool remove_used(Instruction*, unsigned int)：删除给定指令对当前Value的引用，即删除当前Value中的给定Instruction，并删除给定Instruction当前Value所在位置的操作数

继承类
1. Constant
+ 常量无名：name_ == ""
   1. ConstantInt
     + int value_：整型常量的数值 
     + string print()：得到整型常量的具体数值字符串
   2. ConstantFloat
     + float value_：浮点型常量的数值
     + string print()：得到浮点型常量的具体字符串
   3. ConstantArray
     + vecctor<Constant*\> const_array：包含多个常量类型的一个数组
     + string print()：得到代表数组的字符串两端为'['和']'，元素之间用", "隔开
   4. ConstantZero
     + string print()：返回zeroinitializer
1. GlobalVariable
   + bool is_const_：该全局量是否为常量
   + Constant* init_val_：全局量的初始化必须为常量
   + string print()：@<name\> = constant/global <type\> <init_val\>
2. Argument
   + Function* parent：属于哪个函数
   + unsigned int arg_no_：函数的第几个参数
   + string print()：类型名+%参数名(编译器中的名字arg_0、arg_1)
3. Function
   + vector<BasicBlock*\> basic_blocks_：函数的基本块
   + vector<Argument*> arguments_：函数的实参列表
   + Module* parent：函数所属的模块
   + unsigned int seq_cnt：标号计数，函数域内共享
   + vector<set\<Value*>> vreg_set_：
   + int use_ret_cnt：程序中真正使用返回值的次数
   + string print()：得到函数的所有内容
   + void add_basic_block(BasicBlock*)：插入基本块
   + Type* get_return_type()：获取函数返回值类型
   + bool is_declaration()：声明or定义
   + void set_instr_name()：针对函数的实参、基本块以及每一条指令进行不重复标号，共享标号空间，从0开始
   + void remove_bb(BasicBlock*)：删除基本块，以及其和其他基本块之间的连接
   + BasicBlock* getRetBB()：获取第一个强制跳转(ret, br)的基本块
4. BasicBlock
   + list<Instruction*\> instr_list_：指令流，指令序列
   + Function* parent_：基本块所属函数
   + vector<BasicBlock*> pre_bbs_：前驱基本块
   + vector<BasicBlock*> succ_bbs_：后继基本块
   + set<BasicBlock*> dom_frontier_：
   + set<BasicBlock*> rdom_frontier_：
   + set<BasicBlock*> rdoms_：
   + BasicBlock* idom_：必经结点集中的前驱结点
   + set<Value*> live_in：
   + set<Value*> live_out：
   + 构造函数：默认将基本块加入给定Function
   + string print()：得到基本块的所有内容
   + bool add_instruction(Instruction* instr)：插入指令到基本块的末尾
   + bool add_instruction_front(Instruction* instr)：插入指令到基本块的头部
   + bool add_instruction_before_terminator(Instruction* instr)：插入指令到基本块的倒数第二位
   + bool add_instruction_before_inst(Instruction* new_inst, Instruction* inst)：插入指令到给定指令的前方
   + void add_pre_basic_block(BasicBlock* bb)：将给定基本块加入到前驱基本块
   + void add_succ_basic_block(BasicBlock* bb)：将给定基本块加入到后继基本块
   + void remove_pre_basic_block(BasicBlock* bb)：删除前驱基本块中的给定基本块
   + void remove_succ_basic_block(BasicBlock* bb)：删除后继基本块中的给定基本块
   + int isDominate(BasicBlock* bb2)：查看当前基本块是否支配给定基本块
   + Instruction* get_terminator()：如果该基本块的最后一条指令是返回指令或者无条件跳转指令，则返回该指令，否则返回空指针
   + bool delete_instr(Instruction* instr)：TODO 返回false则说明指令不能重复删除或者不属于这个bb
   + bool remove_instr(Instruction* instr)：TODO 从bb移出一个指令，但是不删指令的use关系，因为还要插入其他bb
5. Instruction
   + OpID op_id_：指令类型
   + unsigned int num_ops_：指令数
   + BasicBlock* parent_：指令所属基本块
   + vector<Value*> operands_：指令的操作数
   + vector<list<Use\>::iterator> use_pos_：对应的操作数的use_list_中该操作数的位置
   + vector<list<Instruction*>::iterator> pos_in_bb：在基本块的指令序列中的位置
   + 构造函数1：创建指令并加入基本块
   + 构造函数2：仅创建指令
   + string print()：用于继承，具体内容详见每个子类的定义，下面不作介绍
   + Value* get_operand(unsigned int)：获取给定位置的指令
   + void set_operand(unsigned int, Value*)：将给定位置的操作数设置为给定值，同时在给定值的引用中加入该指令
   + void add_operand(Value*)：添加指令的操作数，用于phi指令
   + void remove_use_of_ops()：删除当前指令的操作数中与当前指令相关的引用
   + void remove_operands(int index1, int index2)：暂时未用到，个人认为具体实现上不知所云
   + 快速类型判断
   1. BinaryInst
      + 二元操作符语句
      + 两种构造函数，第一种插入基本块末尾，第二种不插入，通过Instruction的构造函数实现，同时设置操作数的信息
   2. UnaryInst：一元操作符语句
   3. ICmpInst：整型比较语句
   4. FCmpInst：浮点型比较语句
   5. CallInst：调用语句
   6. BranchInst：分支语句
   7. ReturnInst：返回语句
   8. GetElementPtrInst
   9. StoreInst
   10. LoadInst
   11. AllocaInst
   12. ZextInst
   13. FpToSiInst
   14. SiToFpInst
   15. Bitcast
   16. PhiInst

---

+ 模块：Module
  + vector<GlobalVariable*> global_list_：全局量列表
  + vector<Function*> function_list_：函数列表
  + IntegerType* int1_ty_：1位整型
  + IntegerType* int32_ty_：32位整型
  + Type* float32_ty_：32位浮点型
  + Type* label_ty_：标号型
  + Type* void_ty_：空型
  + map<Type*, PointerType*> pointer_map_：实现从数据类型到数据指针类型的映射
  + map<pair<Type*, int>, ArrayType*> array_map_：实现从{数据类型，数据个数}到数组类型的映射

---

+ 中间代码构造器：IRStmtBuilder
详情见代码

---

#### ir.cpp

用于生成`*.ll`文件的内容

+ string print_as_op(Value* v, bool print_ty)
全局量、函数得到@<name\>，常量直接得到其print的结果，其余情况得到%<name\>，如果print_ty为真，则在其开头加上类型打印结果
+ string print_cmp_type(ICmpInst::ICmpOp op)
整型比较符的选择
+ string print_fcmp_type(FCmpInst::FCmpOp op)
浮点型比较符的选择

#### genIR.h



#### genIR.cpp

