#include "ASTBuilder.hpp"

Token& ASTBuilder::current(){
    return tokens[pos];
}

bool ASTBuilder::check(TokenType type){
    return tokens[pos].type == type;
}

Token ASTBuilder::consume(TokenType type){
    if(tokens[pos].type == type){
        Token result = tokens[pos];
        pos++;
        return result;
    }
    else throw std::runtime_error("Syntax error: unexpected token"); // надо убдет ловить в main, потом можео будет сделать что бы писался столбец и строка.
}


AST ASTBuilder::buildFunction(){
    AST func;
    func.setType(FUNC);
    if(tokens[pos].type == TokenType::INT){
        func.setDataType(consume(TokenType::INT).type);
    } else if(tokens[pos].type == TokenType::VOID){
        func.setDataType(consume(TokenType::VOID).type);
    } else if(tokens[pos].type == TokenType::CHAR){
        func.setDataType(consume(TokenType::CHAR).type);
    } else throw std::runtime_error("Syntax error: unexpected type");

    Token func_name = consume(TokenType::IDENTIFIER);

    consume(TokenType::LPAREN);

    std::vector<AST> params; 
    AST curr;
    curr.setType(VAR);
    while(!check(TokenType::RPAREN)){
        if(tokens[pos].type == TokenType::INT){
            curr.setDataType(TokenType::INT);
            consume(TokenType::INT);
        } else if(tokens[pos].type == TokenType::VOID){
            curr.setDataType(TokenType::VOID);
            consume(TokenType::VOID);
        } else if(tokens[pos].type == TokenType::CHAR){
            curr.setDataType(TokenType::CHAR);
            consume(TokenType::CHAR);
        } else throw std::runtime_error("Syntax error: unexpected param type");
        curr.setValue(consume(TokenType::IDENTIFIER).value);
        func.children.push_back(curr);
        if(check(TokenType::COLON))
            consume(TokenType::COLON);
    }
    consume(TokenType::RPAREN);

    consume(TokenType::LBRACE);
    std::vector<AST> body = buildBlock(); 

    for(auto& node : body){
        func.children.push_back(node);
    }
    consume(TokenType::RBRACE);

    return func;
}

AST ASTBuilder::buildPrimary(){
    AST node;
    if(check(TokenType::IDENTIFIER)){
        node.setType(VAR_REF);
        node.setDataType(TokenType::IDENTIFIER);
        node.setValue(consume(TokenType::IDENTIFIER).value);
        return node;
    } else if(check(TokenType::NUMBER)){
        node.setType(LIT);
        node.setDataType(TokenType::NUMBER);
        node.setValue(consume(TokenType::NUMBER).value);
        return node;
    } else if(check(TokenType::LPAREN)){
        consume(TokenType::LPAREN);
        AST expr = buildExpression();
        consume(TokenType::RPAREN);
        return expr;
    }
    else throw std::runtime_error("Syntax error: unexpected primary token");
}

AST ASTBuilder::buildMulDiv(){
    AST left = buildPrimary();
    while(check(TokenType::MUL) || check(TokenType::DIV)){
        TokenType op = current().type;
        pos++;
        AST right = buildPrimary();
        AST node;
        if(op == TokenType::MUL){
            node.setType(MUL);
        } else node.setType(DIV);
        node.children.push_back(left);
        node.children.push_back(right);
        left = node;// теперь левая переменная это не просто переменная а целое выражение
    }
    return left;
}

AST ASTBuilder::buildAddSub(){
    AST left = buildMulDiv();
    while(check(TokenType::PLUS) || check(TokenType::MINUS)){
        TokenType op = current().type;
        pos++;
        AST right = buildMulDiv();
        AST node;
        if(op == TokenType::PLUS){
            node.setType(SUM);
        } else node.setType(SUB);
        node.children.push_back(left);
        node.children.push_back(right);
        left = node;
    }
    return left;
}

AST ASTBuilder::buildComparison(){
    AST left = buildAddSub();
    while(check(TokenType::LESS) || check(TokenType::MORE) || check(TokenType::CMP)){
        TokenType op = current().type;
        pos++;
        AST right = buildAddSub();
        AST node;
        if(op == TokenType::LESS){
            node.setType(LESS);
        } else if(op == TokenType::MORE) node.setType(MORE);
        else node.setType(CMP);
        node.children.push_back(left);
        node.children.push_back(right);
        left = node;
    }
    return left;
}

AST ASTBuilder::buildExpression(){
    return buildComparison();
}

AST ASTBuilder::buildVar(){
    AST var;
    var.setType(VAR);
    if(check(TokenType::INT)) var.setDataType(consume(TokenType::INT).type);
    else if(check(TokenType::CHAR)) var.setDataType(consume(TokenType::CHAR).type);
    else throw std::runtime_error("Syntax error: expected variable type");
    var.setValue(consume(TokenType::IDENTIFIER).value);
    consume(TokenType::ASSIGN);
    var.children.push_back(buildExpression());
    consume(TokenType::SEMICOLON);
    return var;
}

AST ASTBuilder::buildIf(){
    
}

std::vector<AST> ASTBuilder::buildBlock(){
    std::vector<AST> nodes;
    while(!check(TokenType::RBRACE)){
        if(check(TokenType::INT) || check(TokenType::CHAR)){
            if(tokens[pos+2].type == TokenType::LPAREN){
                nodes.push_back(buildFunction());
            }
            else nodes.push_back(buildVar());
        } else if(check(TokenType::IF)) {nodes.push_back(buildIf());}
        else if(check(TokenType::WHILE)){nodes.push_back(buildWhile());}
        else if(check(TokenType::RETURN)){nodes.push_back(buildReturn());}
        else if(check(TokenType::IDENTIFIER)){nodes.push_back(buildAssignment());}

        else{throw std::runtime_error("Syntax error: incorrect block statement");}

    }
    return nodes;
}

//AST ASTBuilder::buildExpression

AST ASTBuilder::build(){
    AST program;
    program.setType(PROGRAM);
    while(pos < tokens.size()){
        program.children.push_back(buildFunction()); // тут изменяется pos
    }
}