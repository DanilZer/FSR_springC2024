#include "parser.h"


void Parser::Allocate() {
    if (N <= 0)
        return;
    if (K <=0)
        return;

    G = new int*[N];
    for(int i=0; i<=N; i++)
        G[i] = new int[K+1];
}


void Parser::Clear() {

    if (G == NULL)
        return;

    for(int i=0; i<=N; i++)
        if (G[i] != NULL)
            delete [] G[i];

    delete [] G;

    N = 0;
    K = 0;
}


void Parser::ParseFile(std::string Filename) {
    this->Clear();

    std::ifstream f(Filename);

    f >> N;
    f >> K;
    this->Allocate();

    T.reserve(N);
    for(int i = 0; i < N; i++) {
        int v, w;
        f >> v >> w;
        T.emplace_back(std::make_pair(v,w));
    }


    f.close();
}

void Parser::FillMatrix() {
    if (N <= 0)
        return;
    if (K <= 0)
        return;
    if (G == NULL)
        return;

    for(int i=0; i<=N; i++)
        for(int j=0; j<=K; j++)
            G[i][j] = 0;
}
