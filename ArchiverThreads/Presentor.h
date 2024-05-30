#ifndef PRESENTOR_H_INCLUDED
#define PRESENTOR_H_INCLUDED

#include <iostream>
#include <string>

class Presentor {
public:
    Presentor() {}

    void input() {
        std::cout << "Enter the filename: ";
        std::cin >> Filename;
        std::cout << "Enter the alphabets filename: ";
        std::cin >> AlphabetsName;
        std::cout << "Enter the answers filename: ";
        std::cin >> ansName;
        std::cout << "Enter the Number of Threads: ";
        std::cin >> N;
    }

    std::string getFilename() const {
        return Filename;
    }

    std::string getAlphabetsName() const {
        return AlphabetsName;
    }

    std::string getAnsName() const {
        return ansName;
    }

    int getN() const{
        return N;
    }

private:
    std::string Filename;
    std::string AlphabetsName;
    std::string ansName;
    int N;
};

#endif // PRESENTOR_H_INCLUDED
