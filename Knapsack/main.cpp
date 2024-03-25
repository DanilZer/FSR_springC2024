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

    int N = TheParser.GetSize();
    int K = TheParser.GetVolume();
    auto& T = TheParser.Getthing();
    int** M = TheParser.GetMatrix();

    TheSolver.SetData(N, K, M, &T);
    TheSolver.Solve();

    TheSolver.FindThings(N,K);

    int maxV = TheSolver.GetMaxValue();
    int* ans = TheSolver.Getans();

    for (int i = 0 ; i < N ; i++){
        if (ans[i]==1){
            K-= T[i].second;
        }
    }

    std::cout << maxV << " " << K << "\n";
    for (int i = 0; i < N ; i++){
        std::cout << ans[i] << " " ;
    }

    return 0;
}
