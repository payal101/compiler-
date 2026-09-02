#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include <unordered_set>
#include <string>
struct CFGNode;
struct PhiNode{
    std::string Variable;
    std::string Version;
    llvm::PHINode*Instruction=nullptr;
    CFGNode* Block;
};
struct CFGNode {
    llvm::BasicBlock* Block;

    std::vector<CFGNode*> Successors;
    std::vector<CFGNode*> Predecessors;
  std::vector<PhiNode> PhiNodes;
   


    explicit CFGNode(llvm::BasicBlock* block)
        : Block(block) {}
};






class CFG {
public:
    CFG() = default;

    void build(llvm::Function* function);
    void print() const;
    void dfs(CFGNode* node);
    void computeDominators();
    
    void printDominators() const;
    void computeImmediateDominators();
    void printImmediateDominators() const;
    void buildDominatorTree();
    void printDominatorTree(CFGNode* node,int depth) const;
    void computeDominanceFrontiers();
    void printDominanceFrontiers() const;
   
    void findVariableDefinitions();
void insertPhiNodes();
    void printPhiNodes() const;
    void renameToSSA();
    CFGNode* getEntry();


private:
    std::vector<std::unique_ptr<CFGNode>> Nodes;
std::unordered_set<CFGNode*>Visited;

    std::unordered_map<
        CFGNode*,
        std::unordered_set<CFGNode*>
    > Dominators;
   

    CFGNode* getOrCreateNode(llvm::BasicBlock* block);
    std::unordered_map<CFGNode*,CFGNode*>ImmediateDominator;
    std::unordered_map<CFGNode*,std::vector<CFGNode*>>DominatorTree;
     std::unordered_map<
        llvm::BasicBlock*,
        CFGNode*
    > NodeMap;
std::unordered_map<CFGNode*,std::unordered_set<CFGNode*>>DominanceFrontier;
std::unordered_map<std::string,std::unordered_set<CFGNode*>>VariableDefinition;
std::unordered_map<std::string,int>VersionCounter;
std::unordered_map<std::string,std::vector<std::string>>VersionStack;
std::string newVersion(const std::string& variable);
std::string currentVersion(const std::string& variable);
void renameBlock(CFGNode* node);



  
};

