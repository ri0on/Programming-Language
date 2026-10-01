#pragma once
#include "CFG.hpp"
class Parse{
    private:
    enum instr_type{
        add,
        jump//...
    };

    std::vector<std::pair<std::string, instr_type>> dict;

    struct instr{
        enum instr_type type;
        std::vector<std::string> operands;
    };
    typedef std::vector<instr> block;

    std::vector<block> blocks;

    std::vector<std::string> assemble;

    block IF();

    block WHILE();

    public:
    Parse(std::vector<CFG*> c);
};