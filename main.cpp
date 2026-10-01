#include <fstream>
#include <iostream>
#include <vector>
#include "AST.hpp"
#include "CFG.hpp"
using namespace std;



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

   AST G(str);

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

    
    

    //G.printAST();
    //vector<CFG*> cfg = CFG::parse(G);

    //cfg[0]->printCFG();
}

