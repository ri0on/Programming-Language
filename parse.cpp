#include "parse.hpp"
#include <stdexcept>
Parse::block Parse::IF(CFG* cfg){
    //      IF (COND)
    //     / \
    //|true]  |false| 
    //     \  /
    //     end


    // b... COND, true
    // jmp false
    // ///
    // true:
        

    // jmp end
    // ///
    // false:


    // jmp end
    // ///
    // end:


}

Parse::block Parse::WHILE(CFG* cfg){
    //            |->While(Cond)
    //            | /       \
    //            |-BODY     END

    // while:b... COND, BODY
    // jmp end

    // BODY:

    // jmp while
    // END:

}

int Parse::counter = 1;//singlton
std::string Parse::regInc(){
    return std::to_string(counter++);
}
std::string Parse::mapReg(std::string op){
    if(regs.find(op) == regs.end()){
        return regs[op];
    } else{
        regs[op] = "r" + regInc();
        return regs[op];
    }
}

Parse::block Parse::BLOCK(CFG* cfg){
    //  VAR
    //  LESS
    //  SUM
    block res;
    AST curr_ast = cfg->getAST();

    switch(curr_ast.getType()){
        case SUM: {
            std::string op1 = genExpression(curr_ast.children[0]);
            std::string op2 = genExpression(curr_ast.children[1]);
            std::string rg1 = mapReg(op1);
            std::string rg2 = mapReg(op2);
            std::string rg = regInc();
            res.push_back(instr_dict.at(add) + " " + rg + "," + rg1 + "," + rg2);
            break;
        }
        VAR: {
            std::string op1 = curr_ast.getValue();
            std::string op2 = genExpression(curr_ast.children[0], res);
            TokenType type = curr_ast.getDataType();
            std::string rg1 = mapReg(op1);
            std::string rg2 = mapReg(op2);
            res.push_back("move "+rg1+","+rg2);
            break;
        }
        LESS: {
            std::string op1 = genExpression(curr_ast.children[0]);
            std::string op2 = genExpression(curr_ast.children[1]);
            std::string rg1 = mapReg(op1);
            std::string rg2 = mapReg(op2);
            res.push_back("less "+rg1+","+rg2);
            break;
        }
    }
    return {res};
}

//map<var,reg>

Parse::Parse(std::vector<CFG*> c){
    FILE* f = fopen("name", "w");
    for(CFG* cfg: c){
        block b;
        switch(cfg->getType()){
            IF:{ b = IF(cfg); break;}
            WHILE: { b = WHILE(cfg); break;}
            default: { b = BLOCK(cfg);}
        }
        for(std::string str: b) ;//f.fwrite(str);
    }   
}

std::string Parse::genExpression(AST expr, block& steps){
  
    switch (expr.getType()){
            case LIT:{return expr.getValue();}
            case VAR_REF:{
                return mapReg(expr.getValue());
            }
            case SUM:
            case ASSIGN:
            case SUB:
            case MUL:
            case DIV:
            case LESS:
            case MORE:
            case CMP:{
                std::string left = genExpression(expr.children[0], steps);
                std::string right = genExpression(expr.children[1], steps);
                std::string rg =  
                steps.push_back()  
                
                return mapReg(left.getValue() + ", " + right.getValue());
            }
            default:{
                throw std::runtime_error("incorrect expression in PARSE.");
                break;
            }
            
        }
 
}
