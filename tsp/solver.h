#ifndef SOLVER_H
#define SOLVER_H

#include<cstddef>
#include<utility>
#include<iostream>

struct Edge{
    int From;
    int To;
};

class Solver{
public:
    Solver(): N(0), G(NULL), Path(NULL) {};
    Solver(int Size, double** Matrix): N(Size), G(Matrix)
        {Path = new int[N+1];};
    void SetData(int Size, double** Matrix);
    void Clear();
    ~Solver() {Clear();};
    void Solve();
    int GetSize() {return N;};
    int* GetPath() {return Path;};
    double GetPathLen() {return PathLen;};
private:
    int N;
    double** G;
    int* Path;
    double PathLen;
    void CheckPath(int i, int j);
    void PrithPath();
};

#endif // SOLVER_H
