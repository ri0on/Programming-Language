#pragma once
#include <string>
#include <vector>
#include "AST.hpp"
#include "Token.hpp"

enum val{
    USED,
    UNUSED,
    SEEN
};

class CFG{
    private:
        std::string body;
        std::string op1;
        std::string op2;
        std::string op3;// enum
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
        oper_type getType();
        std::string getOp1();
        std::string getOp2();
        std::string getOp3();
};