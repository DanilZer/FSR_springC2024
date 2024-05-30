#ifndef SOLVER_H
#define SOLVER_H

#include <unordered_map>
#include <string>
#include <bitset>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstdio>

class Solver {
public:
    Solver(const std::unordered_map<char, std::bitset<5>>& alphabet, const std::unordered_map<std::bitset<5>, char>& antiAlphabet);
    void encodeFile(const std::string& inputFileName, const std::string& outputFileName, int NumThread);
    void decodeFile(const std::string& inputFileName, const std::string& outputFileName, int NumThread);
    int Get_Numchunk() {return NumChunk; };
private:
    int NumChunk;
    std::unordered_map<char, std::bitset<5>> alphabet;
    std::unordered_map<std::bitset<5>, char> antiAlphabet;

    std::bitset<16> encodeTriple(const std::string& triple);
    std::string decodeTriple(const std::bitset<16>& codetriple);

    void encodeChunk(const std::string& chunk, const std::string& outputFileName);
    void decodeChunk(const std::vector<uint16_t>& chunk, const std::string& outputFileName);

    static const int BITS_PER_CHAR = 5;
    static const int CHARS_PER_TRIPLE = 3;
    static const int BITS_PER_TRIPLE = CHARS_PER_TRIPLE * BITS_PER_CHAR + 1;
    static const int CHARS_PER_THREAD_ENCODE = 60000;
    static const int CHUNKS_PER_THREAD = CHARS_PER_THREAD_ENCODE*16;
};

#endif // SOLVER_H




