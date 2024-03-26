#include "parser.h"
#include "solver.h"

#include <iostream>
#include <vector>
#include <utility>

int main() {
    Parser TheParser;
    Solver TheSolver;
    std::string s;

    std::cin >> s;

    TheParser.ParseFile(s);
    TheParser.FillMatrix();

    int N = TheParser.GetNum();
    int K = TheParser.GetNumEdges();
    int** M = TheParser.GetMatrix();
    auto T = TheParser.GetEdges();
    TheSolver.SetData(N, K, M);
    TheSolver.Solve();
    TheSolver.FindMax();
    int* col = TheSolver.GetColors();
    int ans = TheSolver.GetMaxans();

    std::cout << ans;

    return 0;
}
