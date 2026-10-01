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
        oper_type type;//.....
        val valid = UNUSED;
        static CFG* parse_DFS(AST G);
        static std::pair<CFG*, CFG*> analyze_node(AST g);
    public:
        CFG *link, *sec_link;
        static std::vector<CFG*> parse(AST G);
        CFG(std::string str = "", CFG *l = nullptr, CFG *sl = nullptr)
            : body(str), link(l), sec_link(sl) {}
        void printCFG();
        void setBody(std::string str);
        void setType(oper_type type);
};