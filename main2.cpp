
#include"llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include  "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "codegen/CodeGenerator.h"
#include "ast/NumberExpr.h"
#include "ast/BinaryExpr.h"
using namespace llvm;
int main()
{
    CodeGenerator CG;

    auto &Context = CG.getContext();
    auto &Builder = CG.getBuilder();
    auto *TheModule = CG.getModule();


    FunctionType  *PrintfType =FunctionType ::get(
        IntegerType::getInt32Ty(Context),PointerType::get(
            Type::getInt8Ty(Context),0 ),true);
FunctionCallee PrintfFunc= TheModule->getOrInsertFunction("printf",PrintfType);

FunctionType *FT=FunctionType::get(Type::getInt32Ty(Context),false);
Function *MainFunc=Function::Create(FT,Function::ExternalLinkage,"main",TheModule);

BasicBlock *BB=BasicBlock::Create(Context,"entry",MainFunc);
Builder.SetInsertPoint(BB);

auto ExprTree=
std::make_unique<BinaryExpr>(
    '*',
    std::make_unique<BinaryExpr>(
        '+',
        std::make_unique<NumberExpr>(3),
        std::make_unique<NumberExpr>(4)
    ),
    std::make_unique<BinaryExpr>(
        '-',
        std::make_unique<NumberExpr>(4),
        std::make_unique<NumberExpr>(3)
    )
);
Value *Res=ExprTree->codegen(CG);
Value *FormatStr=Builder.CreateGlobalStringPtr("%d\n");    

Builder.CreateCall(PrintfFunc,{FormatStr,Res});

Builder.CreateRet(ConstantInt::get(Context,APInt(32,0)));
verifyFunction(*MainFunc);
TheModule->print(outs(),nullptr);
return 0;
}