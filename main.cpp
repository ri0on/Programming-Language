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

    
    


    std::vector<CFG> cfg ;//= parse(G);
    
    CFG cfg1("a"), cfg2("b"), cfg3_1("c1"), cfg3_2("c2"), cfg4("d");//, cfg2("b", &cfg3_1, &cfg3_2), cfg3_1("c1", &cfg4), cfg3_2("c2", &cfg4), cfg4("d", &cfg1)
    cfg1.link = &cfg2;
    cfg2.link = &cfg3_1; cfg2.sec_link = &cfg3_2;
    cfg3_1.link = &cfg4; cfg3_2.link = &cfg4;
    cfg4.link = &cfg1;
    cfg.push_back(cfg1);

    cfg1.printCFG();

}

