#pragma once
#include <string>
#include <vector>
#include <map>
#include <regex>
#include <utility>
#include "Token.hpp"

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


    // variable
    VAR,
    VAR_REF,

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

    // FOR
    // BREAK
    // SWITCH
    // GOTO

    // for(){
    //     for(){
    //         if(...) goto end;
    //     }
    // }
    // end:;
};

class AST{
    private:
        AST* parent = nullptr;
        oper_type type = NULL_OP;
        TokenType dataType;
        std::string value;
        bool visited = false;
        static const std::map<oper_type, std::string> enum_names;
        static const std::vector<std::pair<std::regex,oper_type>> patterns;
        
        std::vector<std::string> analyze(std::pair<std::string, oper_type> p, std::smatch pattern);

    public:
        std::vector<AST> children; // параметры - дети функции
        AST();
        AST(std::string str);// был AST в main.cpp
        oper_type getType();
        void setType(oper_type type);
        void setDataType(TokenType type);
        std::string getValue();
        void setValue(std::string inside);
        void printAST(int counter = 0);
        bool getVisited();
};
