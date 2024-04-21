#include "Solver.h"

Solver::Solver(int Size, int Volume, const std::vector<std::pair<int, int>>& things)
    : N(Size), K(Volume), things(things), MaxValue(0) {}

void Solver::SetData(int Size, int Volume, const std::vector<std::pair<int, int>>& things) {
    N = Size;
    K = Volume;
    this->things = things;
}

void Solver::Clear() {
    N = 0;
    K = 0;
    MaxValue = 0;
    cur_items.clear();
    best_items.clear();
    original_indices.clear();
}

std::pair<int, std::vector<int>> Solver::Solve() {
    cur_items.resize(N, 0);
    original_indices.resize(N);
    for (int i = 0; i < N; ++i) {
        original_indices[i] = i;
    }
    BAndB(0, 0, 0, calculateBound(0, 0, 0));
    std::vector<int> real_indices;
    for (int i = 0; i < N; ++i) {
        if (best_items[i] == 1) {
            real_indices.push_back(original_indices[i]);
        }
    }
    return { MaxValue, real_indices };
}

void Solver::BAndB(int level, int cur_w, int cur_v, int BV) {
    if (level == N || cur_w > K)
        return;

    if (cur_v + BV <= MaxValue)
        return;

    if (cur_w + things[level].second <= K) {
        cur_items[level] = 1;
        if (cur_v + things[level].first > MaxValue) {
            MaxValue = cur_v + things[level].first;
            best_items = cur_items;
        }
        BAndB(level + 1, cur_w + things[level].second, cur_v + things[level].first, calculateBound(level + 1, cur_w + things[level].second, cur_v + things[level].first));
        cur_items[level] = 0;
    }

    BAndB(level + 1, cur_w, cur_v, calculateBound(level + 1, cur_w, cur_v));
}

int Solver::calculateBound(int level, int cur_w, int cur_v) {
    int weight = cur_w;
    int value = cur_v;

    for (int i = level; i < N && weight <= K; ++i) {
        if (weight + things[i].second <= K) {
            weight += things[i].second;
            value += things[i].first;
        } else {
            value += (K - weight) * (things[i].first / double(things[i].second));
            break;
        }
    }

    return value - cur_v;
}





