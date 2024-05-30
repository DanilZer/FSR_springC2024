#include "Parser.h"


void Parser::ParseAlphabet(const std::string& AlphabetName) {
    std::ifstream f(AlphabetName);
    if (!f.is_open()) {
        throw ParserException("Error: Couldn't open input file: " + AlphabetName);
    }
    f >> N;
    if (N <= 0 || N > 32){
        throw ParserException("Error: N can't be " + std::to_string(N));
    }

    std::string line;
    std::getline(f, line);

    for (int i = 0; i < N; i++) {
        std::getline(f, line);
        char c;
        std::bitset<5> s;
        std::istringstream iss(line);
        iss >> c >> s;
        if (c == '#'){
            alphabet.emplace(' ', s);
            antialphabet.emplace(s, ' ');
            continue;
        }
        if (c == '$'){
            alphabet.emplace('\n', s);
            antialphabet.emplace(s, '\n');
            continue;
        }
        alphabet.emplace(c, s);
        antialphabet.emplace(s,c);
    }

    f.close();
}
