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
    } else if(tokens[pos].type == TokenType::VOIDtype){
        func.setDataType(consume(TokenType::VOID).type);
    } else if(tokens[pos].type == TokenType::CHAR){
        func.setDataType(consume(TokenType::CHAR).type);
    } else throw std::runtime_error("Syntax error: unexpected type");

    Token func_name = consume(TokenType::IDENTIFIER);

    consume(TokenType::LPAREN);
    struct para
    std::vector<Token> param_names; // надо представить AST узлом или структурой
    while(!check(TokenType::RPAREN)){
        if(tokens[pos].type == TokenType::INT){
        consume(TokenType::INT);
        } else if(tokens[pos].type == TokenType::VOID){
            consume(TokenType::VOID);
        } else if(tokens[pos].type == TokenType::CHAR){
            consume(TokenType::CHAR);
        } else throw std::runtime_error("Syntax error: unexpected param type");
        param_names.push_back(consume(TokenType::IDENTIFIER));
    }
    consume(TokenType::RPAREN);



}

AST ASTBuilder::build(){
    AST program;
    program.setType(PROGRAM);
    while(pos < tokens.size()){
        program.children.push_back(buildFunction()); // тут изменяется pos
    }
}