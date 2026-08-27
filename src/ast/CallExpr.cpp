#include "ast/CallExpr.h"
#include "codegen/CodeGenerator.h"

CallExpr::CallExpr(
    const std::string& callee,
    std::vector<std::unique_ptr<Expr>>arguments
)
:Callee(callee),
Arguments(std::move(arguments))
{

}

const std::string& CallExpr::getName() const
{
    return Callee;
}
const std::vector<std::unique_ptr<Expr>>& CallExpr::getArguments() const
{
    return Arguments;
}
llvm::Value*CallExpr::codegen(CodeGenerator&CG)
{
    llvm::Function* function=CG.getModule()->getFunction(Callee);
    if(!function)
    {
        return nullptr;
    }
    std::vector<llvm::Value*> args;
    for(auto& argument:Arguments)
    {
        llvm::Value*value=argument->codegen(CG);
        if(!value)
        {
            return nullptr;
        }
         args.push_back(value);

    }
   return CG.getBuilder().CreateCall(function,args);
}