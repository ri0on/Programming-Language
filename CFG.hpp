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
        // std::string ident1;
        // std::string ident2;
        // oper_type op;// enum
        AST ast;
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
        void setAST(AST g);
        AST getAST();

        // oper_type getType();
        // std::string getIdent1();//Ident
        // std::string getIdent2();//Ident
        // oper_type getOp();//operator
};