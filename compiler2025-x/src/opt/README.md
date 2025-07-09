## opt

### Description

中间代码优化部分

+ opt
包含优化基类(Optimization)

+ LT_tree
生成支配树

+ mem2reg
将通过`alloca`分配在栈上的局部变量从内存提升到寄存器，从而构建出**SSA**形式的中间代码

### TODO

#### 优化顺序建议 from DeepSeek

1. **预处理阶段**：
   - Mem2Reg（内存到寄存器转换）
   - 简化CFG（控制流图简化）

2. **局部优化**：
   - 常量传播
   - 死代码删除
   - 公共子表达式消除
   - 指令组合

3. **循环优化**：
   - 循环不变代码外提
   - 归纳变量优化
   - 循环展开（可选）

4. **全局优化**：
   - 全局值编号
   - 函数内联

5. **后处理阶段**：
   - 死代码删除（再次）
   - 寄存器分配（如果目标为汇编）

#### 🔁 常见多遍 Pass 顺序（参考 LLVM）from ChatGPT

1. **SSA 构造（mem2reg / SROA）**
   将所有oca指令提升为 SSA 寄存器，为后续优化建立基础 ([willghatch.net][2])。

2. **常量传播（Constant Propagation、SCCP）**
   计算并替换常量表达式，简化控制流（如 unnreachable 分支）。

3. **公共子表达式消除（GVN / CSE / Value Numbering）**
   用哈希等技术识别重复计算，只保留一次 ([en.wikipedia.org][3], [medium.com][4])。

4. **死代码删除（Dead Code Elimination）**
   移除未被使用且无副作用的指令。

5. **循环优化（Loop-Invariant Code Motion, Loop Unroll 等）**
   将不变表达式移动到循环外，展开小循环，加速执行 ([en.wikipedia.org][3], [courses.cs.washington.edu][5])。

6. **控制流图简化（CFG Simplify）**
   合并基本块、移除空分支、修剪 phi 节点，统一整洁 CFG。

7. **SSA 破坏 / Phi 消除（Phi Elimination）**
   在进入后端前将 phi 节点替换为具体的 copy/move 指令。

8. **后端准备优化（CodeGenPrepare 等）**
   特化指令选择前的其他调整，如 lower switch、memcpy 展开等。