#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <regex>
using namespace std;

enum oper_type{
    NULL_OP,

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

struct graph{
    struct graph* parent;
    vector<struct graph> children;
    enum oper_type type;
    string value;
};


map<enum oper_type, string> enum_names = {
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

// [^aeyo]

vector<pair<regex, enum oper_type>> patterns = {
    {regex(R"(\s*(INT|CHAR|VOID)\s+(\w+)\s*(\(\w*\))\s*(:\{)\s*(.*)(\}))"), FUNC},
    {regex(R"(\s*(While)\s+(.*?)\s*(:)\s*(.*))"), WHILE}, 
    {regex(R"(\s*(If)\s+(.*?)\s*(:)\s*(.*?)\s+(Else)\s*(:)\s*(.*))"), IF}, // if условие : тело Else : тело
    {regex(R"(\s*([^;]+);\s*([\s\S]*))"), BODY},
    {regex(R"(\s*(.+)\s*[<]\s*(.+))"), LESS},//проблема с порядком действий
    {regex(R"(\s*(INT|CHAR|VOID)\s+(\w+)\s*(=)\s*(.+))"), VAR}, 
    {regex(R"(\s*(.+)\s*[+]\s*(.+))"), SUM},
    {regex(R"(\s*(.+)\s*[-]\s*(.+))"), SUB},
    {regex(R"(\s*(INT|CHAR|VOID)\s+(\w+)\s*(\[\s*\d+\s*\]))"), MASS},
    {regex(R"(\w+)"), LIT}
};

vector<string> analyze(pair<string, enum oper_type> p, smatch pattern){
    vector<string> operands;
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
    }
    return operands; 
}

struct graph AST(string str){
    struct graph G;
    for(pair p : patterns){
        smatch found;
        if(regex_match(str, found, p.first)){
            vector<string> operands = analyze({str, p.second}, found);
            if(operands.size()<=1){
                G.value = operands[0];
                G.type = LIT;
            }
            else {
                G.value = str;
                G.type = p.second;
                for(string op: operands){
                    if(op.find_first_not_of(" \t") == string::npos) continue;//npos-ненайдено
                    G.children.push_back( AST(op) );
                }
            }
            break;
        }
    }
    return G;
}

int counter = 1;

void printAST(struct graph AST){
    struct graph* a = &AST;

    if(a->children.size()>0) cout<<enum_names[a->type]<<endl;
    
    for(int i=0; i<counter; i++) cout<<"- ";
    cout<<AST.value<<endl;
    for(struct graph gr : a->children){
        counter++;
        printAST(gr);
        counter--;
    }
    
}

int main(){
    string str; // Чтение из файла code.txt

    ifstream file("test.txt"); // a + b + c problem
    if (!file) {
        cerr << "Cannot open file\n";
        return 1;
    }

    string line;
    while (getline(file, line)){ // проблема с многострочностью
        str+=line;
    }

    struct graph G;
    G.type = PROGRAM;
    G.value = ".";
    G.children.push_back(AST(str));
    

    printAST(G);

}
