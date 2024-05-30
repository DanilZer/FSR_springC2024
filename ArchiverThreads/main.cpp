#include <iostream>
#include "Parser.h"
#include "Solver.h"
#include "Checker.h"
#include "Presentor.h"

int main() {
    //Presentor ThePresentor;
    //ThePresentor.input();
    //std::string filename = ThePresentor.getFilename();
    //std::string alphabetsName = ThePresentor.getAlphabetsName();
    //std::string ansName = ThePresentor.getAnsName();
    //int N = ThePresentor.getN();
    Parser TheParser;
    Checker TheChecker;
    TheParser.ParseAlphabet("alphabet.txt");
    //std::cout << "Размер Алфавита: " << TheParser.GetNalphabet() << std::endl;
    //std::cout << "Алфавит содержит:" << std::endl;
    //const auto& alphabet = TheParser.GetAlphabet();
    //for (const auto& el : alphabet) {
      //  std::cout << el.first << " " << el.second  << std::endl;
    //}
    Solver TheSolver(TheParser.GetAlphabet(),TheParser.GetAntiAlphabet());
    TheSolver.encodeFile("example.txt", "ans2.bin",4);
    TheSolver.decodeFile("ans2.bin" , "decodedans2.txt", 4);
    if (TheChecker.Check("example.txt", "decodedans2.txt")) {
        std::cout << "Files are equal." << std::endl;
    } else {
        std::cout << "Files are not equal." << std::endl;
    }

    return 0;
}
