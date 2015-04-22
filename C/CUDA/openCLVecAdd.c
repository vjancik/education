#include <wb.h> //@@ wb include opencl.h for you

const char *vaddsrc = "\n" \
    "__kernel void vadd(__global float *d_A, __global float *d_B, __global float *d_C, int N) {\n" \
    "   int id = get_global_id(0);                                                             \n" \
    "   if (id < N)                                                                            \n" \
    "       d_C[id] = d_A[id] + d_B[id];                                                       \n" \
    "}                                                                                         \n";
//@@ OpenCL Kernel

int main(int argc, char **argv) {
  wbArg_t args;
  int inputLength;
  float *hostInput1;
  float *hostInput2;
  float *hostOutput;

  cl_mem d_A;
  cl_mem d_B;
  cl_mem d_C;
  int size;

  cl_platform_id cpPlatform;        // OpenCL platform
  cl_device_id device_id;           // device ID
  cl_context context;               // context
  cl_command_queue queue;           // command queue
  cl_program program;               // program
  cl_kernel kernel;

  args = wbArg_read(argc, argv);

  wbTime_start(Generic, "Importing data and creating memory on host");
  hostInput1 = ( float * )wbImport(wbArg_getInputFile(args, 0), &inputLength);
  hostInput2 = ( float * )wbImport(wbArg_getInputFile(args, 1), &inputLength);
  hostOutput = ( float * )malloc(inputLength * sizeof(float));
  wbTime_stop(Generic, "Importing data and creating memory on host");

  wbLog(TRACE, "The input length is ", inputLength);

  size = inputLength*sizeof(float);

  cl_int clerr = CL_SUCCESS;

  clerr = clGetPlatformIDs(1, &cpPlatform, NULL);
  clerr = clGetDeviceIDs(cpPlatform, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL);
  context = clCreateContext(0, 1, &device_id, NULL, NULL, &clerr);
  queue = clCreateCommandQueue(context, device_id, 0, &clerr);
  program = clCreateProgramWithSource(context, 1, (const char **) & vaddsrc, NULL, &clerr);
  clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
  kernel = clCreateKernel(program, "vadd", &clerr);

  wbTime_start(GPU, "Allocating GPU memory.");
  //@@ Allocate GPU memory here

  d_A = clCreateBuffer(context, CL_MEM_READ_ONLY, size, NULL, NULL);
  d_B = clCreateBuffer(context, CL_MEM_READ_ONLY, size, NULL, NULL);
  d_C = clCreateBuffer(context, CL_MEM_WRITE_ONLY, size, NULL, NULL);

  wbTime_stop(GPU, "Allocating GPU memory.");

  wbTime_start(GPU, "Copying input memory to the GPU.");
  //@@ Copy memory to the GPU here

  clerr = clEnqueueWriteBuffer(queue, d_A, CL_TRUE, 0, size, hostInput1, 0, NULL, NULL);
  clerr |= clEnqueueWriteBuffer(queue, d_B, CL_TRUE, 0, size, hostInput2, 0, NULL, NULL);

  clerr = clSetKernelArg(kernel, 0, sizeof(cl_mem),(void *)&d_A);
  clerr = clSetKernelArg(kernel, 1, sizeof(cl_mem),(void *)&d_B);
  clerr = clSetKernelArg(kernel, 2, sizeof(cl_mem),(void *)&d_C);
  clerr = clSetKernelArg(kernel, 3, sizeof(int),&inputLength);

  wbTime_stop(GPU, "Copying input memory to the GPU.");

  //@@ Initialize the grid and block dimensions here

  size_t globalSize, localSize;
  localSize = 256;
  globalSize = ((inputLength-1)/localSize + 1)*localSize;

  wbTime_start(Compute, "Performing CUDA computation");
  //@@ Launch the GPU Kernel here

  cl_event event=NULL;
  clerr = clEnqueueNDRangeKernel(queue, kernel, 1, NULL, &globalSize, &localSize, 0, NULL, NULL);
  clFinish(queue);

  wbTime_stop(Compute, "Performing CUDA computation");

  wbTime_start(Copy, "Copying output memory to the CPU");
  //@@ Copy the GPU memory back to the CPU here

  clEnqueueReadBuffer(queue, d_C, CL_TRUE, 0, size, hostOutput, 0, NULL, NULL );

  wbTime_stop(Copy, "Copying output memory to the CPU");

  wbTime_start(GPU, "Freeing GPU Memory");
  //@@ Free the GPU memory here

  wbTime_stop(GPU, "Freeing GPU Memory");

  wbSolution(args, hostOutput, inputLength);

  clReleaseMemObject(d_A);
  clReleaseMemObject(d_B);
  clReleaseMemObject(d_C);
  clReleaseProgram(program);
  clReleaseKernel(kernel);
  clReleaseCommandQueue(queue);
  clReleaseContext(context);

  free(hostInput1);
  free(hostInput2);
  free(hostOutput);

  return 0;
}
