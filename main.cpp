#include <fstream>
#include <iostream>
#include <vector>
#include "AST.hpp"
#include "CFG.hpp"
#include "ASTBuilder.hpp"
using namespace std;

// string tokenTypeToString(TokenType type) {
//     switch (type) {
//         case TokenType::INT:        return "INT";
//         case TokenType::CHAR:       return "CHAR";
//         case TokenType::VOID:       return "VOID";
//         case TokenType::IF:         return "IF";
//         case TokenType::WHILE:      return "WHILE";
//         case TokenType::RETURN:     return "RETURN";

//         case TokenType::PLUS:       return "PLUS";
//         case TokenType::MINUS:      return "MINUS";
//         case TokenType::MUL:        return "MUL";
//         case TokenType::DIV:        return "DIV";
//         case TokenType::ASSIGN:     return "ASSIGN";

//         case TokenType::XOR:        return "XOR";
//         case TokenType::AND:        return "AND";
//         case TokenType::OR:         return "OR";
//         case TokenType::CMP:        return "CMP";
//         case TokenType::LESS:       return "LESS";
//         case TokenType::MORE:       return "MORE";

//         case TokenType::IDENTIFIER: return "IDENTIFIER";
//         case TokenType::NUMBER:     return "NUMBER";

//         case TokenType::SEMICOLON:  return "SEMICOLON";
//         case TokenType::COMMA:      return "COMMA";
//         case TokenType::LPAREN:     return "LPAREN";
//         case TokenType::RPAREN:     return "RPAREN";
//         case TokenType::LBRACE:     return "LBRACE";
//         case TokenType::RBRACE:     return "RBRACE";
//         case TokenType::COLON:      return "COLON";
//     }

//     return "UNKNOWN";
// }

int main(){
    string str; // Чтение из файла code.txt

    ifstream file("code.txt"); 
    if (!file) {
        cerr << "Cannot open file\n";
        return 1;
    }

    string line;
    while (getline(file, line)){
        str+=line;
    }

    Lexer lex;
    vector<Token> tokens = lex.tokenize(str);
    ASTBuilder builder(tokens);
    AST program = builder.build();
    program.printAST();

    vector<CFG*> cfg_code = CFG::parse(program);
    cfg_code[0]->printCFG();
}



/*
code
 ↓
Lexer
 ↓
AST
 ↓
IRBuilder
 ↓
IR
 ↓
CFG
 ↓
CodeGen
 ↓
Assembly


*/