#pragma once

#include <array>
#include <string>
#include <algorithm>

template<class T>
class Matrix
{
public:
    Matrix(unsigned int x, unsigned int y) :
        cols(x),
        rows(y),
        matrixSize(x*y)
    {
        memory.resize(matrixSize);
    }

    bool initFromString(const std::string& input)
    {
        bool status = false;
        if(input.size() == matrixSize)
        {
            std::transform(input.begin(), input.end(), memory.begin(), [](const char& c)
            {
                return (T)(c - '0');
            });
        }
        return status;
    }

    inline T& at(unsigned int x, unsigned int y)
    {
        return memory[y*cols + x];
    }
private:
    unsigned int cols = 0;
    unsigned int rows = 0;
    size_t matrixSize = 0;
    std::vector<T> memory;
};
