/*
Author: Dinyar Islam
Class: ECE4122
Last Date Modified: 26 September 2022

Description: Lab 1 Problem 1

What is the purpose of this file?
This file contains the numberGridPaths() function for Lab 1 Problem 1, which
calculates the total number of paths using the function prototype and returns that value.
*/

#include <iostream>
#include <string>
using namespace std;

/*
The numberGridPaths() function: a recursive function that calculates the total number of paths
by summation of two other previous function calls in the stack.

@param nRows number of rows
@param nCols number of columns
@return number of paths
*/

uint64_t numberGridPaths(unsigned int nRows, unsigned int nCols)
{
    if (nRows == 0 || nCols == 0) //If any of the maze dimensions are 0, no. of paths = 0
    {
        return 0;
    } 
    else if (nRows == 1 || nCols == 1) //If any of the maze dimensions are 1, no. of paths = 1
    {
        return 1;
    }
    else //Calculate the no. of paths using dynamic programming
    {
        uint64_t mazeGrid[nRows][nCols];

        //initialize the rest of the maze grid with zeroes
        for (int i = 0; i < nRows; i++)
        {
            for (int j = 0; j < nCols; j++)
            {
                mazeGrid[i][j] = 0;
            }
        }
        mazeGrid[0][0] = (uint64_t) 1;

        //recursively computes value maze[i][j] using dynamic programming
        uint64_t leftValue; //value one row to the left of the current index
        uint64_t aboveValue; //value one column above the current index
        for (int i = 0; i < nRows; i++)
        {
            for (int j = 0; j < nCols; j++)
            {
                leftValue = 0;
                aboveValue = 0;
                if ((j - 1) >= 0) {
                    leftValue = mazeGrid[i][j - 1];
                }
                if ((i - 1) >= 0) {
                    aboveValue = mazeGrid[i - 1][j];
                }
                if (mazeGrid[i][j] < (aboveValue + leftValue))
                {
                    mazeGrid[i][j] = aboveValue + leftValue;
                }
            }
        }
        
        return (mazeGrid[nRows-1][nCols-1]);
    }
}

