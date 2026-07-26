#include <iostream>
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "codegen/CodeGenerator.h"
#include "ast/AssignmentExpr.h"
#include "llvm/Support/raw_ostream.h"
int main()
{
    Lexer lexer("x=42");


    auto tokens = lexer.tokenize();
Parser parser(tokens);
auto expr=parser.parse();
for (const auto& t : tokens)
{
    std::cout << static_cast<int>(t.Type)
              << " : "
              << t.Text << '\n';
}
if (!expr)
{
    std::cout << "Parse failed!\n";
    return 1;
}
if (dynamic_cast<AssignmentExpr*>(expr.get()))
    std::cout << "Parsed assignment!\n";
else
    std::cout << "Not assignment!\n";
CodeGenerator CG;
CG.createMainFunction();
llvm::Value* result=expr->codegen(CG);


CG.getBuilder().CreateRet(result);

CG.getModule()->print(llvm::outs(), nullptr);

    return 0;
}