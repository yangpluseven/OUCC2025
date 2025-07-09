## parser

### Description

编译器前端部分，词法分析器+语法分析器，借助Flex+Bison实现，定义抽象语法树各类结点。

+ define.h：用于语法分析、语义分析的各种操作和类型
+ tokens.l/parser.y：Flex+Bison规则文件
+ tokens.cpp/tokens.hpp：词法分析器源码，Flex构建（`flex tokens.l -o tokens.cpp --header-file=tokens.hpp`）
+ parser.cpp/parser.hpp：语法分析器源码，Bison构建（`bison parser.y -o parser.cpp -d`）
+ ast.h/ast.cpp：抽象语法树结点相关定义，采用访问者模式（Visitor Pattern），具体的visit方法在中间代码部分定义，见`genIR.cpp`