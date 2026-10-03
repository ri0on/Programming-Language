#include <cctype>
#include "Lexer.hpp"

Token Lexer::assign_kw(const std::string &str){
    Token curr;
    if(str == "INT"){
        curr.type = TokenType::INT;
        curr.value = str;
    } else if(str == "CHAR"){
        curr.type = TokenType::CHAR;
        curr.value = str;
    } else if(str == "VOID"){
        curr.type = TokenType::VOID;
        curr.value = str;
    } else if(str == "If"){
        curr.type = TokenType::IF;
        curr.value = str;
    } else if(str == "While"){
        curr.type = TokenType::WHILE;
        curr.value = str;
    } else if(str == "sb"){
        curr.type = TokenType::RETURN;
        curr.value = str;
    } else if(str == "Else"){
        curr.type = TokenType::ELSE;
        curr.value = str;
    }
    
    else {
        curr.type = TokenType::IDENTIFIER;
        curr.value = str;
    }
    return curr;
}

Token Lexer::assign_special_symb(const std::string &str){
    Token curr;
    //operators
    if(str == "+"){
        curr.type = TokenType::PLUS;
        curr.value = str;
    } else if(str == "-"){
        curr.type = TokenType::MINUS;
        curr.value = str;
    } else if(str == "*"){
        curr.type = TokenType::MUL;
        curr.value = str;
    } else if(str == "/"){
        curr.type = TokenType::DIV;
        curr.value = str;
    } else if(str == "="){
        curr.type = TokenType::ASSIGN;
        curr.value = str;
    }
    //logic
    else if(str == "^"){
        curr.type = TokenType::XOR;
        curr.value = str;
    } else if(str == "~"){
        curr.type = TokenType::AND;
        curr.value = str;
    } else if(str == "|"){
        curr.type = TokenType::OR;
        curr.value = str;
    } else if(str == "=="){
        curr.type = TokenType::CMP;
        curr.value = str;
    } else if(str == "<"){
        curr.type = TokenType::LESS;
        curr.value = str;
    } else if(str == ">"){
        curr.type = TokenType::MORE;
        curr.value = str;
    }
    // punctuation
    else if(str == ";"){
        curr.type = TokenType::SEMICOLON;
        curr.value = str;
    } else if(str == ","){
        curr.type = TokenType::COMMA;
        curr.value = str;
    } else if(str == "("){
        curr.type = TokenType::LPAREN;
        curr.value = str;
    } else if(str == ")"){
        curr.type = TokenType::RPAREN;
        curr.value = str;
    } else if(str == "{"){
        curr.type = TokenType::LBRACE;
        curr.value = str;
    } else if(str == "}"){
        curr.type = TokenType::RBRACE;
        curr.value = str;
    } else if(str == ":"){
        curr.type = TokenType::COLON;
        curr.value = str;
    } else if(str == "["){
        curr.type = TokenType::LBRACKET;
        curr.value = str;
    } else if(str == "]"){
        curr.type = TokenType::RBRACKET;
        curr.value = str;
    } 

    else{
        curr.type = TokenType::UNKNOWN;
        curr.value = str;
    }
    return curr;
}


std::vector<Token> Lexer::tokenize(const std::string &code){
    std::vector<Token> tokens;
    std::string container = "";
    Token curr;
    size_t i = 0;
    while(i<code.size()){
        if(isspace(code[i])){
            i++;
            continue;
        }
        else if(isalpha(code[i]) || code[i] == '_'){
            while(i < code.size() && (isalnum(code[i]) || code[i] == '_')){
                container.push_back(code[i++]);
                
            }            
            curr = assign_kw(container);
        }
        else if(isdigit(code[i])){
            while(i < code.size() && isdigit(code[i])){
                container.push_back(code[i++]);
            }
            curr.type = TokenType::NUMBER;
            curr.value = container;
        } else{
            if(code[i] == '=' && i + 1 < code.size() && code[i+1] == '='){
                container = "==";
                i+=2;
            } else{
                container.push_back(code[i++]);
            }
            curr = assign_special_symb(container);
        }
        container = "";
        tokens.push_back(curr);
    }
    return tokens;
}