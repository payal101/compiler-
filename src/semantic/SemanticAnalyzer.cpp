#include "semantic/SemanticAnalyzer.h"
#include "ast/Program.h"
#include "ast/VariableExpr.h"
#include "ast/NumberExpr.h"
#include "ast/ComparisionExpr.h"
#include "ast/BinaryExpr.h"
#include "ast/AssignmentExpr.h"
#include "ast/Expr.h"
#include "ast/BlockStmt.h"
#include "ast/Ifstmt.h"
#include "ast/WhileStmt.h"
#include "ast/BreakStmt.h"
#include "ast/ContinueStmt.h"
#include "ast/ForStmt.h"
#include <iostream>
#include <vector>


bool SemanticAnalyzer::analyze(Program*program)
{
  HasError=false;
  Scopes.clear();
  enterScope();
  for(auto& stmt:program->Statements)
  {
    visit(stmt.get());
  }
  exitScope();
  return !HasError;
}
void SemanticAnalyzer::visit(Expr*expr)
{
    if(auto* A=dynamic_cast<AssignmentExpr*>(expr))
    {
        visit(A);

    }
    else if(auto* V=dynamic_cast<VariableExpr*>(expr))
    {
        visit(V);
    }
    else if(auto* B=dynamic_cast<BinaryExpr*>(expr))
    {
        visit(B);
    }
    else if(auto*N=dynamic_cast<NumberExpr*>(expr))
    {
        visit(N);
    }
    else if(auto*C=dynamic_cast<ComparisionExpr*>(expr))
    {
        visit(C);
    }
    else if(auto *L=dynamic_cast<BlockStmt*>(expr))
    {
        visit(L);
    }
    else if(auto *I=dynamic_cast<Ifstmt*>(expr))
    {
        visit(I);
    }
    else if(auto*W=dynamic_cast<WhileStmt*>(expr))
    {
        visit(W);
    }
    else if(auto*breakStmt=dynamic_cast<BreakStmt*>(expr))
    {
        visit(breakStmt);
    }
    else if(auto*continueStmt=dynamic_cast<ContinueStmt*>(expr))
    {
        visit(continueStmt);    
    }
}
void SemanticAnalyzer::visit(NumberExpr*expr)
{

}
void SemanticAnalyzer::visit(BinaryExpr*expr)
{
    visit(expr->getLeft());
    visit(expr->getRight());

}
void SemanticAnalyzer::visit(ComparisionExpr*expr)
{
visit(expr->getLeft());
visit(expr->getRight());
}
void SemanticAnalyzer::visit(AssignmentExpr*expr)
{
visit(expr->getValue());
Scopes.back().insert(expr->getName());
}

void SemanticAnalyzer::enterScope()
{
    Scopes.push_back({});
}
void SemanticAnalyzer::exitScope()
{
    Scopes.pop_back();
}
bool SemanticAnalyzer::isDefined(const std::string& name)
{
    for(auto it=Scopes.rbegin();it!=Scopes.rend();it++)
    {
        if(it->find(name)!=it->end())
        {
            return true;
        }
    }
    return false;
}

void SemanticAnalyzer::visit(VariableExpr*expr)
{
    if(!isDefined(expr->getName()))
    {
        std::cout<<"Semantic Error:Undefined variable"
        << expr->getName()<<'\n';

    HasError=true;
    }
}

void SemanticAnalyzer::visit(BlockStmt*expr)
{
    enterScope();
    for(auto& stmt:expr->Statements)
    {
        visit(stmt.get());
    }
    exitScope();
}

void SemanticAnalyzer::visit(Ifstmt*expr)
{
   visit(expr->getCondition());
   visit(expr->getThenBlock());
   if(expr->getElseBlock())
   {
    visit(expr->getElseBlock());
   }
}
void SemanticAnalyzer::visit(WhileStmt*expr)
{
    visit(expr->getCondition());
    LoopDepth++;
    visit(expr->getBody());
    LoopDepth--;
 
}
void SemanticAnalyzer::visit(BreakStmt*expr)
{
    if(LoopDepth=0)
    {
        std::cout<<"Semantic Error:: break outside loop\n";
        HasError=true;
    }
}
void SemanticAnalyzer::visit(ContinueStmt*expr)
{
    if(LoopDepth==0)
    {
        std::cout<<"Semantic Error:continue outside loop";
        HasError=true;
    }
}
void SemanticAnalyzer::visit(ForStmt*expr)
{
    visit(expr->getInit());
    visit(expr->getCondition());
    LoopDepth++;
    visit(expr->getBody());
    LoopDepth--;
    visit(expr->getIncrement());
 
}