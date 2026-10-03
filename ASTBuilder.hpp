#pragma once
#include <vector>
#include "Lexer.hpp"
#include "AST.hpp"

class ASTBuilder{
    private:
        std::vector<Token> tokens;
        size_t pos = 0;

        Token& current();                // Покажи токен, на котором я сейчас стою.
        bool check(TokenType type);     // Я сейчас стою на таком типе токена?
        Token consume(TokenType type); // Я ожидаю здесь именно такой токен. Если он есть — забираю его и двигаюсь дальше. Если нет — syntax error.

        AST buildFunction();          // отвечает только за функции(знает их грамматику)
        std::vector<AST> buildBlock; // Читать инструкции одну за другой, пока блок не закончился. (пока не встретили '}':вызвать buildStatement())
        AST buildStatement();       // Какая инструкция начинается с текущего токена?
        AST buildVar();            // знает только грамматику переменной
        AST buildIf();            // знает только структуру If
        AST buildWhile();        // знает только структуру While
        AST buildExpression();  // отвечает только за выражения (1+1, a < b)  потом надо будет сделать полноценный порядок действий для больших выражений

    public:
        ASTBuilder(const std::vector<Token>& tkns) :
            tokens(tkns) {}
        AST build(); // создаёт корень, пока токены не закончились, читает функции
};