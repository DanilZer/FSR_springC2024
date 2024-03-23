all: main.o

main: main.o parser.o solver.o
	g++ main.o parser.o solver.o -o main

main.o: main.cpp
	g++ -c main.cpp -o main.o

parser.o: parser.cpp
	g++ -c parser.cpp -o parser.o

solver.o: solver.cpp
	g++ -c solver.cpp -o solver.o

clean:
	rm -f *.o main
