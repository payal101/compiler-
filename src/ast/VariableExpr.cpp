#include "ast/VariableExpr.h"
#include "codegen/CodeGenerator.h"
VariableExpr::VariableExpr(const std::string& name)
:Name(name)
{

}
llvm::Value*VariableExpr::codegen(CodeGenerator&CG)
{
    llvm::AllocaInst*Ptr=CG.getNamedValue(Name);
   if(!Ptr)
   {
    return nullptr;
   }
   return CG.getBuilder().CreateLoad(
    llvm::Type::getInt32Ty(CG.getContext()),
    Ptr,
    Name
   );
}
