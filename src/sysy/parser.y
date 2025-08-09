%define parse.error verbose
%locations

%{
    #include <cstring>
    #include <memory>
    #include <stdarg.h>

    #include "ast.h"
    #include "define.h"

    using namespace std;
    unique_ptr<CompUnitNode> root;

    extern int yylineno;
    extern int yylex();
    extern void yyerror(const char *s);
    extern void initFileName(char *name);
    char filename[100];
%}


%union {
    CompUnitNode* compUnit;
    DeclNode* decl;
    DefList* defList;
    DefNode* def;
    ArrayList* arrays;
    InitValList* initValList;
    InitValNode* initVal;
    FuncDefNode* funcDef;
    FuncFParamList* funcFParamList;
    FuncFParamNode* funcFParam;
    BlockNode* block;
    BlockItemList* blockItemList;
    BlockItemNode* blockItem;
    StmtNode* stmt;
    ReturnStmtNode* returnStmt;
    IfStmtNode* ifStmt;
    WhileStmtNode* whileStmt;
    LValNode* lVal;
    PrimaryExpNode* primaryExp;
    NumberNode* number;
    UnaryExpNode* unaryExp;
    CallNode* call;
    FuncCParamList* funcCParamList;
    MulExpNode* mulExp;
    AddExpNode* addExp;
    RelExpNode* relExp;
    EqExpNode* eqExp;
    LAndExpNode* lAndExp;
    LOrExpNode* lOrExp;

    BType ty;
    UnaryOp op;
    string* token;
    int int_val;
    float float_val;
};

%type <compUnit> CompUnit;
%type <decl> Decl;
%type <defList> DefList;
%type <def> Def;
%type <arrays> Arrays;
%type <initValList> InitValList;
%type <initVal> InitVal;
%type <funcDef> FuncDef;
%type <funcFParamList> FuncFParamList
%type <funcFParam> FuncFParam;
%type <block> Block;
%type <blockItemList> BlockItemList;
%type <blockItem> BlockItem;
%type <stmt> Stmt;
%type <returnStmt> ReturnStmt;
%type <ifStmt> IfStmt;
%type <whileStmt> WhileStmt;
%type <lVal> LVal;
%type <primaryExp> PrimaryExp;
%type <number> Number;
%type <unaryExp> UnaryExp;
%type <call> Call;
%type <funcCParamList> FuncCParamList;
%type <mulExp> MulExp;
%type <addExp> AddExp;
%type <relExp> RelExp;
%type <eqExp> EqExp;
%type <lAndExp> LAndExp;
%type <lOrExp> Cond LOrExp;

%type <ty> BType VoidType
%type <op> UnaryOp

// %token 定义终结符的语义值类型
%token <int_val> INT           // 指定INT字面量的语义值是type_int，有词法分析得到的数值
%token <float_val> FLOAT       // 指定FLOAT字面量的语义值是type_float，有词法分析得到的数值
%token <token> ID              // 指定ID
%token GTE LTE GT LT EQ NEQ    // 关系运算
%token INTTYPE FLOATTYPE VOID  // 数据类型
%token CONST RETURN IF ELSE WHILE BREAK CONTINUE
%token LP RP LB RB LC RC COMMA SEMICOLON
%token NOT ASSIGN MINUS ADD MUL DIV MOD AND OR
// Unused tokens
/* %token POS NEG */

%left ASSIGN
%left OR AND
%left EQ NEQ
%left GTE LTE GT LT
%left ADD MINUS
%left MOD MUL DIV
%right NOT
// Unused tokens
/* %right POS NEG */

%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE

%start Program

%%
Program:
    CompUnit {
        root = unique_ptr<CompUnitNode>($1);
    };

// 编译单元
CompUnit:
    CompUnit Decl {
        $$ = $1;
        $$->declList.push_back(unique_ptr<DeclNode>($2));
    }|
    CompUnit FuncDef {
        $$ = $1;
        $$->funcDefList.push_back(unique_ptr<FuncDefNode>($2));
    }|
    Decl {
        $$ = new CompUnitNode();
        $$->declList.push_back(unique_ptr<DeclNode>($1));
    }|
    FuncDef {
        $$ = new CompUnitNode(); 
        $$->funcDefList.push_back(unique_ptr<FuncDefNode>($1));
    };

// 定义列表
DefList:
    Def {
        $$ = new DefList();
        $$->list.push_back(unique_ptr<DefNode>($1));
    }|
    DefList COMMA Def {
        $$ = $1;
        $$->list.push_back(unique_ptr<DefNode>($3));
    };

// 变量或常量声明
Decl:
    CONST BType DefList SEMICOLON {
        $$ = new DeclNode();
        $$->bType = $2;
        $$->isConst = true;
        $$->defList.swap($3->list);
    }|
    BType DefList SEMICOLON {
        $$ = new DeclNode();
        $$->bType = $1;
        $$->isConst = false;
        $$->defList.swap($2->list);
    };

// 基本类型
BType:
    INTTYPE {
        $$ = BType::INT;
    }|
    FLOATTYPE {
        $$ = BType::FLOAT;
    };

// 空类型
VoidType:
    VOID {
        $$ = BType::VOID;
    };

// 定义
Def:
    ID Arrays ASSIGN InitVal {
        $$ = new DefNode();
        $$->id = unique_ptr<string>($1);
        $$->arrays.swap($2->list);
        $$->initVal = unique_ptr<InitValNode>($4);
    }|
    ID ASSIGN InitVal {
        $$ = new DefNode();
        $$->id = unique_ptr<string>($1);
        $$->initVal = unique_ptr<InitValNode>($3);
    }|
    ID Arrays {
        $$ = new DefNode();
        $$->id = unique_ptr<string>($1);
        $$->arrays.swap($2->list);
    }|
    ID {
        $$ = new DefNode();
        $$->id = unique_ptr<string>($1);
    };

// 数组
Arrays:
    LB AddExp RB {
        $$ = new ArrayList();
        $$->list.push_back(unique_ptr<AddExpNode>($2));
    }|
    Arrays LB AddExp RB {
        $$ = $1;
        $$->list.push_back(unique_ptr<AddExpNode>($3));
    };

// 变量或常量初值
InitVal:
    AddExp {
        $$ = new InitValNode();
        $$->exp = unique_ptr<AddExpNode>($1);
    }|
    LC RC {
        $$ = new InitValNode();
    }|
    LC InitValList RC {
        $$ = new InitValNode();
        $$->initValList.swap($2->list);
    };

// 变量列表
InitValList:
    InitValList COMMA InitVal {
        $$ = $1;
        $$->list.push_back(unique_ptr<InitValNode>($3));
    }|
    InitVal {
        $$ = new InitValList();
        $$->list.push_back(unique_ptr<InitValNode>($1));
    };

// 函数定义
FuncDef:
    BType ID LP FuncFParamList RP Block {
        $$ = new FuncDefNode();
        $$->returnType = $1;
        $$->id = unique_ptr<string>($2);
        $$->funcFParamList.swap($4->list);
        $$->block = unique_ptr<BlockNode>($6);
    }|
    BType ID LP RP Block {
        $$ = new FuncDefNode();
        $$->returnType = $1;
        $$->id = unique_ptr<string>($2);
        $$->block = unique_ptr<BlockNode>($5);
    }|
    VoidType ID LP FuncFParamList RP Block {
        $$ = new FuncDefNode();
        $$->returnType = $1;
        $$->id = unique_ptr<string>($2);
        $$->funcFParamList.swap($4->list);
        $$->block = unique_ptr<BlockNode>($6);
    }|
    VoidType ID LP RP Block {
        $$ = new FuncDefNode();
        $$->returnType = $1;
        $$->id = unique_ptr<string>($2);
        $$->block = unique_ptr<BlockNode>($5);
    };

// 函数形参列表
FuncFParamList:
    FuncFParam {
        $$ = new FuncFParamList();
        $$->list.push_back(unique_ptr<FuncFParamNode>($1));
    }|
    FuncFParamList COMMA FuncFParam {
        $$ = $1;
        $$->list.push_back(unique_ptr<FuncFParamNode>($3));
    };

// 函数形参
FuncFParam:
    BType ID {
        $$ = new FuncFParamNode();
        $$->bType = $1;
        $$->id = unique_ptr<string>($2);
        $$->isArray = false;
    }|
    BType ID LB RB {
        $$ = new FuncFParamNode();
        $$->bType = $1;
        $$->id = unique_ptr<string>($2);
        $$->isArray = true;
    }|
    BType ID LB RB Arrays {
        $$ = new FuncFParamNode();
        $$->bType = $1;
        $$->id = unique_ptr<string>($2);
        $$->isArray = true;
        $$->arrays.swap($5->list);
    };

// 语句块
Block:
    LC RC {
        $$ = new BlockNode();
    }|
    LC BlockItemList RC {
        $$ = new BlockNode();
        $$->blockItemList.swap($2->list);
    };

// 语句块项列表
BlockItemList:
    BlockItem {
        $$ = new BlockItemList();
        $$->list.push_back(unique_ptr<BlockItemNode>($1));
    }|
    BlockItemList BlockItem {
        $$ = $1;
        $$->list.push_back(unique_ptr<BlockItemNode>($2));
    };

// 语句块项
BlockItem:
    Decl {
        $$ = new BlockItemNode();
        $$->decl = unique_ptr<DeclNode>($1);
    }|
    Stmt {
        $$ = new BlockItemNode();
        $$->stmt = unique_ptr<StmtNode>($1);
    };

Stmt:
    SEMICOLON {
        $$ = new StmtNode();
        $$->sType = StmtType::SEMI;
    }|
    LVal ASSIGN AddExp SEMICOLON {
        $$ = new StmtNode();
        $$->sType = StmtType::ASGN;
        $$->lVal = unique_ptr<LValNode>($1);
        $$->exp = unique_ptr<AddExpNode>($3);
    }|
    AddExp SEMICOLON {
        $$ = new StmtNode();
        $$->sType = StmtType::EXP;
        $$->exp = unique_ptr<AddExpNode>($1);
    }|
    CONTINUE SEMICOLON {
        $$ = new StmtNode();
        $$->sType = StmtType::CONTINUE;
    }|
    BREAK SEMICOLON {
        $$ = new StmtNode();
        $$->sType = StmtType::BREAK;
    }|
    Block {
        $$ = new StmtNode();
        $$->sType = StmtType::BLK;
        $$->block = unique_ptr<BlockNode>($1);
    }|
    ReturnStmt {
        $$ = new StmtNode();
        $$->sType = StmtType::RET;
        $$->returnStmt = unique_ptr<ReturnStmtNode>($1);
    }|
    IfStmt {
        $$ = new StmtNode();
        $$->sType = StmtType::IF;
        $$->ifStmt = unique_ptr<IfStmtNode>($1);
    }|
    WhileStmt {
        $$ = new StmtNode();
        $$->sType = StmtType::WHILE;
        $$->whileStmtAST = unique_ptr<WhileStmtNode>($1);
    };

//选择语句
IfStmt:
    IF LP Cond RP Stmt %prec LOWER_THEN_ELSE {
        $$ = new IfStmtNode();
        $$->cond = unique_ptr<LOrExpNode>($3);
        $$->ifStmt = unique_ptr<StmtNode>($5);
    }|
    IF LP Cond RP Stmt ELSE Stmt {
        $$ = new IfStmtNode();
        $$->cond = unique_ptr<LOrExpNode>($3);
        $$->ifStmt = unique_ptr<StmtNode>($5);
        $$->elseStmt = unique_ptr<StmtNode>($7);
    };

//循环语句
WhileStmt:
    WHILE LP Cond RP Stmt {
        $$ = new WhileStmtNode();
        $$->cond = unique_ptr<LOrExpNode>($3);
        $$->stmt = unique_ptr<StmtNode>($5);
    };

//返回语句
ReturnStmt:
    RETURN AddExp SEMICOLON {
        $$ = new ReturnStmtNode();
        $$->exp = unique_ptr<AddExpNode>($2);
    }|
    RETURN SEMICOLON {
        $$ = new ReturnStmtNode();
    };

// 条件表达式
Cond:
    LOrExp {
        $$ = $1;
    };

// 左值表达式
LVal:
    ID {
        $$ = new LValNode();
        $$->id = unique_ptr<string>($1);
    }|
    ID Arrays {
        $$ = new LValNode();
        $$->id = unique_ptr<string>($1);
        $$->arrays.swap($2->list);
    };

// 基本表达式
PrimaryExp:
    LP AddExp RP {
        $$ = new PrimaryExpNode();
        $$->exp = unique_ptr<AddExpNode>($2);
    }|
    LVal {
        $$ = new PrimaryExpNode();
        $$->lval = unique_ptr<LValNode>($1);
    }|
    Number {
        $$ = new PrimaryExpNode();
        $$->number = unique_ptr<NumberNode>($1);
    };

// 数值
Number:
    INT {
        $$ = new NumberNode();
        $$->isInt = true;
        $$->intval = $1;
    }|
    FLOAT {
        $$ = new NumberNode();
        $$->isInt = false;
        $$->floatval = $1;
    };

// 一元表达式
UnaryExp:
    PrimaryExp {
        $$ = new UnaryExpNode();
        $$->primaryExp = unique_ptr<PrimaryExpNode>($1);
    }|
    Call {
        $$ = new UnaryExpNode();
        $$->call = unique_ptr<CallNode>($1);
    }|
    UnaryOp UnaryExp {
        $$ = new UnaryExpNode();
        $$->op = $1;
        $$->unaryExp = unique_ptr<UnaryExpNode>($2);
    };

//函数调用
Call:
    ID LP RP {
        $$ = new CallNode();
        $$->id = unique_ptr<string>($1);
    }|
    ID LP FuncCParamList RP {
        $$ = new CallNode();
        $$->id = unique_ptr<string>($1);
        $$->funcCParamList.swap($3->list);
    };

// 单目运算符,这里可能与优先级相关，不删除该非终结符
UnaryOp:
    ADD {
        $$ = UnaryOp::ADD;
    }|
    MINUS {
        $$ = UnaryOp::MINUS;
    }|
    NOT {
        $$ = UnaryOp::NOT;
    };

// 函数实参表
FuncCParamList:
    AddExp {
        $$ = new FuncCParamList();
        $$->list.push_back(unique_ptr<AddExpNode>($1));
    }|
    FuncCParamList COMMA AddExp {
        $$ = (FuncCParamList*) $1;
        $$->list.push_back(unique_ptr<AddExpNode>($3));
    };

//乘除模表达式
MulExp:
    UnaryExp {
        $$ = new MulExpNode();
        $$->unaryExp = unique_ptr<UnaryExpNode>($1);
    }|
    MulExp MUL UnaryExp {
        $$ = new MulExpNode();
        $$->mulExp = unique_ptr<MulExpNode>($1);
        $$->op = MulOp::MUL;
        $$->unaryExp = unique_ptr<UnaryExpNode>($3);
    }|
    MulExp DIV UnaryExp {
        $$ = new MulExpNode();
        $$->mulExp = unique_ptr<MulExpNode>($1);
        $$->op = MulOp::DIV;
        $$->unaryExp = unique_ptr<UnaryExpNode>($3);
    }|
    MulExp MOD UnaryExp {
        $$ = new MulExpNode();
        $$->mulExp = unique_ptr<MulExpNode>($1);
        $$->op = MulOp::MOD;
        $$->unaryExp = unique_ptr<UnaryExpNode>($3);
    };

// 加减表达式
AddExp:
    MulExp {
        $$ = new AddExpNode();
        $$->mulExp = unique_ptr<MulExpNode>($1);
    }|
    AddExp ADD MulExp {
        $$ = new AddExpNode();
        $$->addExp = unique_ptr<AddExpNode>($1);
        $$->op = AddOp::ADD;
        $$->mulExp = unique_ptr<MulExpNode>($3);
    }|
    AddExp MINUS MulExp {
        $$ = new AddExpNode();
        $$->addExp = unique_ptr<AddExpNode>($1);
        $$->op = AddOp::MINUS;
        $$->mulExp = unique_ptr<MulExpNode>($3);
    };

// 关系表达式
RelExp:
    AddExp {
        $$ = new RelExpNode();
        $$->addExp = unique_ptr<AddExpNode>($1);
    }|
    RelExp GTE AddExp {
        $$ = new RelExpNode();
        $$->relExp = unique_ptr<RelExpNode>($1);
        $$->op = RelOp::GTE;
        $$->addExp = unique_ptr<AddExpNode>($3);
    }|
    RelExp LTE AddExp {
        $$ = new RelExpNode();
        $$->relExp = unique_ptr<RelExpNode>($1);
        $$->op = RelOp::LTE;
        $$->addExp = unique_ptr<AddExpNode>($3);
    }|
    RelExp GT AddExp {
        $$ = new RelExpNode();
        $$->relExp = unique_ptr<RelExpNode>($1);
        $$->op = RelOp::GT;
        $$->addExp = unique_ptr<AddExpNode>($3);
    }|
    RelExp LT AddExp {
        $$ = new RelExpNode();
        $$->relExp = unique_ptr<RelExpNode>($1);
        $$->op = RelOp::LT;
        $$->addExp = unique_ptr<AddExpNode>($3);
    };

// 相等性表达式
EqExp:
    RelExp {
        $$ = new EqExpNode();
        $$->relExp = unique_ptr<RelExpNode>($1);
    }|
    EqExp EQ RelExp {
        $$ = new EqExpNode();
        $$->eqExp = unique_ptr<EqExpNode>($1);
        $$->op = EqOp::EQ;
        $$->relExp = unique_ptr<RelExpNode>($3);
    }|
    EqExp NEQ RelExp {
        $$ = new EqExpNode();
        $$->eqExp = unique_ptr<EqExpNode>($1);
        $$->op = EqOp::NEQ;
        $$->relExp = unique_ptr<RelExpNode>($3);
    };

// 逻辑与表达式
LAndExp:
    EqExp {
        $$ = new LAndExpNode();
        $$->eqExp = unique_ptr<EqExpNode>($1);
    }|
    LAndExp AND EqExp {
        $$ = new LAndExpNode();
        $$->lAndExp = unique_ptr<LAndExpNode>($1);
        $$->eqExp = unique_ptr<EqExpNode>($3);
    };

// 逻辑或表达式
LOrExp:
    LAndExp {
        $$ = new LOrExpNode();
        $$->lAndExp = unique_ptr<LAndExpNode>($1);
    }|
    LOrExp OR LAndExp {
        $$ = new LOrExpNode();
        $$->lOrExp = unique_ptr<LOrExpNode>($1);
        $$->lAndExp = unique_ptr<LAndExpNode>($3);
    };
%%

void initFileName(char *name) {
    strcpy(filename, name);
}

void yyerror(const char* fmt) {
    printf("%s:%d ", filename, yylloc.first_line);
    printf("%s\n", fmt);
}
