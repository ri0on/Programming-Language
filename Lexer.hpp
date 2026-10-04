#pragma once
#include <string>
#include <vector>
#include "Token.hpp"


class Lexer{
    private:
        Token assign_kw(const std::string &str);
        Token assign_special_symb(const std::string &str);
    public:
        std::vector<Token> tokenize(const std::string& code);
};
