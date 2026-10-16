#include "AST.hpp"
#include <iostream>

const std::map<oper_type, std::string> AST::enum_names{
        {NULL_OP, "NULL_OP"},
    {PROGRAM, "PROGRAM"},
    {FUNC, "FUNC"},
    {BODY, "BODY"},

    {VAR, "VAR"},
    {VAR_REF, "VAR_REF"},
    {ASSIGN, "ASSIGN"},
    {LIT, "LIT"},

    {SUM, "SUM"},
    {SUB, "SUB"},
    {MUL, "MUL"},
    {DIV, "DIV"},

    {LESS, "LESS"},
    {MORE, "MORE"},
    {CMP, "CMP"},

    {IF, "IF"},
    {WHILE, "WHILE"},
    {RETURN, "RETURN"},

    {XOR, "XOR"},
    {AND, "AND"},
    {OR, "OR"},

    {MASS, "MASS"}
};


AST::AST(){}

// void AST::printAST(int counter){
//     std::cout<<enum_names.at(type)<<" : ";
    
//     for(int i=0; i<counter; i++) std::cout<<"- ";
//     std::cout<<value<<std::endl;
//     for(auto& gr: children){
//         gr.printAST(counter+1);
//     }
// }
void AST::printAST(int counter) {
    if (counter > 0) {
        for (int i = 0; i < counter - 1; i++) {
            std::cout << "  | "; // Чистый ASCII отступ
        }
        std::cout << "  +-- "; // Текстовая стрелочка
    }

    std::cout << enum_names.at(type);
    
    if (!value.empty()) {
        std::cout << " [" << value << "]";
    }
    std::cout << std::endl;

    for (auto& gr : children) {
        gr.printAST(counter + 1);
    }
}




oper_type AST::getType(){
    return type;
}

void AST::setType(oper_type type){
    this->type = type;
}

void AST::setDataType(TokenType type){
    this->dataType = type;
}

std::string AST::getValue(){
    return value;
}

bool AST::getVisited(){
    return visited;
}

void AST::setValue(std::string inside){
    this->value = inside;
}

std::string AST::getEnumName(oper_type type){
    return AST::enum_names.at(type);
}
TokenType AST::getDataType(){
    return this->dataType;
}