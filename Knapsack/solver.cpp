#include "solver.h"

void Solver::SetData(int Size, int Volume, int** Matrix, const std::vector<std::pair<int, int>>* things) {
    this->Clear();

    N = Size;
    K = Volume;
    if (N <= 0 || K <= 0)
        return;

    G = Matrix;
    T = things;
    ans = new int[N]{0};
}

void Solver::Clear() {
    N = 0;
    K = 0;
    G = NULL;
    T = NULL;
    delete[] ans;
    ans = NULL;
}

void Solver::Solve() {
    if (N <= 0 || K <= 0 || G == NULL || ans == NULL)
        return;

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= K; j++) {
            if ((*T)[i - 1].second > j) {
                G[i][j] = G[i - 1][j];
            } else {
                G[i][j] = std::max(G[i - 1][j], G[i - 1][j - (*T)[i - 1].second] + (*T)[i - 1].first);
            }
        }
    }

    MaxValue = G[N][K];
}

void Solver::FindThings(int i, int j) {
    if (G[i][j] == 0){
        return;
    }
    if (G[i-1][j] == G[i][j]){
        FindThings(i-1 , j);
    } else{
        FindThings(i-1,j - (*T)[i-1].second);
        ans[i-1]+=1;
    }
}
