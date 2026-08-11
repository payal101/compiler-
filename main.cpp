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
int main()
{

std::string source = R"(
function add(a, b) {
    return a + b;
}

function main() {
    return add(5, 7);
}
)";
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

std::cout<<"Statements"
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


CG.getModule()->print(llvm::outs(), nullptr);

    return 0;
}