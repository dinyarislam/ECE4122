https://cuda-tutorial.readthedocs.io/en/latest/tutorials/tutorial01/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <cuda.h>
#include <cuda_runtime.h>

#define N 100000000

#define MAX_ERR 1e-6

//
// Kernel function that runs on the GPU
//
// Adds components of two vectors
//
__global__ void vector_add(float *out, float *a, float *b, int n) 
{
    
    for(int i = 0; i < n; i ++)
    {
        out[i] = a[i] + b[i];
    }
}
//
// Kernel function that runs on the GPU
//
int main()
{
    float *a, *b, *out;
    float *d_a, *d_b, *d_out; 

    // Allocate host memory
    a   = (float*)malloc(sizeof(float) * N);
    b   = (float*)malloc(sizeof(float) * N);
    out = (float*)malloc(sizeof(float) * N);

    // Initialize host arrays
    for(int i = 0; i < N; i++)
    {
        a[i] = 1.0f;
        b[i] = 2.0f;
    }

    // Allocate device memory
    // http://horacio9573.no-ip.org/cuda/group__CUDART__MEMORY_gc63ffd93e344b939d6399199d8b12fef.html#gc63ffd93e344b939d6399199d8b12fef
    cudaMalloc((void**)&d_a, sizeof(float) * N);
    cudaMalloc((void**)&d_b, sizeof(float) * N);
    cudaMalloc((void**)&d_out, sizeof(float) * N);

    // http://horacio9573.no-ip.org/cuda/group__CUDART__MEMORY_g48efa06b81cc031b2aa6fdc2e9930741.html
    // Transfer data from host to device memory
    cudaMemcpy(d_a, a, sizeof(float) * N, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, sizeof(float) * N, cudaMemcpyHostToDevice);

    // Executing kernel 
    vector_add<<<1,1>>>(d_out, d_a, d_b, N);
    
    // Transfer data back to host memory
    cudaMemcpy(out, d_out, sizeof(float) * N, cudaMemcpyDeviceToHost);

    // Verification
    for(int i = 0; i < N; i++){
        assert(fabs(out[i] - a[i] - b[i]) < MAX_ERR);
    }
    printf("out[0] = %f\n", out[0]);
    printf("PASSED\n");

    // Deallocate device memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_out);

    // Deallocate host memory
    free(a); 
    free(b); 
    free(out);
}
