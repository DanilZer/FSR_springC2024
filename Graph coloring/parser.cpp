#include "parser.h"


void Parser::Allocate() {
    if (N <= 0)
        return;
    if (K <=0)
        return;

    G = new int*[N];
    for(int i=0; i<N; i++){
        G[i] = new int[N];
        std::fill_n(G[i], N, 0);
    }
}


void Parser::Clear() {

    if (G == NULL)
        return;

    for(int i=0; i<N; i++)
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

    T.reserve(K);
    for(int i = 0; i < K; i++) {
        int n, m;
        f >> n >> m;
        T.emplace_back(std::make_pair(n,m));
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

    for (int i=0 ; i<K ;i++){
        G[T[i].first][T[i].second]=1;
        G[T[i].second][T[i].first]=1;
    }
}
