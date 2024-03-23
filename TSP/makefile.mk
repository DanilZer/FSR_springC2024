all: main.o

main.o: main.o
	g++ main.cpp parser.cpp solver.cpp -o main.exe

clean:
	rm *.o output