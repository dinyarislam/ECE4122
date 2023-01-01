/*
Author: Dinyar Islam
Class: ECE4122
Last Date Modified: 26 September 2022

Description: Lab 1 Problem 2

What is the purpose of this file?
The main file for the sudoku solver program that takes a text file as a command line argument that 
is the path to an input file, solves the sudoku grid(s) in the file and outputs the result.
*/

#include <iostream>
#include <thread>
#include <string>
#include <fstream>
#include <chrono>
#include <mutex>
#include <vector>
#include "sudokoSolver.h"
using namespace std;


std::mutex outFileMutex;
std::mutex inFileMutex;
std::fstream outFile;
std::fstream inFile; 

/*
Sudoku Grid class declaration
*/
class SudokuGrid
{
public:
    std::string m_strGridName; // sudoku grid name
    unsigned char gridElement[9][9]; //array for sudoku grid
    // constructor function
    SudokuGrid(){}

    // friend operator function for >> operator
    friend fstream& operator>>(fstream& os, SudokuGrid& gridIn);
    // friend operator function for << operator
    friend fstream& operator<<(fstream& os, const SudokuGrid& gridOut);
    
    /*
    The solve() function: This member function calls sudokuSolverDriver() function in the
    sudokoSolver.cpp file to actually solve the grid. It also carries out the necessary
    type conversions
    */
    void solve()
    {
        int intGrid[9][9];
        for (int ii = 0 ; ii < 9 ; ii++) // unsigned char to int converion of grid elements
        {
            for (int jj = 0 ; jj < 9 ; jj++)
            {
                std::string s(1, gridElement[ii][jj]);
                intGrid[ii][jj] = stoi(s, nullptr, 0);
            }
        }
        sudokuSolverDriver(intGrid, 0, 0);
        for (int ii = 0 ; ii < 9 ; ii++) // int to unsigned char converion of grid elements
        {
            for (int jj = 0 ; jj < 9 ; jj++)
            {
                gridElement[ii][jj] = (unsigned char) (intGrid[ii][jj] + 48);
            }
        }
    }
};

/*
operator>> function: reads a single SudokuGrid object from a fstream file.

@param os the fstream object pointer
@param gridIn the SudokuGrid object pointer
@return fstream object pointer
*/
fstream& operator>>(fstream& os, SudokuGrid& gridIn)
{
    // Read in the grid name
    std::getline(os, gridIn.m_strGridName);
    std::string strIn;
    for (int ii = 0 ; ii < 9 ; ii++)
    {
        std::getline(os, strIn);
        for (int jj = 0 ; jj < 9 ; jj++)
        {
            gridIn.gridElement[ii][jj] = strIn[jj];
        }

    }
    return os;
}

/*
operator<< function: writes the SudokuGrid object to a file in the same format that is used in 
reading in the object

@param os the fstream object pointer
@param gridIn the SudokuGrid object pointer
@return fstream object pointer
*/
fstream& operator<<(fstream& os, const SudokuGrid& gridOut)
{
    // Write out the grid name
    os << gridOut.m_strGridName << endl;
    for (int ii = 0 ; ii < 9 ; ii++)
    {
        for (int jj = 0 ; jj < 9 ; jj++)
        {
            if (jj == 8)
            {
                os << gridOut.gridElement[ii][jj] << endl;
            }
            else
            {
                os << gridOut.gridElement[ii][jj];
            }
        }

    }
    return os;
}

/*
The solveSudokuPuzzles() function: the function uses do-while loop to 
continue to read in and solve puzzles and then write out the solution 
until the end of the file is reached.
*/
void solveSudokuPuzzles()
{
    do
    {
        bool readFlag = false;
        inFileMutex.lock();
        SudokuGrid gridIn;
        if (!inFile.eof())
        {
            inFile >> gridIn;
            readFlag = true;
        }
        inFileMutex.unlock();

        if (readFlag)
        {
            gridIn.solve();
            outFileMutex.lock();
            outFile << gridIn;
            outFileMutex.unlock();
        }
    } while (!inFile.eof());
    return;
}

/*
The main function: The function dynamically determines the maximum number of threads 
(numThreads) that can run concurrently and spawn (numThreads-1) threads calling the 
function solveSudokuPuzzles(). 
*/
int main(int argc, char *argv[]) 
{
    // Validation check for number of args
    if (argc != 2)
    {
        cout << "Invalid Input!" << endl;
        return 0;
    }
    
    // Calculate the number of threads to spawn
    unsigned int numThreads;
    numThreads = std::thread::hardware_concurrency();

    //open files
    inFile.open(argv[1]);
    outFile.open("Lab2Prob2.txt", ios::out);
    if (!inFile || !outFile)
    {
        cout << "Failed to open file!" << endl;
        return 0;
    }

    std::vector<std::thread> threadObjects; // vector container for mult threads

    for (int ii = 0 ; ii < numThreads-1 ; ii++)
    {
        threadObjects.push_back(std::thread(solveSudokuPuzzles));
    }

    // call thread function inside the main
    solveSudokuPuzzles();

    // Wait for threads to finish
    for (int ii = 0 ; ii < numThreads-1 ; ii++)
    {
        threadObjects[ii].join();
    }

    //close files
    inFile.close();
    outFile.close();
    return 0;
}