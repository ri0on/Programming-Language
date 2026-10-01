#include "CFG.hpp"
#include "AST.hpp"
#include <stack>
#include <fstream>

void CFG::setBody(std::string str){
    body = str;
}

std::pair<CFG*, CFG*> CFG::analyze_node(AST g){
    CFG* elem, *end;
    switch(g.getType()){
        case IF: {
            elem = new CFG();
            elem->setType(IF);
            elem->setBody(g.children[0].getValue());
            end = new CFG();
            end->setBody("MERGE");
            std::pair<CFG*, CFG*> tp = analyze_node(g.children[1]);
            std::pair<CFG*, CFG*> ep = analyze_node(g.children[2]);
            elem->link = tp.first;
            elem->sec_link = ep.first;
            tp.second->link = end;
            ep.second->link = end;
            break;
        } 
        case WHILE: {break;}
        default: {
            elem = new CFG();
            elem->setBody(g.getValue());
            elem->setType(g.getType());
            end = elem;
        } 
    }    
    return {elem, end};
}

void append(CFG* prev, CFG* next){
    prev->link = next;
}

CFG* CFG::parse_DFS(AST G){
    std::stack<AST> graphs;
    //std::queue<graph>
    CFG* start = new CFG(G.getValue());

    CFG *cfg_last = start;

    for(auto it = G.children.rbegin(); it != G.children.rend(); ++it){
            if (!(*it).getVisited()) graphs.push(*it);
        }

    while(!graphs.empty()){
        AST tmp = graphs.top();
        graphs.pop();

        std::pair<CFG*,CFG*> p = analyze_node(tmp);
        append(cfg_last, p.first);
        cfg_last = p.second;
            
    }

    cfg_last->link = start;
    return start;
}

std::vector<CFG*> CFG::parse(AST G){// для функций
    std::vector<CFG*> funcs;
    for(AST func: G.children){
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

void CFG::setType(oper_type type){
    this->type = type;
}

//AST, написать код который будет подменивать имена переменных регситрами(временные регистры, освобождение регистров) и размапить их





