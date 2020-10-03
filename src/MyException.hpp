#pragma once

#include <exception>

class MyException : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Invalid mode.";
    }
};