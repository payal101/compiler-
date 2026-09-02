#include "analysis/CFG.h"
#include "llvm/IR/CFG.h"
#include "llvm/IR/Instructions.h"
#include <iostream>
void CFG::build(llvm::Function*function)
{
    Nodes.clear();
    if(!function)
    {
        return;
    }

    for(llvm::BasicBlock& block:*function)
{
   Nodes.push_back(std::make_unique<CFGNode>(&block));
}
for(const auto& nodePtr:Nodes)
{
    CFGNode* node=nodePtr.get();
    llvm::BasicBlock*block=node->Block;
    for(llvm::BasicBlock*successor:llvm::successors(block))
    {
        for(const auto& successorPtr:Nodes)
        {
            CFGNode*successorNode=successorPtr.get();
            if(successorNode->Block==successor)
            {
                node->Successors.push_back(successorNode);
                successorNode->Predecessors.push_back(node);
                break;
            }
        }
    }
}
}

void CFG::print() const
{
    for (const auto& node : Nodes)
    {
        std::cout << "BasicBlock: ";

        if (node->Block->hasName())
            std::cout << node->Block->getName().str();
        else
            std::cout << "<unnamed>";

        std::cout << "\n";

        std::cout << "  Successors: ";

        for (CFGNode* successor : node->Successors)
        {
            if (successor->Block->hasName())
                std::cout
                    << successor->Block->getName().str()
                    << " ";
            else
                std::cout << "<unnamed> ";
        }

        std::cout << "\n";

        std::cout << "  Predecessors: ";

        for (CFGNode* predecessor : node->Predecessors)
        {
            if (predecessor->Block->hasName())
                std::cout
                    << predecessor->Block->getName().str()
                    << " ";
            else
                std::cout << "<unnamed> ";
        }

        std::cout << "\n\n";
    }
}

void CFG::dfs(CFGNode*node)
{
    if(!node)
    {
        return;
    }
    if(Visited.count(node))
    {
        return;
    }
    Visited.insert(node);
    std::cout<<"Visited";
    if(node->Block->hasName())
    {
        std::cout<<node->Block->getName().str();
    }
    else
    {
        std::cout<<"<unamed>";
    }
    std::cout<<"\n";
    for(CFGNode* successor:node->Successors)
    {
        dfs(successor);
    }
}
CFGNode* CFG::getEntry()
{
    if(Nodes.empty())
    {
        return nullptr;
    }
    return Nodes.front().get();
}
void CFG::computeDominators()
{
    Dominators.clear();
    if(Nodes.empty())
    {
        return;
    }
    CFGNode* entry=Nodes.front().get();

    for(const auto& nodePtr:Nodes)
    {
        CFGNode*node=nodePtr.get();
        if(node==entry)
        {
            Dominators[node].insert(entry);
        }
        else
        {
            for(const auto&otherPtr:Nodes)
            {
                Dominators[node].insert(otherPtr.get());
            }
        }
    }

    bool changed=true;
    while(changed)
    {
        changed=false;
        for(const auto&nodePtr:Nodes)
        {
        CFGNode* node=nodePtr.get();
        if(node==entry)
        {
            continue;
        }
        if(node->Predecessors.empty())
        {
            continue;
        }
        std::unordered_set<CFGNode*>newDom;
        newDom=Dominators[node->Predecessors[0]];
        for(size_t i=1;i<node->Predecessors.size();++i)
        {
            CFGNode* pred=node->Predecessors[i];
            std::unordered_set<CFGNode*>intersection;
            for(CFGNode* candidate:newDom)
            {
            
                    if(Dominators[pred].count(candidate))
                    {
                        intersection.insert(candidate);
                    }
                
                

            }
            newDom=std::move(intersection);
        }
        newDom.insert(node);
        if(newDom!=Dominators[node])
        {
            Dominators[node]=std::move(newDom);
            changed=true;
        }
        }
    }
}

void CFG::printDominators()const
{
    std::cout<<"\n===Dominators===\n";
    for(const auto&nodePtr:Nodes)
    {
        CFGNode*node=nodePtr.get();
        std::cout<<"Dom(";
        if(node->Block->hasName())
        {
            std::cout<<node->Block->getName().str();
        }
        else
        {
            std::cout<<"<unnamed>";
        }
        std::cout<<") ={";
        for(CFGNode* dominator:Dominators.at(node))
        {
            if(dominator->Block->hasName())
            {
                std::cout<<dominator->Block->getName().str()
                <<"  ";

            }
            else{
                std::cout<<"<unnamed>";
            }
        }
        std::cout<<"}\n";
    }
}

void CFG::computeImmediateDominators()
{
    ImmediateDominator.clear();
    if(Nodes.empty())
    {
        return;
    }
    CFGNode* entry=Nodes.front().get();
    ImmediateDominator[entry]=nullptr;

    for(const auto&nodePtr: Nodes)
    {
        CFGNode* node= nodePtr.get();//entry to the pointer as a node
        if(node==entry)
        {
            continue;
        }
        CFGNode*idom=nullptr;
        for(CFGNode* candidate:Dominators[node])
        {
            if(candidate==node)
            {
                continue;
            }
            bool isImmediate=true;
            for(CFGNode*other:Dominators[node])// chekcing for the nearest dominator
            {
if(other==node|| other==candidate)
{
    continue;
}
if(Dominators[other].count(candidate))
{
    isImmediate=false;
    break;
}

            }
if(isImmediate)
{
    idom=candidate;
    break;
}
        }
        ImmediateDominator[node]=idom;
    }
}

void CFG::printImmediateDominators() const
{
    std::cout<<"\n===Immediate Dominators====\n";
    for(const auto& nodePtr:Nodes)
    {
        CFGNode* node=nodePtr.get();
        std::cout<<"idom (";
        if(node->Block->hasName())
        {
            std::cout<<node->Block->getName().str();

        }
        else
        {
            std::cout<<"<unnamed>";
        }
        std::cout<<")= ";

        CFGNode*idom=ImmediateDominator.at(node);//creating immediate dominator
        if(!idom)
        {
            std::cout<<"none";

        }
        else if(idom->Block->hasName())
        {
            std::cout<<idom->Block->getName().str();
        }
        else
        {
            std::cout<<"<unnamed>";
        }
        std::cout<<"\n";
    }
}

void CFG::buildDominatorTree()
{
    DominatorTree.clear();

    //fixed: to intialize every dominator node

    for(const auto&nodePtr:Nodes)
    {
        CFGNode* node=nodePtr.get();
        DominatorTree[node]={};
    }
    for(const auto&nodePtr:Nodes)
    {
        CFGNode* node= nodePtr.get();
        CFGNode* idom=ImmediateDominator[node];
        if(idom!=nullptr)
        {
            DominatorTree[idom].push_back(node);
        }
    }
}

void CFG::printDominatorTree(CFGNode*node,int depth) const
{
    if(!node)
    {
        return;
    }
    for(int i=0;i<depth;i++)
    {
        std::cout<<" ";
    }
   if(node->Block->hasName())
   {
    std::cout<<node->Block->getName().str();
   }
   else{
    std::cout<<"<unnamed>";
   }
   std::cout<<"\n";
   auto it=DominatorTree.find(node);
   if(it==DominatorTree.end())
   {
    return;
   }
   for(CFGNode*child:it->second)
   {
    printDominatorTree(child,depth+1);
   }
}

void CFG::computeDominanceFrontiers()
{
    DominanceFrontier.clear();
    for(const auto& nodePtr:Nodes)
    {
        CFGNode* node=nodePtr.get();
        if(node->Predecessors.size()<2)
        {
            continue;
        }
        CFGNode* idom=ImmediateDominator.at(node);
        for(CFGNode* predecessor:node->Predecessors)
        {
            CFGNode* runner=predecessor;
            while(runner!=idom)
            {
                DominanceFrontier[runner].insert(node);
                runner=ImmediateDominator.at(runner);
                if(runner==nullptr)
                {
                    break;
                }
            }
        }
    }
}

void CFG::printDominanceFrontiers() const
{
    std::cout<<"\n====Dominance Frontier====\n";
    for(const auto& nodePtr:Nodes)
    {
        CFGNode * node=nodePtr.get();
        std::cout<<"DF(";
        if(node->Block->hasName())
        {
            std::cout<<node->Block->getName().str();
        }
        else{
            std::cout<<"<unnamed>";
        }
        std::cout<<")={";
        auto it=DominanceFrontier.find(node);
        if(it!=DominanceFrontier.end())
        {
            for(CFGNode* frontierNode:it->second)
            {
                if(frontierNode->Block->hasName())
                {
                    std::cout<<frontierNode->Block->getName().str()<<" ";
                }
                else
                {
                    std::cout<<"<unnamed>";
                }
            }
            std::cout<<"}\n";
        }
    }
}
void CFG::findVariableDefinitions()
{
    VariableDefinition.clear();
    for(const auto& nodePtr:Nodes)
    {
        CFGNode* node=nodePtr.get();
        for(llvm::Instruction& instruction : *node->Block)
        {
            if(auto* store=llvm::dyn_cast<llvm::StoreInst>(&instruction))
            {
                llvm::Value*ptr=store->getPointerOperand();
                if(auto* alloca=llvm::dyn_cast<llvm::AllocaInst>(ptr))
                {
                    std::string variable=alloca->getName().str();
                    VariableDefinition[variable].insert(node);
                }
            }
        }
    }
}


void CFG::insertPhiNodes()
{
    for(const auto& [variable,definitionBlocks]:VariableDefinition)
    {
        for(CFGNode* definitionBlock:definitionBlocks)
        {
            auto frontierIt=DominanceFrontier.find(definitionBlock);
            if(frontierIt==DominanceFrontier.end())
            {
                continue;
            }
            for(CFGNode* frontierBlock:frontierIt->second)

            {
                bool alreadyExists=false;
                for(const PhiNode&phi:frontierBlock->PhiNodes)
                {
                    if(phi.Variable==variable)
                    {
                        alreadyExists=true;
                        break;
                    }
                }
            
            if(!alreadyExists)
            {
                PhiNode phi;
                phi.Variable=variable;
                phi.Block=frontierBlock;

                frontierBlock->PhiNodes.push_back(phi);
            }
        }
    }
    }
}

void CFG::printPhiNodes() const

{
    std::cout<<"\n===Phi Nodes===\n";

    for(const auto&nodePtr :Nodes)
    {
        CFGNode* node=nodePtr.get();
        if(node->PhiNodes.empty())
        {
            continue;
        }
        std::cout<<"\n";
        for(const PhiNode&phi:node->PhiNodes)
        {
            std::cout<<" "<<phi.Variable<<"= phi(...)\n";
        }
    }
}

std::string CFG::newVersion(const std::string& variable)
{
    int version=VersionCounter[variable];
    VersionCounter[variable]++;
    std::string name=variable+std::to_string(version);
  VersionStack[variable].push_back(name);
  return name;
}
std::string CFG::currentVersion(const std::string& variable)
{
    if(VersionStack[variable].empty())
    {
        return "";

    }
    return VersionStack[variable].back();
}
void CFG::renameBlock(CFGNode*node)
{

std::unordered_map<std::string,size_t>oldSizes;
for(const auto&[variable,stack]:VersionStack)
{
    oldSizes[variable]=stack.size();
}
   if(!node)
   {
    return;
   }
   std::cout<<"\nRenaming Block";
   if(node->Block->hasName())
   {
    std::cout<<node->Block->getName().str();
   }
   else{
    std::cout<<"<unnamed>";
   }
   std::cout<<"\n";
 
   for(PhiNode& phi:node->PhiNodes)
   {
    std::string version=newVersion(phi.Variable);
    phi.Version=version;
    std::cout<<" Phi"
    <<phi.Variable
    <<"->"
    <<phi.Version
    <<"\n";
}


   for(llvm::Instruction& instruction:*node->Block)
   {
    if(auto* store=llvm::dyn_cast<llvm::StoreInst>(&instruction))
    {
        llvm::Value* value=store->getValueOperand();
        llvm::Value*pointer=store->getPointerOperand();
        if(auto*alloca =llvm::dyn_cast<llvm::AllocaInst>(pointer))
        {
            std::string variable=alloca->getName().str();
            if(variable.empty())
            {
                continue;
            }
               std::string current=currentVersion("x");
    if(!current.empty())
    {
        std::cout<<"User x-> "<<current<<"\n";
    }
            std::string version=newVersion(variable);
            std::cout<<"Defination"<<variable
            <<"->"
            <<version
            <<"\n";
        }
    }
   
   }
     auto it=DominatorTree.find(node);
   if(it!=DominatorTree.end())
   {
    for(CFGNode*child:it->second)
    {
        renameBlock(child); 
    }
   }
   for(const auto&[variable,oldSize]:oldSizes)
   {
    VersionStack[variable].resize(oldSize);
   }

}

void CFG::renameToSSA()
{
    VersionCounter.clear();
    VersionStack.clear();

    CFGNode* entry=getEntry();
    if(!entry)
    {
        return;
    }
    renameBlock(entry);
}