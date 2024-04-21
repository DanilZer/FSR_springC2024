#include "parser.h"
#include "solver.h"

#include <iostream>
#include <vector>
#include <utility>

int main() {
    Parser TheParser;
    std::string s;

    std::cin >> s;

    TheParser.ParseFile(s);

    int N = TheParser.GetSize();
    int K = TheParser.GetVolume();
    auto& T = TheParser.Getthing();

    Solver solver(N, K, T);
    auto [max_v, item_ind] = solver.Solve();
    int* ans = new int[N]{0};
    std::cout << max_v << " ";
    for (int i = 0; i < item_ind.size(); i++) {
        ans[item_ind[i]] = 1;
        K -= T[item_ind[i]].second;
    }
    std::cout << K  <<"\n";
    for (int i = 0 ; i < N; i++){
        std::cout << ans[i]<< " ";
    }

    return 0;
}
