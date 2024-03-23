all: main.exe

main.exe: main.cpp
	g++ main.cpp parser.cpp solver.cpp -o main.exe

clean:
	rm *.o output