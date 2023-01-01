/*
Author: Dinyar Islam
Class: ECE4122
Last Date Modified: 26 September 2022

Description: Lab 1 Problem 1

What is the purpose of this file?
This file contains the main.cpp file for Lab 1 Problem 1, which validates the input arguments
and calls the numberGridPaths() function in the numberGridPaths.cpp file.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <climits>

uint64_t numberGridPaths(unsigned int nRows, unsigned int nCols);

/*
The main function: validates the input arguments and calls the numberGridPaths() function in the numberGridPaths.cpp file.
Finally it prints the number of paths or an error message to a text file based on the arguments.

@param argc argument Count:is int and stores number of command-line arguments passed by the user including the name of the program.
@param *argv argument vector: array of character pointers listing all the arguments.
@return 0
*/
int main(int argc, char *argv[])
{
    unsigned int nRows; //number of rows
    unsigned int nCols; //number of columns
    uint64_t numPaths; //number of paths
    bool invFlag = false; //flag for invalidity
    std::string argStr; //string type for argument values

    // validation checks for arguments entered by user
    if (argc != 3)
    {
        invFlag = true;
    }

    if (!invFlag)
    {
        for (int i = 1; i < argc; i++) 
        {
            argStr = argv[i];
            if (argStr.length() != 1)  //check single character argv value i.e. 1 and not 001
            {
                if (argStr[i] == '0')
                {
                    invFlag = true;
                    i = 3;
                }
                else
                {
                    for (int j = 0; j < argStr.length(); j++)
                    {
                        if (!isdigit(argStr[j])) //check if input has ASCII characters other than digits
                        {
                            invFlag = true;
                            i = 3;
                        }
                    }
                }
            }
            else if (!isdigit(*argv[i]))  //check if input has ASCII characters other than digits
            {
                invFlag = true;
                i = 3;
            }
            else if (int(*argv[i]) > INT_MAX || int(*argv[i]) < 0) //Is input a positive int? If not error message
            {
                invFlag = true;
                i = 3;
            }
        }
    }
    // file handling
    std::ofstream pathFile("NumberPaths.txt"); //open file
    if (invFlag)
    {
        pathFile << "Invalid Input!"; //write to file
        return 0;
    }
    nRows = std::stoul (argv[1],nullptr,0);
    nCols = std::stoul (argv[2],nullptr,0);
    numPaths = numberGridPaths(nRows, nCols); //function call to numberGridPaths()
    pathFile << "Total Number Paths: " << numPaths; //write to file
    pathFile.close(); //close file
    return 0;
}
