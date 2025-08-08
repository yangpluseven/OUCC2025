#include "ast.h"

void CompUnitNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

void DefNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

void DeclNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

void InitValNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

void FuncDefNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

void FuncFParamNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

void BlockNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

void StmtNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

void ReturnStmtNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

void IfStmtNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

void WhileStmtNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

void AddExpNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

void MulExpNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

void UnaryExpNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

void PrimaryExpNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

void NumberNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

void CallNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

void LValNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

void RelExpNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

void EqExpNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

void LAndExpNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

void LOrExpNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }

void BlockItemNode::accept(ASTVisitor &visitor) { visitor.visit(*this); }
