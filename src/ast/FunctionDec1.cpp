#include "ast/FunctionDec1.h"
#include "codegen/CodeGenerator.h"
 
FunctionDec1::FunctionDec1(
    const std::string& name,
    std::vector<std::string> parameters,
    std::unique_ptr<BlockStmt> body

)
:Name(name),
Parameters(std::move(parameters)),
Body(std::move(body))
{

}
const std::string& FunctionDec1::getName() const
{
    return Name;
}
const std::vector<std::string>&  FunctionDec1::getParameters() const
{
    return Parameters;
}
BlockStmt*FunctionDec1::getBody() const
{
    return Body.get();
}
llvm::Value*FunctionDec1::codegen(CodeGenerator&CG)
{
    auto& Context=CG.getContext();
   llvm::Module*Module =CG.getModule();

    llvm::FunctionType*FunctionType=
    llvm::FunctionType::get(
        llvm::Type::getInt32Ty(Context),
        std::vector<llvm::Type*>(
            Parameters.size(),
            llvm::Type::getInt32Ty(Context)
        ),
        false
    );
    llvm::Function* function=llvm::Function::Create(
        FunctionType,
        llvm::Function::ExternalLinkage,
        Name,
        Module
    );

    llvm::BasicBlock*Entry=
    llvm::BasicBlock::Create(
        Context,
        "entry",
       function
    );
    CG.getBuilder().SetInsertPoint(Entry);
    unsigned index=0;
    for(auto& arg:function->args())
    {
        std::string parameterName=Parameters[index];
        llvm::AllocaInst* alloca=CG.getBuilder().CreateAlloca(
            llvm::Type::getInt32Ty(Context),
            nullptr,
            parameterName
        );
        CG.getBuilder().CreateStore(&arg,alloca);
        CG.setNamedValue(parameterName,alloca);

        index++;
    }

    Body->codegen(CG);
    return function;
}