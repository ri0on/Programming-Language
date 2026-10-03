all: clean app
	./app

app: main.o AST.o CFG.o Lexer.o
	g++ -static main.o AST.o CFG.o Lexer.o -o app -O3

main.o: main.cpp AST.hpp CFG.hpp Lexer.hpp
	g++ -c main.cpp -o main.o

AST.o: AST.cpp AST.hpp
	g++ -c AST.cpp -o AST.o

CFG.o: CFG.cpp CFG.hpp AST.hpp
	g++ -c CFG.cpp -o CFG.o

Lexer.o: Lexer.cpp Lexer.hpp
	g++ -c Lexer.cpp -o Lexer.o

clean:
	rm -f *.o app.exe app