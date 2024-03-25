#ifndef SOLVER_H
#define SOLVER_H

#include<cstddef>
#include<utility>
#include <vector>
#include<iostream>

class Solver{
public:
    Solver(): N(0), K(0), G(nullptr), ans(nullptr), MaxValue(0) {}
    Solver(int Size, int Volume, int** Matrix, const std::vector<std::pair<int, int>>*  things):
        N(Size), K(Volume), G(Matrix), T(things), ans(new int[Size]), MaxValue(0) {}
    void SetData(int Size, int Volume, int** Matrix, const std::vector<std::pair<int, int>>* things);
    void Clear();
    ~Solver() {Clear();};
    void Solve();
    void FindThings(int i, int j);
    int GetSize() {return N;};
    int* Getans() {return ans;};
    int GetMaxValue() {return MaxValue;};
private:
    int N;
    int K;
    int** G;
    const std::vector<std::pair<int, int>>* T;
    int* ans;
    int MaxValue;
    int ResSpace;
};

#endif // SOLVER_H
