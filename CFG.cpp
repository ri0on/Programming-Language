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
        case BODY: {
             if (g.children.empty()) {
                elem = new CFG();
                elem->setType(BODY);
                elem->setBody(AST::getEnumName(BODY));
                end = elem;
                break;
            }

            std::pair<CFG*, CFG*> begin_end = analyze_node(g.children[0]);
            CFG* local_end = begin_end.second;
            elem = begin_end.first;

            for(size_t i = 1; i < g.children.size(); i++){
                if(local_end == nullptr){
                    end = nullptr;
                    break;
                }
                std::pair<CFG*, CFG*> child = analyze_node(g.children[i]);
                local_end->link = child.first;
                local_end = child.second;
            }
            end = local_end;
            break;
        }
        case IF: {
            elem = new CFG();
            elem->setType(IF);
            elem->setBody(AST::getEnumName(IF));
            CFG* merge = new CFG();
            merge->setBody("MERGE");
            bool has_continue = false;
            std::pair<CFG*, CFG*> tp = analyze_node(g.children[1]);
            std::pair<CFG*, CFG*> ep = analyze_node(g.children[2]);
             elem->link = tp.first;
             elem->sec_link = ep.first;
            if(tp.second != nullptr){
                tp.second->link = merge;
                has_continue = true;
            }
            if(ep.second != nullptr){
                ep.second->link = merge;
                has_continue = true;
            }
            if(has_continue){
                end = merge;
            } else{
                delete merge;
                end = nullptr;
            }
            break;
        } 
        case WHILE: {
            elem = new CFG();
            elem->setType(WHILE);
            elem->setBody(AST::getEnumName(WHILE));
            CFG* exit = new CFG();
            exit->setBody("MERGE");
            std::pair<CFG*, CFG*> body = analyze_node(g.children[1]);
            elem->link = body.first;
            elem->sec_link = exit;
            if(body.second != nullptr){
                body.second->link = elem;
            }
            
            end = exit;
            break;
        }
        case RETURN: {
            elem = new CFG();
            elem->setType(RETURN);
            elem->setBody(AST::getEnumName(RETURN));
            end = nullptr;
            break;
        }
        default: {
            elem = new CFG();
            oper_type type = g.getType();
            elem->setType(type);
            elem->setBody(AST::getEnumName(type));
            
            
            end = elem;
        } 
    }
    elem->setAST(g);    
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
        if(cfg_last == nullptr) break;
        AST tmp = graphs.top();
        graphs.pop();

        std::pair<CFG*,CFG*> p = analyze_node(tmp);
        append(cfg_last, p.first);
        cfg_last = p.second;
            
    }
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
        if(temp->link != nullptr){
            if(temp->link != this && temp->link->valid != USED){//nullptr
            if(temp->link->valid == UNUSED){
                out << "state \"" << temp->link->body << "\" as n" << temp->link << "\n";
                temp->link->valid = SEEN;
                id.push(temp->link);
                }
            }
            out << "n" << temp << "--> n" << temp->link << "\n";
        }
        

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

AST CFG::getAST(){
    return this->ast;
}
void CFG::setAST(AST g){
    ast = g;
}

// oper_type CFG::getType(){return this->type;}

// std::string CFG::getIdent1(){
//     return this->ident1;
// }
// std::string CFG::getIdent2(){
//     return this->ident2;
// }

// oper_type CFG::getOp(){
//     return this->op;
// }
//AST, написать код который будет подменивать имена переменных регситрами(временные регистры, освобождение регистров) и размапить их





