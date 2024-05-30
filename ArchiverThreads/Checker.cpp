#include "Checker.h"


bool Checker::Check(const std::string& file1, const std::string& file2) {
    std::ifstream f1(file1);
    std::ifstream f2(file2);

    if (!f1.is_open()) {
        throw CheckerException("Error: Couldn't open input file: " + file1);
    }

    if (!f2.is_open()) {
        throw CheckerException("Error: Couldn't open input file: " + file2);
    }

    char c1, c2;
    while (true) {
        f1.get(c1);
        f2.get(c2);

        if (f1.eof() || f2.eof()) {
            f1.close();
            f2.close();
            break;
        }

        if (c1 != c2) {
            throw CheckerException("Files differ at character: " + std::string(1, c1) + " vs " + std::string(1, c2));
        }
    }

    f1.close();
    f2.close();
    return true;
}
