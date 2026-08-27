#pragma once
#include <unordered_set>
#include <string>
#include<vector>
#include<memory>
#include<vector>
#include "semantic/Scope.h"
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
class FunctionDec1;
class ReturnStmt;
class CallExpr;

class SemanticAnalyzer{
    public:
    bool analyze(Program* program);
private:
bool HasError=false;
int LoopDepth=0;
Scope* CurrentScope=nullptr;
std::vector<std::unique_ptr<Scope>> ScopeStorage;

void enterScope();
void exitScope();
bool isDefined(const std::string& name);
bool declaredVariable(const std::string&);
bool isDeclared(const std::string&);
Type visit(Expr*expr);
void visit(AssignmentExpr*expr);
Type visit(VariableExpr*expr);
Type visit(BinaryExpr*expr);
Type visit(NumberExpr*expr);
Type visit(ComparisionExpr*expr);
void visit(BlockStmt*expr);
void visit(Ifstmt*expr);
void visit(WhileStmt*expr);
void visit(BreakStmt*expr);
void visit(ContinueStmt*expr);
void visit(ForStmt*expr);
void visit(FunctionDec1*expr);
void visit(ReturnStmt*expr);
Type visit(CallExpr*expr);

};