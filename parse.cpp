#include "parse.hpp"

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


Parse::block Parse::BLOCK(CFG* cfg){
    //  VAR
    //  LESS
    //  SUM
    std::string res;
    switch(cfg->getType()){
        SUM: {
            std::string op1 = cfg->getOp1();
            std::string op2 = cfg->getOp2();
            std::string rg1 = "";//mapReg(op1);
            std::string rg2 = "";//mapReg(op2);
            std::string rg = "";//regInc();
            res = "add "+rg+","+rg1+","+rg2;
            break;
        }
        VAR: {
            std::string op1 = cfg->getOp1();
            std::string op2 = cfg->getOp2();
            std::string rg1 = "";//mapReg(op2);
            std::string op3 = cfg->getOp3();
            std::string rg2 = "";//mapReg(op3);
            res = "move "+rg1+","+rg2;
            break;
            // int a = b + c;

            // add rg1, rg2, rg3
            // move rg4, rg1

            //         VAR
            //       /  |  \
            //   type name   SUM
            //              .........
        }
        LESS: {
            std::string op1 = cfg->getOp1();
            std::string op2 = cfg->getOp2();
            std::string rg1 = "";//mapReg(op1);
            std::string rg2 = "";//mapReg(op2);
            res = "less "+rg1+","+rg2;
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

    // linker
}