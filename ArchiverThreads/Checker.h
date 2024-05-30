#ifndef CHECKER_H_INCLUDED
#define CHECKER_H_INCLUDED

#include <fstream>
#include <string>
#include <iostream>
#include "Exception.h"

class Checker {
public:
    Checker() {}
    bool Check(const std::string& file1, const std::string& file2);
};

#endif // CHECKER_H_INCLUDED
