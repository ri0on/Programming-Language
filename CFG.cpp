#include "CFG.hpp"
#include <stack>
#include <fstream>

CFG CFG::parse_DFS(AST G){
    std::stack<AST> graphs;
    //std::queue<graph>
    CFG *cfg_last;
    graphs.push(G);
    while(!graphs.empty()){
        AST tmp = graphs.top();

        //CFG* current = analyze(tmp);
        //append(cfg_last, current);
        //cfg_last = current;

        graphs.pop();
        for(auto& gr: tmp.children)
            graphs.push(gr);
    }
    return {};
}

std::vector<CFG> CFG::parse(AST G){
    std::vector<CFG> funcs;
    for(auto& func: G.children){
        funcs.push_back(parse_DFS(func));
    }
    return funcs;
}

void CFG::printCFG(){
    // PlantUML
    std::ofstream out("CFG.puml");

    std::stack<CFG*> id;
    CFG* temp;
    id.push(this);
    out << "@startuml\n";
    out << "state \"" << id.top()->body << "\" as n" << id.top() << "\n";
    while(!id.empty()){
        temp = id.top();
        temp->valid = USED;
        id.pop();

        if(temp->link != this && temp->link->valid != USED){//nullptr
            if(temp->link->valid == UNUSED){
                out << "state \"" << temp->link->body << "\" as n" << temp->link << "\n";
                temp->link->valid = SEEN;
                id.push(temp->link);
            }
        }
        out << "n" << temp << "--> n" << temp->link << "\n";

        if(temp->sec_link != nullptr && temp->sec_link->valid != USED) {
            if(temp->sec_link->valid == UNUSED){
                out << "state \"" << temp->sec_link->body << "\" as n" << temp->sec_link << "\n";
                temp->sec_link->valid = SEEN;
                id.push(temp->sec_link);
            }
            out << "n" << temp << "--> n" << temp->sec_link << "\n";
        }
    }
    out << "@enduml\n";
}