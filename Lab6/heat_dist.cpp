/*
Author: Dinyar Islam
Class: ECE4122
Last Date Modified: 10 November 2022

Description: Lab 5

What is the purpose of this file?
OpenMPI program to determine the steady state heat distribution in a thin metal plate using synchronous iteration on a GPU.
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include "mpi.h"

using namespace std;


/*
The main method that uses OpenMPI to solve the steady state temperature
@param argc the number of command-line arguments
@param *argv[] pointer to array of arguments
*/
int main(int argc, char* argv[])
{
    int size, rank, ii, jj, kk;
    int index, up, down, left, right;

    // As always, we must call MPI_Init
    MPI_Init(&argc, &argv);

    // Get information about the number of tasks and which
    // rank this task is.
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // validation check for argument count
    if (argc != 5)
    {
        if (rank == 0)
        {
            std::cout << "Invalid Input!" << std::endl;
        }
        return 0;
    }

    // extract cmd line arguments
    std::string argStr_n;
    std::string argStr_limit;
    std::string arg_n = "-n";
    std::string arg_I = "-I";

    if (arg_n.compare(argv[1]) == 0 && arg_I.compare(argv[3]) == 0)
    {
        argStr_n = argv[2];
        argStr_limit = argv[4];
    }
    else if (arg_I.compare(argv[1]) == 0 && arg_n.compare(argv[3]) == 0)
    {
        argStr_n = argv[4];
        argStr_limit = argv[2];
    }
    else
    {
        if (rank == 0)
        {
            std::cout << "Invalid Input!" << std::endl;
        }
        return 0;
    }

    // std::cout<<argStr_n<<"\n";
    // std::cout<<argStr_limit<<"\n";

    // validation check for argument values
    for (int j = 0; j < argStr_n.length(); j++)
    {
        if (!isdigit(argStr_n[j])) //check if input has ASCII characters other than digits
        {
            if (rank == 0)
            {
                std::cout << "Invalid Input!" << std::endl;
            }
            return 0;
        }
    }
    for (int j = 0; j < argStr_limit.length(); j++)
    {
        if (!isdigit(argStr_limit[j])) //check if input has ASCII characters other than digits
        {
            if (rank == 0)
            {
                std::cout << "Invalid Input!" << std::endl;
            }
            return 0;
        }
    }
    int n = std::stoi(argStr_n);
    int limit = std::stoi(argStr_limit);
    if (n <= 0 | limit <= 0)
    {
        if (rank == 0)
        {
            std::cout << "Invalid Input!" << std::endl;
        }
        return 0;
    }

    // set width of mesh
    int width = n + 2;

    // allocate the oversized arrays to ensure each processor gets same amount of data
    int newWidth = size * (int)std::ceil((double)width / (double)size);
    int send_count = newWidth * newWidth / size;
    int recv_count = send_count;

    // start clock
    double start = MPI_Wtime();

    // Use a 1D array to represent a two dimensional array
    // array allocation
    double* h = new double[newWidth * newWidth];
    double* g = new double[newWidth * newWidth];

    int block_size = (newWidth / size);

    // initialize the arrays
    for (ii = 0; ii < width; ii++)
    {
        for (jj = 0; jj < width; jj++)
        {
            if (ii == 0 | jj == 0 | ii == width - 1 | jj == width - 1)
            {
                if (ii == 0 & (jj >= std::ceil(0.3 * (width - 1))) & (jj < std::ceil(0.7 * (width - 1))))
                {
                    h[ii * newWidth + jj] = 100;
                    g[ii * newWidth + jj] = 100;
                }
                else
                {
                    h[ii * newWidth + jj] = 20;
                    g[ii * newWidth + jj] = 20;
                }
            }
            else
            {
                h[ii * newWidth + jj] = 0;
                g[ii * newWidth + jj] = 0;
            }
        }
    }

    int startHere = rank * block_size;

    // calculate temperatures for internal points
    for (kk = 0; kk < limit; kk++)
    {
        for (ii = startHere; ii < startHere + block_size; ii++)
        {
            // skip first and last rows
            if (ii == 0 || ii >= width - 1)
                continue;
            for (jj = 0; jj < width; jj++)
            {
                // skip first and last columns
                if (jj == 0 || jj >= width - 1)
                    continue;
                index = ii * newWidth + jj;
                left = (ii-1) * newWidth + jj;
                right = (ii+1) * newWidth + jj;
                up = ii * newWidth + jj-1;
                down = ii * newWidth + jj+1;
                g[index] = 0.25 * (h[left] + h[right] + h[up] + h[down]);
                //g[index] = rank;
            }
        }
        MPI_Allgather(
            &g[startHere * newWidth],
            send_count,
            MPI_DOUBLE,
            h,
            recv_count,
            MPI_DOUBLE, MPI_COMM_WORLD
        );
    }
    // end clock
    double end = MPI_Wtime();
    double elapsedTime = (end - start) * 1000;

    if (rank == 0)
    {
        printf("Thin plate calculation took  %.3f milliseconds.\n", elapsedTime);

        // csv file output
        std::fstream fout;
        fout.open("finalTemperatures.csv", std::ios::out);
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < width; j++)
            {
                fout << std::fixed << std::setprecision(15) << h[(i * newWidth) + j] << ",";
            }
            fout << "\n";
            //std::cout<<"hello"<<"\n";
        }
        fout.close();

    }
    MPI_Finalize();

    return 0;
}

/*
PACE-ICE CMD:
mpic++ heat_dist.cpp
mpirun -np 50 ./a.out -n 16 -I 10000
*/