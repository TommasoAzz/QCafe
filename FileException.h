#ifndef FILEEXCEPTION_H
#define FILEEXCEPTION_H
#include <iostream>
#include <exception>

class FileException: public std::exception {
public:
    static const bool INPUT = true;
    static const bool OUTPUT = false;
    FileException(bool, const std::string&);
    virtual const char* what() const noexcept; // noexcept restituisce true a compile-time se non ci sono istruzioni che portano a errori a run-time
    bool io_mode() const;
private:
    bool io; // true = input, false = output;
    std::string error_message;
};

#endif // FILEEXCEPTION_H
