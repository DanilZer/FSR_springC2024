#ifndef PARSER_H
#define PARSER_H

#include<fstream>
#include <algorithm>
#include <vector>
#include <utility>

class Parser{
public:
    Parser(): N(0), T(NULL), G(NULL) {};
    void Allocate();
    void Clear();
    ~Parser() {Clear();};
    void ParseFile(std::string Filename);
    void FillMatrix();
    int GetNum() {return N;};
    int GetNumEdges() {return K;};
    std::vector<std::pair<int, int>>& GetEdges() {return T;};
    int** GetMatrix() {return G;};
private:
    int N;
    int K;
    std::vector<std::pair<int, int>> T;
    int** G;
};

#endif // PARSER_H
