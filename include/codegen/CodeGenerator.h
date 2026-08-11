#pragma once

#include <memory>

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"


#include<unordered_map>
#include<string>
#include <vector>

class CodeGenerator {
public:
    CodeGenerator();

    llvm::LLVMContext& getContext();
    llvm::IRBuilder<>& getBuilder();
    llvm::Module* getModule();
    llvm::Function*createMainFunction();
    llvm::AllocaInst* getNamedValue(const std::string&name);
    void setNamedValue(
        const std::string&name,
        llvm::AllocaInst* value
    );
    void pushLoop(llvm::BasicBlock*breakTarget,llvm::BasicBlock*continueTarget);
    void popLoop();
    llvm::BasicBlock*getBreakTarget();
   
    llvm::BasicBlock*getContinueTarget();
   
private:
    llvm::LLVMContext Context;
    std::unique_ptr<llvm::Module> TheModule;
    llvm::IRBuilder<> Builder;
    std::unordered_map<std::string,llvm::AllocaInst*>NamedValues;
    std::vector<llvm::BasicBlock*>BreakTargets;
    std::vector<llvm::BasicBlock*>ContinueTargets;
  


};