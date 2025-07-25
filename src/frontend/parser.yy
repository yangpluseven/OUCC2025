%language "c++"
%define api.parser.class { Parser }
%define api.namespace { Compiler }
%define api.value.type variant
%define parse.error verbose
%defines "generated/parser.tab.hpp"
%locations

%code requires {
    #include <string>
    #include <vector>
    #include <memory>

    #include "ast.hpp"
    #include "define.hpp"

    namespace Compiler {
        class Lexer;
    }
}

%param { Compiler::Lexer& lexer }
%param { std::unique_ptr<CompUnit>& root }

%type <std::unique_ptr<CompUnit>> CompUnit
%type <std::unique_ptr<DeclDef>> DeclDef
%type <std::unique_ptr<Decl>> Decl
%type <std::unique_ptr<DefList>> DefList
%type <std::unique_ptr<Def>> Def
%type <std::unique_ptr<ArrayList>> Arrays
%type <std::unique_ptr<InitValList>> InitValList
%type <std::unique_ptr<InitVal>> InitVal
%type <std::unique_ptr<FuncDef>> FuncDef
%type <std::unique_ptr<FuncFParamList>> FuncFParamList
%type <std::unique_ptr<FuncFParam>> FuncFParam
%type <std::unique_ptr<Block>> Block
%type <std::unique_ptr<BlockItemList>> BlockItemList
%type <std::unique_ptr<BlockItem>> BlockItem
%type <std::unique_ptr<Stmt>> Stmt
%type <std::unique_ptr<ReturnStmt>> ReturnStmt
%type <std::unique_ptr<IfStmt>> IfStmt
%type <std::unique_ptr<WhileStmt>> WhileStmt
%type <std::unique_ptr<LVal>> LVal
%type <std::unique_ptr<PrimaryExp>> PrimaryExp
%type <std::unique_ptr<NumberNode>> Number
%type <std::unique_ptr<UnaryExp>> UnaryExp
%type <std::unique_ptr<Call>> Call
%type <std::unique_ptr<FuncCParamList>> FuncCParamList
%type <std::unique_ptr<MulExp>> MulExp
%type <std::unique_ptr<AddExp>> Exp AddExp
%type <std::unique_ptr<RelExp>> RelExp
%type <std::unique_ptr<EqExp>> EqExp
%type <std::unique_ptr<LAndExp>> LAndExp
%type <std::unique_ptr<LOrExp>> Cond LOrExp

%type <Type> BType VoidType
%type <UnaryOp> UnaryOp

%token <int> INT
%token <float> FLOAT
%token <std::string> ID

%token T_INT T_FLOAT T_VOID
%token T_CONST
%token T_RETURN
%token T_IF T_ELSE
%token T_WHILE T_BREAK T_CONTINUE T_LOWER_THEN_ELSE

%token T_GE T_LE T_EQ T_NEQ T_AND T_OR

%right '='
%left T_OR T_AND
%left T_EQ T_NEQ
%left '<' '>' T_LE T_GE
%left '+' '-' '*' '/' '%'
%right '!'

%nonassoc LOWER_THEN_ELSE
%nonassoc ELSE

%start Program

%%

Program:
    CompUnit {
        root = std::move($1);
    };

CompUnit:
    CompUnit DeclDef {
        $1->declDefList.push_back(std::move($2));
        $$ = std::move($1);
    }
|   DeclDef {
        $$ = std::make_unique<CompUnit>();
        $$->declDefList.push_back(std::move($1));
    };

DeclDef:
    Decl {
        $$ = std::make_unique<DeclDef>();
        $$->decl = std::move($1);
    }
|   FuncDef {
        $$ = std::make_unique<DeclDef>();
        $$->funcDef = std::move($1);
    };

Decl:
    T_CONST BType DefList ';' {
        $$ = std::make_unique<Decl>();
        $$->isConst = true;
        $$->bType = $2;
        $$->defList.swap($3->list);
    }
|   BType DefList ';' {
        $$ = std::make_unique<Decl>();
        $$->isConst = false;
        $$->bType = $1;
        $$->defList.swap($2->list);
    };

BType:
    T_INT {
        $$ = Type::INT;
    }
|   T_FLOAT {
        $$ = Type::FLOAT;
    };

VoidType:
    T_VOID {
        $$ = Type::VOID;
    };

DefList:
    Def {
        $$ = std::make_unique<DefList>();
        $$->list.push_back(std::move($1));
    }
|   DefList ',' Def {
        $1->list.push_back(std::move($3));
        $$ = std::move($1);
    };

Def:
    ID Arrays '=' InitVal {
        $$ = std::make_unique<Def>();
        $$->id = std::make_unique<std::string>(std::move($1));
        $$->arrays = std::move($2->list);
    }
|   ID '=' InitVal {
        $$ = std::make_unique<Def>();
        $$->id = std::make_unique<std::string>(std::move($1));
        $$->initVal = std::move($3);
    }
|   ID Arrays {
        $$ = std::make_unique<Def>();
        $$->id = std::make_unique<std::string>(std::move($1));
        $$->arrays = std::move($2->list);
    }
|   ID {
        $$ = std::make_unique<Def>();
        $$->id = std::make_unique<std::string>(std::move($1));
    };

Arrays:
    '[' Exp ']' {
        $$ = std::make_unique<ArrayList>();
        $$->list.push_back(std::move($2));
    }
|   Arrays '[' Exp ']' {
        $1->list.push_back(std::move($3));
        $$ = std::move($1);
    };

InitVal:
    Exp {
        $$ = std::make_unique<InitVal>();
        $$->exp = std::move($1);
    }
|   '{' '}' {
        $$ = std::make_unique<InitVal>();
    }
|   '{' InitValList '}' {
        $$ = std::make_unique<InitVal>();
        $$->initValList.swap($2->list);
    };

InitValList:
    InitValList ',' InitVal {
        $1->list.push_back(std::move($3));
        $$ = std::move($1);
    }
|   InitVal {
        $$ = std::make_unique<InitValList>();
        $$->list.push_back(std::move($1));
    };

FuncDef:
    BType ID '(' FuncFParamList ')' Block {
        $$ = std::make_unique<FuncDef>();
        $$->returnType = $1;
        $$->id = std::make_unique<std::string>(std::move($2));
        $$->funcFParamList.swap($4->list);
        $$->block = std::move($6);
    }
|   BType ID '(' ')' Block {
        $$ = std::make_unique<FuncDef>();
        $$->returnType = $1;
        $$->id = std::make_unique<std::string>(std::move($2));
        $$->block = std::move($5);
    }
|   VoidType ID '(' FuncFParamList ')' Block {
        $$ = std::make_unique<FuncDef>();
        $$->returnType = $1;
        $$->id = std::make_unique<std::string>(std::move($2));
        $$->funcFParamList.swap($4->list);
        $$->block = std::move($6);
    }
|   VoidType ID '(' ')' Block {
        $$ = std::make_unique<FuncDef>();
        $$->returnType = $1;
        $$->id = std::make_unique<std::string>(std::move($2));
        $$->block = std::move($5);
    };

FuncFParamList:
    FuncFParam {
        $$ = std::make_unique<FuncFParamList>();
        $$->list.push_back(std::move($1));
    }
|   FuncFParamList ',' FuncFParam {
        $1->list.push_back(std::move($3));
        $$ = std::move($1);
    };

FuncFParam:
    BType ID {
        $$ = std::make_unique<FuncFParam>();
        $$->bType = $1;
        $$->id = std::make_unique<std::string>(std::move($2));
        $$->isArray = false;
    }
|   BType ID '[' ']' {
        $$ = std::make_unique<FuncFParam>();
        $$->bType = $1;
        $$->id = std::make_unique<std::string>(std::move($2));
        $$->isArray = true;
    }
|   BType ID '[' ']' Arrays {
        $$ = std::make_unique<FuncFParam>();
        $$->bType = $1;
        $$->id = std::make_unique<std::string>(std::move($2));
        $$->isArray = true;
        $$->arrays.swap($5->list);
    };

Block:
    '{' '}' {
        $$ = std::make_unique<Block>();
    }
|   '{' BlockItemList '}' {
        $$ = std::make_unique<Block>();
        $$->blockItemList.swap($2->list);
    };

BlockItemList:
    BlockItem {
        $$ = std::make_unique<BlockItemList>();
        $$->list.push_back(std::move($1));
    }
|   BlockItemList BlockItem {
        $1->list.push_back(std::move($2));
        $$ = std::move($1);
    };

BlockItem:
    Decl {
        $$ = std::make_unique<BlockItem>();
        $$->decl = std::move($1);
    }
|   Stmt {
        $$ = std::make_unique<BlockItem>();
        $$->stmt = std::move($1);
    };

Stmt:
    ';' {
        $$ = std::make_unique<Stmt>();
        $$->sType = StmtType::SEMI;
    }
|   LVal '=' Exp ';' {
        $$ = std::make_unique<Stmt>();
        $$->sType = StmtType::ASGN;
        $$->lVal = std::move($1);
        $$->exp = std::move($3);
    }
|   Exp ';' {
        $$ = std::make_unique<Stmt>();
        $$->sType = StmtType::EXP;
        $$->exp = std::move($1);
    }
|   T_CONTINUE ';' {
        $$ = std::make_unique<Stmt>();
        $$->sType = StmtType::CONTINUE;
    }
|   T_BREAK ';' {
        $$ = std::make_unique<Stmt>();
        $$->sType = StmtType::BREAK;
    }
|   Block {
        $$ = std::make_unique<Stmt>();
        $$->sType = StmtType::BLK;
        $$->block = std::move($1);
    }
|   ReturnStmt {
        $$ = std::make_unique<Stmt>();
        $$->sType = StmtType::RET;
        $$->returnStmt = std::move($1);
    }
|   IfStmt {
        $$ = std::make_unique<Stmt>();
        $$->sType = StmtType::IF;
        $$->ifStmt = std::move($1);
    }
|   WhileStmt {
        $$ = std::make_unique<Stmt>();
        $$->sType = StmtType::WHILE;
        $$->whileStmt = std::move($1);
    };

IfStmt:
    T_IF '(' Cond ')' Stmt %prec T_LOWER_THEN_ELSE {
        $$ = std::make_unique<IfStmt>();
        $$->cond = std::move($3);
        $$->ifStmt = std::move($5);
    }
|   T_IF '(' Cond ')' Stmt T_ELSE Stmt {
        $$ = std::make_unique<IfStmt>();
        $$->cond = std::move($3);
        $$->ifStmt = std::move($5);
        $$->elseStmt = std::move($7);
    };

WhileStmt:
    T_WHILE '(' Cond ')' Stmt {
        $$ = std::make_unique<WhileStmt>();
        $$->cond = std::move($3);
        $$->stmt = std::move($5);
    };

ReturnStmt:
    T_RETURN Exp ';' {
        $$ = std::make_unique<ReturnStmt>();
        $$->exp = std::move($2);
    }
|   T_RETURN ';' {
        $$ = std::make_unique<ReturnStmt>();
    };

Exp:
    AddExp {
        $$ = std::move($1);
    };

Cond:
    LOrExp {
        $$ = std::move($1);
    };

LVal:
    ID {
        $$ = std::make_unique<LVal>();
        $$->id = std::make_unique<std::string>(std::move($1));
    }
|   ID Arrays {
        $$ = std::make_unique<LVal>();
        $$->id = std::make_unique<std::string>(std::move($1));
        $$->arrays.swap($2->list);
    };

PrimaryExp:
    '(' Exp ')' {
        $$ = std::make_unique<PrimaryExp>();
        $$->exp = std::move($2);
    }
|   LVal {
        $$ = std::make_unique<PrimaryExp>();
        $$->lVal = std::move($1);
    }
|   Number {
        $$ = std::make_unique<PrimaryExp>();
        $$->number = std::move($1);
    };

Number:
    INT {
        $$ = std::make_unique<NumberNode>();
        $$->bType = Type::INT;
        $$->intValue = $1;
    }
|   FLOAT {
        $$ = std::make_unique<NumberNode>();
        $$->bType = Type::FLOAT;
        $$->floatValue = $1;
    };

UnaryExp:
    PrimaryExp {
        $$ = std::make_unique<UnaryExp>();
        $$->primaryExp = std::move($1);
    }
|   Call {
        $$ = std::make_unique<UnaryExp>();
        $$->call = std::move($1);
    }
|   UnaryOp UnaryExp {
        $$ = std::make_unique<UnaryExp>();
        $$->opExp.op = $1;
        $$->opExp.unaryExp = std::move($2);
    };

Call:
    ID '(' ')' {
        $$ = std::make_unique<Call>();
        $$->id = std::make_unique<std::string>(std::move($1));
    }
|   ID '(' FuncCParamList ')' {
        $$ = std::make_unique<Call>();
        $$->id = std::make_unique<std::string>(std::move($1));
        $$->funcCParamList.swap($3->list);
    };

UnaryOp:
    '+' {
        $$ = UnaryOp::ADD;
    }
|   '-' {
        $$ = UnaryOp::MINUS;
    }
|   '!' {
        $$ = UnaryOp::NOT;
    };

FuncCParamList:
    Exp {
        $$ = std::make_unique<FuncCParamList>();
        $$->list.push_back(std::move($1));
    }
|   FuncCParamList ',' Exp {
        $1->list.push_back(std::move($3));
        $$ = std::move($1);
    };

MulExp:
    UnaryExp {
        $$ = std::make_unique<MulExp>();
        $$->unaryExp = std::move($1);
    }
|   MulExp '*' UnaryExp {
        $$ = std::make_unique<MulExp>();
        $$->mulExp = std::move($1);
        $$->op = MulOp::MUL;
        $$->unaryExp = std::move($3);
    }
|   MulExp '/' UnaryExp {
        $$ = std::make_unique<MulExp>();
        $$->mulExp = std::move($1);
        $$->op = MulOp::DIV;
        $$->unaryExp = std::move($3);
    }
|   MulExp '%' UnaryExp {
        $$ = std::make_unique<MulExp>();
        $$->mulExp = std::move($1);
        $$->op = MulOp::MOD;
        $$->unaryExp = std::move($3);
    };

AddExp:
    MulExp {
        $$ = std::make_unique<AddExp>();
        $$->mulExp = std::move($1);
    }
|   AddExp '+' MulExp {
        $$ = std::make_unique<AddExp>();
        $$->addExp = std::move($1);
        $$->op = AddOp::ADD;
        $$->mulExp = std::move($3);
    }
|   AddExp '-' MulExp {
        $$ = std::make_unique<AddExp>();
        $$->addExp = std::move($1);
        $$->op = AddOp::MINUS;
        $$->mulExp = std::move($3);
    };

RelExp:
    AddExp {
        $$ = std::make_unique<RelExp>();
        $$->addExp = std::move($1);
    }
|   RelExp '<' AddExp {
        $$ = std::make_unique<RelExp>();
        $$->relExp = std::move($1);
        $$->op = RelOp::LT;
        $$->addExp = std::move($3);
    }
|   RelExp '>' AddExp {
        $$ = std::make_unique<RelExp>();
        $$->relExp = std::move($1);
        $$->op = RelOp::GT;
        $$->addExp = std::move($3);
    }
|   RelExp T_LE AddExp {
        $$ = std::make_unique<RelExp>();
        $$->relExp = std::move($1);
        $$->op = RelOp::LTE;
        $$->addExp = std::move($3);
    }
|   RelExp T_GE AddExp {
        $$ = std::make_unique<RelExp>();
        $$->relExp = std::move($1);
        $$->op = RelOp::GTE;
        $$->addExp = std::move($3);
    };

EqExp:
    RelExp {
        $$ = std::make_unique<EqExp>();
        $$->relExp = std::move($1);
    }
|   EqExp T_EQ RelExp {
        $$ = std::make_unique<EqExp>();
        $$->eqExp = std::move($1);
        $$->op = EqOp::EQ;
        $$->relExp = std::move($3);
    }
|   EqExp T_NEQ RelExp {
        $$ = std::make_unique<EqExp>();
        $$->eqExp = std::move($1);
        $$->op = EqOp::NEQ;
        $$->relExp = std::move($3);
    };

LAndExp:
    EqExp {
        $$ = std::make_unique<LAndExp>();
        $$->eqExp = std::move($1);
    }
|   LAndExp T_AND EqExp {
        $$ = std::make_unique<LAndExp>();
        $$->lAndExp = std::move($1);
        $$->eqExp = std::move($3);
    };

LOrExp:
    LAndExp {
        $$ = std::make_unique<LOrExp>();
        $$->lAndExp = std::move($1);
    }
|   LOrExp T_OR LAndExp {
        $$ = std::make_unique<LOrExp>();
        $$->lOrExp = std::move($1);
        $$->lAndExp = std::move($3);
    };

%%

void Compiler::Parser::error(const location_type& l, const std::string& m) {
    std::cerr << "Error at " << l << ": " << m << std::endl;
}
