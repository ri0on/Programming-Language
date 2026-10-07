#pragma once
#include "CFG.hpp"
#include <map>

class Parse{

    private:
    enum instr_type{
        add,
        jump//...
    };

    std::vector<std::pair<instr_type, std::string>> dict;

    // struct instr{
    //     enum instr_type type;
    //     std::vector<std::string> operands;
    // };
    typedef std::vector<std::string> block;

    static int counter;
    static std::map<std::string, std::string> regs;
    static std::string regInc();
    static std::string mapReg(std::string op);

    std::vector<block> blocks;

    std::vector<std::string> assemble;//файл

    block IF(CFG* cfg);

    block WHILE(CFG* cfg);

    block BLOCK(CFG* cfg);

    public:
    Parse(std::vector<CFG*> c);
    
};