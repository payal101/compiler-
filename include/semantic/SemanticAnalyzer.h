#pragma once
#include <unordered_set>
#include <string>
#include<vector>
class Program;
class Expr;
class AssignmentExpr;
class VariableExpr;
class BinaryExpr;
class NumberExpr;
class ComparisionExpr;
class BlockStmt;
class Ifstmt;
class WhileStmt;
class BreakStmt;
class ContinueStmt;
class ForStmt;
class SemanticAnalyzer{
    public:
    bool analyze(Program* program);
private:
bool HasError=false;
int LoopDepth=0;
std::vector<std::unordered_set<std::string>>Scopes;

void enterScope();
void exitScope();
bool isDefined(const std::string& name);
bool declaredVariable(const std::string&);
bool isDeclared(const std::string&);
void visit(Expr*expr);
void visit(AssignmentExpr*expr);
void visit(VariableExpr*expr);
void visit(BinaryExpr*expr);
void visit(NumberExpr*expr);
void visit(ComparisionExpr*expr);
void visit(BlockStmt*expr);
void visit(Ifstmt*expr);
void visit(WhileStmt*expr);
void visit(BreakStmt*expr);
void visit(ContinueStmt*expr);
void visit(ForStmt*expr);

};