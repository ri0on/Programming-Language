#pragma once
#include <string>
#include <vector>
#include <map>
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
    ASSIGN,

    // ctrl
    IF,
    // ELSE,
    WHILE,

    // func
    FUNC,

    // massive
    MASS,

    LIT,
    //return
    RETURN,
    
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
    public:
        
        std::vector<AST> children; // параметры - дети функции
        AST();
        oper_type getType();
        void setType(oper_type type);
        void setDataType(TokenType type);
        std::string getValue();
        void setValue(std::string inside);
        void printAST(int counter = 0);
        bool getVisited();
        static std::string getEnumName(oper_type type);
};
