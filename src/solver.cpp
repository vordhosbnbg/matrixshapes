#include <iostream>
#include "matrix.h"

int main(void)
{
    unsigned int cols;
    unsigned int rows;
    std::cin >> cols >> rows; std::cin.ignore();
    std::string matrixData;
    matrixData.reserve(cols*rows);
    std::string line;
    for(int row = 0; row < rows; ++row)
    {
        std::getline(std::cin, line);
        matrixData.append(line);
    }
    Matrix<int> mx(cols, rows);

    mx.initFromString(matrixData);
    std::cout << mx.at(5, 15);

    return 0;
}
