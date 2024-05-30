#ifndef EXCEPTION_H_INCLUDED
#define EXCEPTION_H_INCLUDED

#include <stdexcept>
#include <string>

class BaseException : public std::runtime_error {
public:
    explicit BaseException(const std::string& message)
        : std::runtime_error(message) {}
};

class SolverException : public BaseException {
public:
    explicit SolverException(const std::string& message)
        : BaseException(message) {}
};

class ParserException : public BaseException {
public:
    explicit ParserException(const std::string& message)
        : BaseException(message) {}
};

class CheckerException : public BaseException {
public:
    explicit CheckerException(const std::string& message)
        : BaseException(message) {}
};


#endif // EXCEPTION_H_INCLUDED
