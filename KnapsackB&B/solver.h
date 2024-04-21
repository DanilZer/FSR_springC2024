#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>

class Solver {
public:
    Solver(): N(0), K(0), MaxValue(0) {}
    Solver(int Size, int Volume, const std::vector<std::pair<int, int>>& things);
    void SetData(int Size, int Volume, const std::vector<std::pair<int, int>>& things);
    void Clear();
    ~Solver() { Clear(); };
    std::pair<int, std::vector<int>> Solve();
    int GetSize() { return N; };
    int GetMaxValue() { return MaxValue; };
    void BAndB(int level, int cur_w, int cur_v, int BV);
    int calculateBound(int level, int cur_w, int current_v);
private:
    int N;
    int K;
    std::vector<std::pair<int, int>> things;
    int MaxValue;
    std::vector<int> cur_items;
    std::vector<int> best_items;
    std::vector<int> original_indices;
};

#endif // SOLVER_H
