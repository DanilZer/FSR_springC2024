#include "parser.h"


void Parser::Allocate() {
    if (N <= 0)
        return;
    if (K <=0)
        return;

}


void Parser::Clear() {

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


