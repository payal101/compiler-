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
#include "ast/FunctionDec1.h"
#include "ast/ReturnStmt.h"
#include "semantic/Scope.h"
#include "ast/CallExpr.h"
#include "semantic/Type.h"
#include <iostream>
#include <vector>


bool SemanticAnalyzer::analyze(Program*program)
{
  HasError=false;
  CurrentScope=nullptr;
  ScopeStorage.clear();
  enterScope();
  for(auto& stmt:program->Statements)
  {
    visit(stmt.get());
  }
  exitScope();
  return !HasError;
}
Type SemanticAnalyzer::visit(Expr*expr)
{
    if(auto* A=dynamic_cast<AssignmentExpr*>(expr))
    {
        visit(A);
        return Type::Int;

    }
    else if(auto* V=dynamic_cast<VariableExpr*>(expr))
    {
        return visit(V);
    }
    else if(auto* B=dynamic_cast<BinaryExpr*>(expr))
    {
        visit(B);
        return Type::Int;
    }
    else if(auto*N=dynamic_cast<NumberExpr*>(expr))
    {
        visit(N);
        return Type::Int;
    }
    else if(auto*C=dynamic_cast<ComparisionExpr*>(expr))
    {
      return  visit(C);
    }
    else if(auto *L=dynamic_cast<BlockStmt*>(expr))
    {
        visit(L);
        return Type::Int;
    }
    else if(auto *I=dynamic_cast<Ifstmt*>(expr))
    {
        visit(I);
        return Type::Int;
    }
    else if(auto*W=dynamic_cast<WhileStmt*>(expr))
    {
        visit(W);
        return Type::Int;
    }
    else if(auto*F= dynamic_cast<FunctionDec1*>(expr))
    {
        visit(F);
        return Type::Int;
    }

    else if(auto*breakStmt=dynamic_cast<BreakStmt*>(expr))
    {
        visit(breakStmt);
        return Type::Int;
    }
    else if(auto*continueStmt=dynamic_cast<ContinueStmt*>(expr))
    {
        visit(continueStmt); 
        return Type::Int;   
    }
    else if(auto*R=dynamic_cast<ReturnStmt*>(expr))
    {
        visit(R);
        return Type::Int;
    }
    else if(auto*C=dynamic_cast<CallExpr*>(expr))
    {
       return visit(C);
    }
    return Type::Error;
}
Type SemanticAnalyzer::visit(NumberExpr*expr)
{
    return Type::Int;

}
Type SemanticAnalyzer::visit(BinaryExpr*expr)
{ Type leftType = visit(expr->getLeft());
    Type rightType = visit(expr->getRight());
    if(leftType==Type::Error||rightType==Type::Error)
    {
        return Type::Error;
    }
    if(leftType!=rightType)
    {
        std::cout<<"Semantic Error:Type mismatch in binary expression";
        HasError=true;
        return Type::Error;
    }
    return leftType;

}
Type SemanticAnalyzer::visit(ComparisionExpr*expr)
{
Type leftType=visit(expr->getLeft());
Type rightType=visit(expr->getRight());

if(leftType==Type::Error||rightType==Type::Error)
{
    return Type::Error;
}
    if(leftType!=rightType)
    {
        std::cout<<"Semantic Error : Type mismatch in comparision";
        HasError=true;
        return Type::Error;
    }
    return Type::Int;

}
void SemanticAnalyzer::visit(AssignmentExpr*expr)
{
Type valueType=visit(expr->getValue());
if(valueType==Type::Error)
{
    return ;
}
CurrentScope->declare(
    Symbol(
        expr->getName(),
        valueType,
        SymbolKind::Variable
    )
);

}

void SemanticAnalyzer::enterScope()
{
    ScopeStorage.push_back(
        std::make_unique<Scope>(CurrentScope)
    );
    
CurrentScope= ScopeStorage.back().get();
}
void SemanticAnalyzer::exitScope()
{
    CurrentScope=CurrentScope->getParent();
}
bool SemanticAnalyzer::isDefined(const std::string& name)
{
    return CurrentScope && CurrentScope->lookup(name)!=nullptr;
}

Type SemanticAnalyzer::visit(VariableExpr*expr)
{
    Symbol*symbol=CurrentScope->lookup(expr->getName());
    if(!symbol)
    {
        std::cout<<"Semantic Error: Undefined variable"<<expr->getName()<<'\n';
        HasError=true;
        return Type::Error;
    }
    return symbol->getType();
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
    if(LoopDepth==0)
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
void SemanticAnalyzer::visit(FunctionDec1*expr)
{
    CurrentScope->declare(
        Symbol(
            expr->getName(),
            Type::Int,
            SymbolKind::Function,
            expr->getParameters()
        )
    );
    enterScope();
    for(const auto& parameter :expr->getParameters())
    {
CurrentScope->declare(
    Symbol(
        parameter,
        Type::Int,
        SymbolKind::Parameter
    )
);
    }
    visit(expr->getBody());
    exitScope();
}
void SemanticAnalyzer::visit(ReturnStmt*expr)
{
    visit(expr->getValue());
}

Type SemanticAnalyzer::visit(CallExpr*expr)
{
    Symbol* symbol=CurrentScope->lookup(expr->getName());
    if(!symbol)
    {
        std::cout<<"Semantic Error: Undefined function "
        << expr->getName() <<'\n';
    HasError=true;
    return Type::Error;
    }
    if(symbol->getKind()!=SymbolKind::Function)
    {
        std::cout<<"Semantic Error"<<expr->getName()<<"is not a Function\n";
        HasError=true;
        return Type::Error;
    }
    for(auto& argument:expr->getArguments())
    {
        visit(argument.get());
    }
    if(expr->getArguments().size()!=symbol->getParameters().size())
    {
        std::cout<<"Semantic Error:Function  "
        <<expr->getName()
        <<symbol->getParameters().size()
        <<"  arguments , got  "
        <<expr->getArguments().size()
        <<'\n';
    HasError=true;
    return Type::Error;
    }
    return Type::Int;
}