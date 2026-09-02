#include <iostream>
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "codegen/CodeGenerator.h"
#include "ast/AssignmentExpr.h"
#include "llvm/Support/raw_ostream.h"
#include "ast/Program.h"
#include "ast/ComparisionExpr.h"
#include "semantic/SemanticAnalyzer.h"
#include "ast/BlockStmt.h"
#include "analysis/CFG.h"
#include "semantic/Scope.h"
#include <cassert>
int main()
{
std::string source = R"(
x=3;
if (x>0) {
    x = 1;
} else {
    x = 2;
}
y = x + 3;)";


Lexer lexer(source);
    auto tokens = lexer.tokenize();
Parser parser(tokens);
auto program=parser.parse();
if(program)
{
    std::cout<<"Program parsed\n";
}
for (const auto& t : tokens)
{
    std::cout << static_cast<int>(t.Type)
              << " : "
              << t.Text << '\n';
}

if (!program)
{
    std::cout << "Parse failed!\n";
    return 1;
}

std::cout<<" Number of executable statements are "
<<program->Statements.size()   
<<'\n';

SemanticAnalyzer SA;
if(!SA.analyze(program.get()))
{
     std::cout << "Semantic analysis failed\n";
    return 1;
}

//if (dynamic_cast<AssignmentExpr*>(expr.get()))
  //  std::cout << "Parsed assignment!\n";
//else
  //  std::cout << "Not assignment!\n";
  std::cout << "Program statements = "
          << program->Statements.size() << '\n';

if(auto* block =
    dynamic_cast<BlockStmt*>(program->Statements[0].get()))
{
    std::cout << "Block statements = "
              << block->Statements.size() << '\n';
}
CodeGenerator CG;
CG.createMainFunction();

llvm::Value*result=nullptr;

//llvm::Value* result=expr->codegen(CG);
if(dynamic_cast<ComparisionExpr*>(program->Statements[0].get()))
{
    std::cout<<"Comparision parsed\n";
}

for (auto& statement : program->Statements)
{
    std::cout << typeid(*statement).name() << '\n';
    result = statement->codegen(CG);
}
CG.getBuilder().CreateRet(llvm::ConstantInt::get(
    llvm::Type::getInt32Ty(CG.getContext()),
    0
)
);
llvm::Function*mainFunction=CG.getModule()->getFunction("main");
CFG cfg;
cfg.build(mainFunction);
std::cout<<"CFG\n";
cfg.print();
std::cout<<"\n===DFS====\n";
cfg.dfs(cfg.getEntry());

cfg.computeDominators();
cfg.printDominators();

cfg.computeImmediateDominators();
cfg.printImmediateDominators();

cfg.buildDominatorTree();
cfg.printDominatorTree(cfg.getEntry(),0);

cfg.computeDominanceFrontiers();

cfg.printDominanceFrontiers();
cfg.findVariableDefinitions();
cfg.insertPhiNodes();
cfg.printPhiNodes();
cfg.renameToSSA();

CG.getModule()->print(llvm::outs(), nullptr);

    return 0;
}
