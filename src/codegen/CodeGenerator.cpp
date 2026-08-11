#include "codegen/CodeGenerator.h"
#include <unordered_map>
using namespace llvm;


CodeGenerator::CodeGenerator()
    : TheModule(std::make_unique<llvm::Module>("toy", Context)),
      Builder(Context)
    
{
}

LLVMContext& CodeGenerator::getContext() {
    return Context;
}

IRBuilder<>& CodeGenerator::getBuilder() {
    return Builder;
}

Module* CodeGenerator::getModule() {
    return TheModule.get();
}
llvm::Function* CodeGenerator::createMainFunction()
{
    auto*FT=llvm::FunctionType::get(
        llvm::Type::getInt32Ty(Context),
        false
    );

    auto *MainFunc=llvm::Function::Create(
        FT,
        llvm::Function::ExternalLinkage,
        "main",
        TheModule.get()
    );

    auto *BB=llvm::BasicBlock::Create(
        Context,
        "entry",
        MainFunc
    );
    Builder.SetInsertPoint(BB);
    return MainFunc;
}

llvm::AllocaInst* CodeGenerator::getNamedValue(const std::string&name)
{
    auto it=NamedValues.find(name);
    if(it==NamedValues.end())
    {
        return nullptr;
    }
    return it->second;
}

void CodeGenerator:: setNamedValue(
    const std::string& name,
    llvm::AllocaInst*value
){
    NamedValues[name]=value;
}

void CodeGenerator::pushLoop(llvm::BasicBlock*breakTarget,llvm::BasicBlock*continueTarget)
{
    BreakTargets.push_back(breakTarget);
    ContinueTargets.push_back(continueTarget);

}
void CodeGenerator::popLoop()
{
    BreakTargets.pop_back();
    ContinueTargets.pop_back();
}
llvm::BasicBlock*CodeGenerator::getBreakTarget()
{
    return BreakTargets.empty() ?  nullptr:
    BreakTargets.back();
}
llvm::BasicBlock*CodeGenerator::getContinueTarget()
{
    return ContinueTargets.empty() ? nullptr:
    ContinueTargets.back();
}



