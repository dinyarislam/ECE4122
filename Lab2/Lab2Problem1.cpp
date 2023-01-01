/*
Author: Dinyar Islam
Class: ECE4122
Last Date Modified: 10 October 2022

Description: Lab 2 Problem 1

What is the purpose of this file?
The program reads in two matrices (A & B) from a text file using a command line argument to specify the file path and name, and
multiples the two matrices together and outputs the multiplied matrix to a text file called MatrixOut.txt.
*/

#include <omp.h>
#include <sys/time.h>
#include <fstream>
#include <iostream>
#include <vector>

#define CHUNKSIZE 100

/*
The main function that reads in two matrices (A & B) from a text file using a command line argument to specify the file path and name, and
multiples the two matrices together and outputs the multiplied matrix to a text file called MatrixOut.txt.

@param argc the number of command-line arguments
@param *argv[] pointer to array of arguments
*/
int main(int argc, char *argv[]) 
{
    int i,j,k; // index variables
    int rows; // rows of input matrices
    int cols; // cols of input matrices
    int nRows, nCols; // dimension of product matrix
    std::ifstream fileIn; // input file
    std::ofstream fileOut; // output file

    // Validation check for number of args
    if (argc != 2)
    {
        std::cout << "Invalid Input!" << std::endl;
        return 0;
    }

    // open input and output files
    fileIn.open(argv[1]);
    fileOut.open("MatrixOut.txt", std::ios::out);
    if (!fileIn || !fileOut)
    {
        std::cout << "Failed to open file!" << std::endl;
        return 0;
    }

    // Reading first matrix (Matrix A) from file
    fileIn >> rows >> cols;
    nRows = rows; // assiging product matrix rows
    std::vector<std::vector<double>> matrixA(rows, std::vector<double> (cols, 0));
    int chunk = CHUNKSIZE;
//#pragma omp for schedule(dynamic, chunk)
        for (std::size_t i = 0; i < rows; i++)
        {
            for (std::size_t j = 0; j < cols; j++)
            {
                fileIn >> matrixA[i][j];
            }
        }

    // Reading second matrix (Matrix B) from file
    fileIn >> rows >> cols;
    nCols = cols; // assiging product matrix cols
    std::vector<std::vector<double>> matrixB(rows, std::vector<double> (cols, 0));

//#pragma omp for schedule(dynamic, chunk)
        for (std::size_t i = 0; i < rows; i++)
        {
            for (std::size_t j = 0; j < cols; j++)
            {
                fileIn >> matrixB[i][j];
            }
        }

    std::vector<std::vector<double>> matrixC(nRows, std::vector<double> (nCols, 0));
    //std::cout << "row: " << rows << "col: " << cols << "\n";
#pragma omp parallel shared(matrixA, matrixB, matrixC, rows, nRows, nCols, chunk) private(i, j, k)// Start of parallel region
    {
#pragma omp for schedule(dynamic, chunk) nowait
        for (i = 0; i < nRows; ++i)
        {
            for (j = 0; j < nCols; ++j)
            {
                for (k = 0; k < rows; ++k)
                {
                    matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
                }
            }
        }
    } /* end of parallel region */

    // Writing to file
    fileOut << nRows << " " << nCols << "\n";
    for (std::size_t i = 0; i < nRows; i++)
    {
        for (std::size_t j = 0; j < nCols; j++)
        {
            fileOut << matrixC[i][j] << " ";
        }
        fileOut << "\n";
    } 

    // printing matrices for debugging
    // for (const auto &row : matrixC)
    // {
    //     for (const auto elem : row)
    //     {
    //         std::cout << elem << " ";
    //     }
    //     std::cout << "\n";
    // }

    //close files
    fileIn.close();
    fileOut.close();
    return 0;
}
 