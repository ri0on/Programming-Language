#pragma once
#include <string>
#include <vector>


enum class TokenType{
    UNKNOWN,

    // keywords
    INT,
    CHAR,
    VOID,
    IF,
    ELSE,
    WHILE,
    RETURN,
    // operators
    PLUS,
    MINUS,
    MUL,
    DIV,
    ASSIGN,
    // logic
    XOR,
    AND,
    OR,
    CMP,
    LESS,
    MORE,
    // identifiers / literals
    IDENTIFIER,
    NUMBER,
    // punctuation
    SEMICOLON,  // ;
    COMMA,      // ,
    LPAREN,     // (
    RPAREN,     // )
    LBRACE,     // {
    RBRACE,     // }
    COLON,      // :
    LBRACKET,   // [
    RBRACKET    // ]
};

struct Token{
    TokenType type;
    std::string value;
};
class Lexer{
    private:
        Token assign_kw(const std::string &str);
        Token assign_special_symb(const std::string &str);
    public:
        std::vector<Token> tokenize(const std::string& code);
};
