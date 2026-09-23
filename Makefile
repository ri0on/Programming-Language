all: app

app: main.o AST.o CFG.o
	g++ -static main.o AST.o CFG.o -o app -O3

main.o: main.cpp AST.hpp CFG.hpp
	g++ -c main.cpp -o main.o

AST.o: AST.cpp AST.hpp
	g++ -c AST.cpp -o AST.o

CFG.o: CFG.cpp CFG.hpp AST.hpp
	g++ -c CFG.cpp -o CFG.o

clean:
	rm -f *.o app.exe app