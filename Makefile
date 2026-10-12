all: clean app
	./app

app: main.o AST.o CFG.o Lexer.o ASTBuilder.o
	g++ -static main.o AST.o CFG.o Lexer.o ASTBuilder.o -o app -O3

main.o: main.cpp AST.hpp CFG.hpp Lexer.hpp
	g++ -c main.cpp -o main.o -O3

AST.o: AST.cpp AST.hpp
	g++ -c AST.cpp -o AST.o -O3

CFG.o: CFG.cpp CFG.hpp AST.hpp
	g++ -c CFG.cpp -o CFG.o -O3

Lexer.o: Lexer.cpp Lexer.hpp
	g++ -c Lexer.cpp -o Lexer.o -O3

ASTBuilder.o: ASTBuilder.cpp ASTBuilder.hpp
	g++ -c ASTBuilder.cpp -o ASTBuilder.o -O3

clean:
	rm -f *.o app.exe app