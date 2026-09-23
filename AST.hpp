#pragma once
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <utility>

enum oper_type {NULL_OP,

    // math
    SUM,
    SUB,
    MUL,
    DIV,

    BODY,

    // logic
    XOR,
    AND,
    OR,
    CMP,
    LESS,
    MORE,

    // type
    INT,
    CHAR,
    VOID,

    // variable
    VAR,

    // ctrl
    IF,
    // ELSE,
    WHILE,

    // func
    FUNC,

    // massive
    MASS,

    LIT,
    
    PROGRAM
};

class AST{
    private:
        AST* parent = nullptr;
        oper_type type;
        std::string value;

        static const std::map<oper_type, std::string> enum_names;
        static const std::vector<std::pair<std::regex,oper_type>> patterns;
        
        std::vector<std::string> analyze(std::pair<std::string, oper_type> p, std::smatch pattern);

    public:
        std::vector<AST> children;
        AST(std::string str);// был AST в main.cpp

        void printAST(int counter = 0);
};
