#include "ast/Expr.h"
#include <string>
class VariableExpr:public Expr
{
    public:
    VariableExpr(const std::string&name);
    llvm::Value*codegen(CodeGenerator&CG)override;
    const std::string& getName()const{
        return Name;
    }
private:
std::string Name;
};