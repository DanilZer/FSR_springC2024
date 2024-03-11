#include "parser.h"

double Dist(Point& A, Point& B) {
    double dx = A.X - B.X;
    double dy = A.Y - B.Y;
    return sqrt(dx * dx + dy * dy);
}


void Parser::Allocate() {
    if (N <= 0)
        return;

    P = new Point[N];
    G = new double*[N];

    for(int i=0; i<N; i++)
        G[i] = new double[N];
}


void Parser::Clear() {
    N = 0;

    if (P != NULL)
        delete [] P;

    if (G == NULL)
        return;

    for(int i=0; i<N; i++)
        if (G[i] != NULL)
            delete [] G[i];

    delete [] G;
}


void Parser::ParseFile(std::string Filename) {
    this->Clear();

    std::ifstream f;
    f.open(Filename);

    f >> N;
    this->Allocate();

    for(int i=0; i<N; i++)
        f >> P[i].X >> P[i].Y;

    f.close();
}

void Parser::FillMatrix() {
    if (N <= 0)
        return;

    if (G == NULL)
        return;

    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            G[i][j] = Dist(P[i], P[j]);
}
