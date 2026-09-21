#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <utility>
#include <regex>
#include <stack>
#include <set>
#include <fstream>
using namespace std;

// --------------------- AST -------------

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
    {regex(R"(\s*(While)\s+(.*?)\s*(:\()\s*(.*)(\)))"), WHILE}, 
    {regex(R"(\s*(If)\s+(.*?)\s*(:\[)\s*(.*?)(\])\s+(Else)\s*(:\[)\s*(.*)(\]))"), IF}, // if условие : тело Else : тело
    {regex(R"(\s*(INT|CHAR|VOID)\s+(\w+)\s*(=)\s*(.+))"), VAR}, 
    {regex(R"(\s*([^;]+);\s*([\s\S]*))"), BODY},
    {regex(R"(\s*(.+)\s*[<]\s*(.+))"), LESS},//проблема с порядком действий
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
        default: break; 
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

    for(int i=0; i<counter; i++) cout<<"- ";
    if(a->children.size()>0) cout<<enum_names[a->type]<<endl;
    
    for(int i=0; i<counter; i++) cout<<"- ";
    cout<<AST.value<<endl;
    for(struct graph gr : a->children){
        counter++;
        printAST(gr);
        counter--;
    }
    
}


// ---------------------- CFG ----------------------


enum val{
    USED,
    UNUSED,
    SEEN
};

struct CFG{
    CFG *link, *sec_link;
    string body;
    enum val valid = UNUSED;
};

CFG parse_DFS(graph G){
    stack<graph> graphs;
    //std::queue<graph>
    CFG *cfg_last;
    graphs.push(G);
    while(!graphs.empty()){
        graph tmp = graphs.top();

        //CFG* current = analyze(tmp);
        //append(cfg_last, current);
        //cfg_last = current;

        graphs.pop();
        for(graph gr: tmp.children)
            graphs.push(gr);
    }
    return {};
}

std::vector<CFG> parse(graph G){
    vector<CFG> funcs;
    for(graph func: G.children){
        funcs.push_back(parse_DFS(func));
    }
    return funcs;
}

//lvl 1     l11 l12 l13
//          / \   \
//lvl 2 l111 l112 l121
//        /   /

void printCFG(CFG *cfg){
    // PlantUML
    //cfg1 -> cfg2 ->cfg3_cfg3.1 ->cfg4 -> cfg1
    ofstream out("CFG.puml");

    stack<CFG*> id;
    CFG* temp;
    id.push(cfg);
    out << "@startuml\n";
    out << "state \"" << id.top()->body << "\" as n" << id.top() << "\n";
    while(!id.empty()/*temp->link != nullptr*/){
        temp = id.top();
        temp->valid = USED;
        id.pop();


        if(temp->link != cfg && temp->link->valid != USED){
            if(temp->link->valid == UNUSED){
                out << "state \"" << temp->link->body << "\" as n" << temp->link << "\n";
                out << "n" << temp << "--> n" << temp->link << "\n";
                temp->link->valid = SEEN;
            }
            else out << "n" <<temp << "--> n" << temp->link << "\n";
            id.push(temp->link);
        }
        /*else if(temp->link == cfg){
            out << "state \"" << temp->link->body << "\" as n" << temp->link << "\n";
            out << temp << "-->" << temp->link << "\n";
        }*/

        if(temp->sec_link != nullptr && temp->sec_link->valid != USED) {
            if(temp->sec_link->valid == UNUSED){
                out << "state \"" << temp->sec_link->body << "\" as n" << temp->sec_link << "\n";
                out << "n" << temp << "--> n" << temp->sec_link << "\n";
                temp->sec_link->valid = SEEN;
            }
            else out << "n" << temp << "--> n" << temp->sec_link << "\n";
            id.push(temp->sec_link);
        }
        // pretemp = temp;
        // temp = pretemp->link;
        // out << "state \"" << temp->body << "\" as " << temp << "\n";
        // out << pretemp << "-->" << temp << "\n";
        // if(pretemp->sec_link != nullptr){
        //     CFG* sec_temp = pretemp->sec_link;
        //     out << "state \"" << sec_temp->body << "\" as " << sec_temp << "\n";
        //     out << pretemp << "-->" << sec_temp << "\n"; //вопрос равна ли ссылка false ссылке true, пока приму что да.
        //     if(temp->link != nullptr)
        //         out << sec_temp << "-->" << temp->link << "\n";
        // }
    }
    out << "@enduml\n";
}

    //     if
    //    /  \
    // true  false  
    //   \    /
    //    ...

int main(){
    string str; // Чтение из файла code.txt

    ifstream file("code.txt"); 
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
    

    //printAST(G);

    std::vector<CFG> cfg ;//= parse(G);
    
    CFG cfg1, cfg2, cfg3_1, cfg3_2, cfg4;
    cfg1.body = "a";
    cfg1.link = &cfg2;
    cfg1.sec_link = 0;

    cfg2.link = &cfg3_1;
    cfg2.body = "b";
    cfg2.sec_link = &cfg3_2;

    cfg3_1.link = &cfg4;
    cfg3_1.body = "c1";
    cfg3_1.sec_link = 0;
    
    cfg3_2.link = &cfg4;
    cfg3_2.body = "c2";    
    cfg3_2.sec_link = 0;

    cfg4.link = &cfg1;
    cfg4.body = "d";
    cfg4.sec_link = 0;

    cfg.push_back(cfg1);

    printCFG(&cfg1);

}

