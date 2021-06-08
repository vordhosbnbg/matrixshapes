#include <iostream>
#include <random>

void printHelp()
{
    std::cout << "Usage: generator num_cols num_rows fill_ratio" << std::endl;
}

int main(int argc, char** argv)
{
    if(argc == 4)
    {
        try
        {
            int cols = std::stoi(argv[1]);
            int rows = std::stoi(argv[2]);
            float fill_ratio = std::stof(argv[3]);

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> chance(0, 1) ;

            std::cout << cols << " " << rows << std::endl;
            for(int row = 0; row < rows; ++row)
            {
                for(int col = 0; col < cols; ++col)
                {
                    if(chance(gen) > fill_ratio)
                    {
                        std::putchar('0');
                    }
                    else
                    {
                        std::putchar('1');
                    }
                }
                std::putchar('\n');
            }

        }
        catch(std::exception& e)
        {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
    else
    {
        printHelp();
    }
    return 0;
}
