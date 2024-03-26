#include "solver.h"

void Solver::SetData(int Size, int Volume, int** Matrix) {
    this->Clear();

    N = Size;
    K = Volume;
    if (N <= 0 || K <= 0)
        return;

    G = Matrix;
    Colors = new int[N];
    std::fill_n(Colors, N, -1);
    AvailableColors = new int[N];
    std::fill_n(AvailableColors, N, 1);
}

void Solver::Clear() {
    N = 0;
    K = 0;
    G = NULL;
    delete[] Colors;
    Colors = NULL;
    delete[] AvailableColors;
    AvailableColors = NULL;
}

void Solver::Solve() {
    if (N <= 0 || K <= 0 || G == NULL || Colors == NULL)
        return;

    Colors[0] = 0;

    for (int v=0; v<N ;v++){
        std::fill_n(AvailableColors, N, 1);

        for (int i = 0 ; i < N ; i++){
            if (G[v][i]==1 && Colors[i]!=-1)
                AvailableColors[Colors[i]] = 0;
        }

        int cr;

        for (cr = 0 ; cr < N ; cr++){
            if (AvailableColors[cr] == 1)
                break;
        }

        Colors[v] = cr;
    }
}

void Solver::FindMax() {
    for (int i = 0 ; i < N ; i++){
        if (Colors[i] > ans){
            ans = Colors[i];
        }
    }
    ans++;
}
