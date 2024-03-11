#ifndef PARSER_H
#define PARSER_H

#include<fstream>
#include<cmath>

struct Point {
    double X;
    double Y;
};

double Dist(Point& A, Point& B);

class Parser{
public:
    Parser(): N(0), P(NULL), G(NULL) {};
    void Allocate();
    void Clear();
    ~Parser() {Clear();};
    void ParseFile(std::string Filename);
    void FillMatrix();
    int GetSize() {return N;};
    Point* GetPoints() {return P;};
    double** GetMatrix() {return G;};
private:
    int N;
    Point* P;
    double** G;
};

#endif // PARSER_H
