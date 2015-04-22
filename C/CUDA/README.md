#CUDA Projects

This folder contains source files I completed for the assignments for the [Heterogeneous Parallel Programming](https://www.coursera.org/course/hetero) course on Coursera.

Each assignment demonstrates a different technique used in parallel programming.

###Files

**vecAdd.c**: Simple vector addition example.

**matrixMult.c**: Matrix multiplication example.

**tiledMM.c**: Tiled matrix multiplication example using shared memory.

**imgConvolution.c**: Image convolution example using both shared and constant memory. The code is fully implemented but has a bug I was unable to trace down.

**listReduction.c**: List reduction example.

**cudaStreams.c**: Implementation of vector addition using four CUDA streams to parallelize computation and data transfer.

**openCLVecAdd.c**: Basic openCL vector addition example.

**openACCVecAdd.c**: Basic openACC vector addition example.

**C++AMPVecAdd.cc**: Basic C++AMP vector addition example.

*Note: The online grader, for which the assignments were submitted used the [WebGPU](https://github.com/abduld/WebGPU) library as a wrapper for CUDA libraries.*
