#include "solver.h"

void Solver::SetData(int Size, double** Matrix) {
    this->Clear();

    N = Size;

    if (N <= 0)
        return;

    G = Matrix;
    Path = new int[N+1];
}

void Solver::Clear() {
    N = 0;
    G = NULL;

    if (Path != NULL)
        delete [] Path;
}

void Solver::Solve() {
    if (N <= 0 || G == NULL || Path == NULL)
        return;

    for(int i=0; i<N; i++)
        Path[i] = i;
    Path[N] = 0;

    for(int i=0; i<N-2; i++)
        for(int j=N; j>=i+3; j--) {
            // std::cout << "i = " << i << ", j = " << j << '\n';
            this->CheckPath(i, j);
            // this->PrithPath();
        }

    PathLen = 0;
    for(int i=0; i<N; i++)
        PathLen += G[Path[i]][Path[i+1]];
}

void Solver::CheckPath(int i, int j) {
    double old_dist = G[Path[i]][Path[i+1]] + G[Path[j]][Path[j-1]];
    double new_dist = G[Path[i]][Path[j-1]] + G[Path[j]][Path[i+1]];

    if (new_dist < old_dist) {
        int p = i+1;
        int q = j-1;
        while(p < q) {
            std::swap(Path[p], Path[q]);
            p++;
            q--;
        }
    }
}

void Solver::PrithPath() {
    for(int i=0; i<=N; i++)
        std::cout << Path[i] << "  ";
    std::cout << '\n';
}
