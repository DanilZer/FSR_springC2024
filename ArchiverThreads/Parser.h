#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <fstream>
#include <unordered_map>
#include <sstream>
#include <cstdint>
#include <bitset>
#include "Exception.h"

class Parser {
public:
    Parser(): N(0) {};
    ~Parser() {};
    void ParseAlphabet(const std::string& AlphabetName);
    int GetNalphabet() const { return N; };
    const std::unordered_map<char, std::bitset<5>>& GetAlphabet() const { return alphabet; };
    const std::unordered_map<std::bitset<5>, char>& GetAntiAlphabet() const { return antialphabet; };
private:
    int N;
    std::unordered_map<char, std::bitset<5>> alphabet;
    std::unordered_map<std::bitset<5> , char> antialphabet;
};
#endif // PARSER_H_INCLUDED
