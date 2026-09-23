#include "AST.hpp"
#include <iostream>

const std::map<oper_type, std::string> AST::enum_names{
        {BODY, "BODY"},
        {SUM, "SUM"},
        {SUB, "SUB"},
        {LESS, "LESS"},
        {IF, "IF"}, 
        {WHILE, "WHILE"}, 
        {FUNC, "FUNC"},
        {VAR, "VAR"}, 
        {MASS, "MASS"},
        {LIT, "LIT"},
        {PROGRAM, "PROGRAM"}
};

const std::vector<std::pair<std::regex,oper_type>> AST::patterns{
    {std::regex(R"(\s*(INT|CHAR|VOID)\s+(\w+)\s*(\(\w*\))\s*(:\{)\s*(.*)(\}))"), FUNC},
    {std::regex(R"(\s*(While)\s+(.*?)\s*(:\()\s*(.*)(\)))"), WHILE}, 
    {std::regex(R"(\s*(If)\s+(.*?)\s*(:\[)\s*(.*?)(\])\s+(Else)\s*(:\[)\s*(.*)(\]))"), IF}, // if условие : тело Else : тело
    {std::regex(R"(\s*(INT|CHAR|VOID)\s+(\w+)\s*(=)\s*(.+))"), VAR}, 
    {std::regex(R"(\s*([^;]+);\s*([\s\S]*))"), BODY},
    {std::regex(R"(\s*(.+)\s*[<]\s*(.+))"), LESS},
    {std::regex(R"(\s*(.+)\s*[+]\s*(.+))"), SUM},
    {std::regex(R"(\s*(.+)\s*[-]\s*(.+))"), SUB},
    {std::regex(R"(\s*(INT|CHAR|VOID)\s+(\w+)\s*(\[\s*\d+\s*\]))"), MASS}, 
    {std::regex(R"(\w+)"), LIT}
};

std::vector<std::string> AST::analyze(std::pair<std::string, oper_type> p, std::smatch pattern){
    std::vector<std::string> operands;
    switch (p.second){

        case BODY:{ // пробег по всем подстрокам, разделенными ; и добавление их в operands
            operands.push_back(pattern[1]);
            operands.push_back(pattern[2]);
            break;
        }
        case FUNC:{
            operands.push_back(pattern[1]);
            operands.push_back(pattern[2]);
            operands.push_back(pattern[3]);
            operands.push_back(pattern[5]);
            break;
        }
        case SUM:{
            operands.push_back(pattern[1]);
            operands.push_back(pattern[2]);
            break;
        }
        case SUB:{
            operands.push_back(pattern[1]);
            operands.push_back(pattern[2]);
            break;
        }
        
        case LESS:{
            operands.push_back(pattern[1]);
            operands.push_back(pattern[2]);
            break;
        }

        case IF:{
            operands.push_back(pattern[2]);
            operands.push_back(pattern[4]);
            operands.push_back(pattern[7]);//тут надо что бы принадлежал ELSE
            break;
        }
        case VAR:{
            operands.push_back(pattern[1]);
            operands.push_back(pattern[2]);
            operands.push_back(pattern[4]);
            break;
        }
        case WHILE:{
            operands.push_back(pattern[2]);
            operands.push_back(pattern[4]);
            break;
        }

        case LIT:{
            operands.push_back(p.first);
            break;
        }
        default: break; 
    }
    return operands; 
}

AST::AST(std::string str){
    for(const auto& p : patterns){
        std::smatch found;
        if(std::regex_match(str, found, p.first)){
            std::vector<std::string> operands = analyze({str, p.second}, found);
            if(operands.size()<=1){
                value = operands[0];
                type = LIT;
            }
            else {
                value = str;
                type = p.second;
                for(std::string op: operands){
                    if(op.find_first_not_of(" \t") == std::string::npos) continue;//npos-ненайдено
                    children.push_back( AST(op) );
                }
            }
            break;
        }
    }
}

void AST::printAST(int counter){

    for(int i=0; i<counter; i++) std::cout<<"- ";
    if(children.size()>0) std::cout<<enum_names.at(type)<<std::endl;
    
    for(int i=0; i<counter; i++) std::cout<<"- ";
    std::cout<<value<<std::endl;
    for(auto& gr: children){
        gr.printAST(counter+1);
    }
}