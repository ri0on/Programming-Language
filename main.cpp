#include <fstream>
#include <iostream>
#include <vector>
#include "AST.hpp"
#include "CFG.hpp"
#include "Lexer.hpp"
using namespace std;

string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::INT:        return "INT";
        case TokenType::CHAR:       return "CHAR";
        case TokenType::VOID:       return "VOID";
        case TokenType::IF:         return "IF";
        case TokenType::WHILE:      return "WHILE";
        case TokenType::RETURN:     return "RETURN";

        case TokenType::PLUS:       return "PLUS";
        case TokenType::MINUS:      return "MINUS";
        case TokenType::MUL:        return "MUL";
        case TokenType::DIV:        return "DIV";
        case TokenType::ASSIGN:     return "ASSIGN";

        case TokenType::XOR:        return "XOR";
        case TokenType::AND:        return "AND";
        case TokenType::OR:         return "OR";
        case TokenType::CMP:        return "CMP";
        case TokenType::LESS:       return "LESS";
        case TokenType::MORE:       return "MORE";

        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::NUMBER:     return "NUMBER";

        case TokenType::SEMICOLON:  return "SEMICOLON";
        case TokenType::COMMA:      return "COMMA";
        case TokenType::LPAREN:     return "LPAREN";
        case TokenType::RPAREN:     return "RPAREN";
        case TokenType::LBRACE:     return "LBRACE";
        case TokenType::RBRACE:     return "RBRACE";
        case TokenType::COLON:      return "COLON";
    }

    return "UNKNOWN";
}

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

   //AST G(str);

    // AST *G = new AST();

    // AST *sec_main = new AST();
    // AST *VAR3 = new AST();

    // AST *main = new AST();
    // AST *VAR1 = new AST();
    // AST *VAR2 = new AST();
    // AST *Cond = new AST();
    // AST *iT = new AST();
    // AST *iE = new AST();
    // AST *If = new AST();
    // AST *RET = new AST();

    // G->setType(PROGRAM);

    // sec_main->setType(FUNC);
    // VAR3->setType(VAR);

    // main->setType(FUNC);
    // RET->setType(LIT);
    // Cond->setType(LESS);
    // VAR1->setType(VAR);
    // VAR2->setType(VAR);
    // If->setType(IF);
    // iT->setType(SUM);
    // iE->setType(SUB);

    // G->setValue("Source");

    // sec_main->setValue("sec_main");
    // VAR3->setValue("int c = 5");

    // main->setValue("main");
    // VAR1->setValue("int a = 1");
    // VAR2->setValue("int b = 2");
    // If->setValue("If");
    // Cond->setValue("a < b");
    // iT->setValue("a + b");
    // iE->setValue("a - b");
    // RET->setValue("return");

    // sec_main->children.push_back(*VAR3);

    // If->children.push_back(*Cond);If->children.push_back(*iT);If->children.push_back(*iE);
    // main->children.push_back(*VAR1);main->children.push_back(*VAR2); main->children.push_back(*If); main->children.push_back(*RET);
    // G->children.push_back(*main); G->children.push_back(*sec_main);

    
    

    // G.printAST();
    // vector<CFG*> cfg = CFG::parse(G);

    // cfg[0]->printCFG();

    Lexer lex;
    vector<Token> toks = lex.tokenize(str);
    for(auto& i : toks){
        cout << tokenTypeToString(i.type) << " : " << i.value << endl; 
    }

}



