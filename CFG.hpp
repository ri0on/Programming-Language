#pragma once
#include <string>
#include <vector>
#include "AST.hpp"

enum val{
    USED,
    UNUSED,
    SEEN
};

class CFG{
    private:
        std::string body;
        val valid = UNUSED;
        CFG parse_DFS(AST G);
    public:
        CFG *link, *sec_link;
        std::vector<CFG> parse(AST G);
        CFG(std::string str = "", CFG *l = nullptr, CFG *sl = nullptr)
            : body(str), link(l), sec_link(sl) {}
        void printCFG();
};