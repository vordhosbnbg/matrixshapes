# matrixshapes 

This repo contains a generator and a solver.
The generator is used to create a random matrix X by Y tiles with a specific percentage of the tiles randomly filled with 1s
The solver takes the input of the generator output and outputs the number of individual shapes (graphs of connected nodes)

## Building
        cmake
        make
        
## Usage 

        ./generator num_cols num_rows fill_ratio > data.txt
        ./solver < data.txt
        
## Data format
First line has two numbers:
        ROWS COLUMNS
Next ROWS lines has COLUMNS number of 0s and 1s:
        0010101001100101010
        
