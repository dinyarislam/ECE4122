/*
Author: Dinyar Islam
Class: ECE4122
Last Date Modified: 10 November 2022

Description: Lab 4

What is the purpose of this file?
CUDA program to determine the steady state heat distribution in a thin metal plate using synchronous iteration on a GPU.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/*
The HANDLE_ERROR method
@param result
*/
inline cudaError_t HANDLE_ERROR(cudaError_t result)
{
#if defined(DEBUG) || defined(_DEBUG)
    if (result != cudaSuccess)
    {
        fprintf(stderr, "CUDA Runtime Error: %s\n", cudaGetErrorString(result));
        assert(result == cudaSuccess);
    }
#endif
    return result;
}

/*
The calculateTemp method is the kernal for calculating the temperature on each thread
@param h the memory address to the h array
@param g the memory address to the g array
@param limit the maximum number of iterations
@param n number of interior points 
*/
__global__
void calculateTemp(double* h, double* g, int n, int limit)
{
    // Calculate the column index of the Pd element, denote by x
    int y = threadIdx.x + blockIdx.x * blockDim.x;
    // Calculate the row index of the Pd element, denote by y
    int x = threadIdx.y + blockIdx.y * blockDim.y;

    // exit kernal if exterior point
    if (x <= 0 || x >= n+1 || y <= 0 || y >= n+1)
    {
        return;
    }
    else
    {
        g[y * (n+2) + x] = 0.25 * (h[(y-1) * (n+2) + x] + h[(y+1) * (n+2) + x] + h[y * (n+2) + x-1] + h[y * (n+2) + x+1]);
    }
}


/*
The main method that uses CUDA to solve the steady state temperature by calling the kernal above
@param argc the number of command-line arguments
@param *argv[] pointer to array of arguments
*/
int main(int argc, char* argv[])
{
    // validation check for argument count
    if (argc != 5)
    {
        std::cout << "Invalid Input!" << std::endl;
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
        std::cout << "Invalid Input!" << std::endl;
        return 0;
    }

    // std::cout<<argStr_n<<"\n";
    // std::cout<<argStr_limit<<"\n";

    // validation check for argument values
    for (int j = 0; j < argStr_n.length(); j++)
    {
        if (!isdigit(argStr_n[j])) //check if input has ASCII characters other than digits
        {
            std::cout << "Invalid Input!" << std::endl;
            return 0;
        }
    }
    for (int j = 0; j < argStr_limit.length(); j++)
    {
        if (!isdigit(argStr_limit[j])) //check if input has ASCII characters other than digits
        {
            std::cout << "Invalid Input!" << std::endl;
            return 0;
        }
    }
    int n = std::stoi(argStr_n);
    int limit = std::stoi(argStr_limit);
    if (n <= 0 | limit <= 0)
    {
        std::cout << "Incorrect value for n or I" << "\n";
        return 0;
    }


    // Use a 1D array to represent a two dimensional array
    int size = (n + 2) * (n + 2) * sizeof(double);
    double* h;
    double* g;

    // capture start time
    cudaEvent_t     start, stop;
    HANDLE_ERROR(cudaEventCreate(&start));
    HANDLE_ERROR(cudaEventCreate(&stop));
    HANDLE_ERROR(cudaEventRecord(start, 0));

    // allocate unified memory on the CPU and GPU (more streamlined than as device to host copying not required)
    HANDLE_ERROR(cudaMallocManaged((void**) &h, size));
    HANDLE_ERROR(cudaMallocManaged((void**) &g, size));

    // initialize the arrays
    for (int y = 0; y < n+2; y++)
    {
        for (int x = 0; x < n+2; x++)
        {
            if (y == 0 | x == 0 | y == n + 1 | x == n + 1)
            {
                if (y == 0 & (x >= std::round(0.3 * (n + 2))) & (x < std::round(0.7 * (n + 2))))
                {
                    h[y * (n+2) + x] = 100;
                    g[y * (n+2) + x] = 100;
                }
                else
                {
                    h[y * (n+2) + x] = 20;
                    g[y * (n+2) + x] = 20;
                }
            }
            else
            {
                h[y * (n+2) + x] = 0;
                g[y * (n+2) + x] = 0;
            }
        }
    }

    // kernel invocation code
    dim3 dimBlock(32, 32);
    dim3 dimGrid((n + 34) / 32, (n + 34) / 32);

    // std::cout<<n<<endl;
    // std::cout<<limit<<endl;

    // alternate between h and g to allow array copying
    for (int i = 0; i < limit; i++)
    {
        if (i % 2)
        {
            // for (int i = 0; i < (n + 2); i++)
            // {
            //     for (int j = 0; j < (n + 2); j++)
            //     {
            //         std::cout<<h[i*(n+2)+j]<<",";
            //     }
            //     std::cout<<"\n";
            // }
            //std::cout<<"hello"<<"\n";
            calculateTemp<<<dimGrid, dimBlock>>>(g, h, n, limit);
        }
        else
        {
            calculateTemp<<<dimGrid, dimBlock>>>(h, g, n, limit);
        }
        // Wait for GPU to finish before accessing on host
        cudaDeviceSynchronize();
    }

    // get stop time, and display the timing results
    HANDLE_ERROR(cudaEventRecord(stop, 0));
    HANDLE_ERROR(cudaEventSynchronize(stop));
    float   elapsedTime;
    HANDLE_ERROR(cudaEventElapsedTime(&elapsedTime, start, stop));
    printf("Thin plate calculation took  %.3f milliseconds\n", elapsedTime);

    // destroy events to free memory
    HANDLE_ERROR(cudaEventDestroy(start));
    HANDLE_ERROR(cudaEventDestroy(stop));


    // csv file output
    std::fstream fout;
    fout.open("finalTemperatures.csv", std::ios::out);
    for (int i = 0; i < n + 2; i++)
    {
        for (int j = 0; j < n + 2; j++)
        {
            fout << h[(i * (n + 2)) + j] << ", ";
        }
        fout << "\n";
        //std::cout<<"hello"<<"\n";
    }

    // free the memory allocated on the GPU
    HANDLE_ERROR(cudaFree(h));
    HANDLE_ERROR(cudaFree(g));

    return 0;
}

/*
PACE-ICE CMD:
module load gcc/9.2.0 cuda/11.1
nvcc *.cu -o main
*/