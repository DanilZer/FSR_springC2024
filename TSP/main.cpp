#include "parser.h"
#include "solver.h"

#include<iostream>

int main() {
    Parser TheParser;
    Solver TheSolver;
    std::string s;

    std::cin >> s;

    TheParser.ParseFile(s);
    TheParser.FillMatrix();

    int N = TheParser.GetSize();
    Point* P = TheParser.GetPoints();
    double** M = TheParser.GetMatrix();

    TheSolver.SetData(N, M);
    TheSolver.Solve();

    double PathLen = TheSolver.GetPathLen();
    int* Path = TheSolver.GetPath();

    std::cout  << PathLen  << '\n';
    for(int i=0; i<N; i++)
        std::cout << Path[i] << ' ';
    std::cout << '\n';

    return 0;
}
