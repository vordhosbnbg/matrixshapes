#include <iostream>
#include "matrix.h"

int main(void)
{
    unsigned int cols;
    unsigned int rows;
    std::cin >> cols >> rows; std::cin.ignore();
    Matrix<unsigned char, unsigned char, unsigned short> mx(cols, rows);
    {
        std::string matrixData;
        matrixData.reserve(cols*rows);
        std::string line;
        for(int row = 0; row < rows; ++row)
        {
            std::getline(std::cin, line);
            matrixData.append(line);
        }
        mx.initFromString(matrixData);
    }

    unsigned int shapesNb = mx.findNbShapes();
    std::cout << shapesNb;

    return 0;
}
