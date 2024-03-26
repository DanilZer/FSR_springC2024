#ifndef SOLVER_H
#define SOLVER_H

#include<cstddef>
#include<utility>
#include <vector>
#include<iostream>

class Solver{
public:
    Solver(): N(0), K(0), G(nullptr), Colors(nullptr),AvailableColors(nullptr), ans(0) {}
    Solver(int Size, int Volume, int** Matrix):
        N(Size), K(Volume), G(Matrix),Colors(new int[Size]),AvailableColors(new int[Size]), ans(0) {}
    void SetData(int Size, int Volume, int** Matrix);
    void Clear();
    ~Solver() {Clear();};
    void Solve();
    void FindMax();
    int GetNum() {return N;};
    int* GetColors() {return Colors;};
    int GetMaxans() {return ans;};
private:
    int N;
    int K;
    int** G;
    int* Colors;
    int* AvailableColors;
    int ans;
};

#endif // SOLVER_H
