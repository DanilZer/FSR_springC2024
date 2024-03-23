all: main.o

main.o: main.o
	g++ main.cpp parser.cpp solver.cpp -o main.o

clean:
	rm *.o output
