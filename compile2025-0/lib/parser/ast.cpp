#include "parser/ast.h"

void CompUnit::accept(Visitor &visitor) { visitor.visit(*this); }
void DeclDef::accept(Visitor &visitor) { visitor.visit(*this); }
void Def::accept(Visitor &visitor) { visitor.visit(*this); }
void Decl::accept(Visitor &visitor) { visitor.visit(*this); }
void InitVal::accept(Visitor &visitor) { visitor.visit(*this); }
void FuncDef::accept(Visitor &visitor) { visitor.visit(*this); }
void FuncFParam::accept(Visitor &visitor) { visitor.visit(*this); }
void Block::accept(Visitor &visitor) { visitor.visit(*this); }
void Stmt::accept(Visitor &visitor) { visitor.visit(*this); }
void ReturnStmt::accept(Visitor &visitor) { visitor.visit(*this); }
void IfStmt::accept(Visitor &visitor) { visitor.visit(*this); }
void WhileStmt::accept(Visitor &visitor) { visitor.visit(*this); }
void AddExp::accept(Visitor &visitor) { visitor.visit(*this); }
void MulExp::accept(Visitor &visitor) { visitor.visit(*this); }
void UnaryExp::accept(Visitor &visitor) { visitor.visit(*this); }
void PrimaryExp::accept(Visitor &visitor) { visitor.visit(*this); }
void Number::accept(Visitor &visitor) { visitor.visit(*this); }
void Call::accept(Visitor &visitor) { visitor.visit(*this); }
void LVal::accept(Visitor &visitor) { visitor.visit(*this); }
void RelExp::accept(Visitor &visitor) { visitor.visit(*this); }
void EqExp::accept(Visitor &visitor) { visitor.visit(*this); }
void LAndExp::accept(Visitor &visitor) { visitor.visit(*this); }
void LOrExp::accept(Visitor &visitor) { visitor.visit(*this); }
void BlockItem::accept(Visitor &visitor) { visitor.visit(*this); }