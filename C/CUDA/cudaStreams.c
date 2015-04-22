#include  <wb.h>

__global__ void vecAdd(float * in1, float * in2, float * out, int len) {
    //@@ Insert code to implement vector addition here
    int i = threadIdx.x+blockDim.x*blockIdx.x;
    if(i<len) out[i] = in1[i] + in2[i];
}

int remLength(int blockSize, int offset, int length) {
    int size = ((blockSize+offset)<= length) ? blockSize : (length  - blockSize+offset);
    return (size>0) ? size : 0;
}

int main(int argc, char ** argv) {
    wbArg_t args;
    int inputLength;
    float * hostInput1;
    float * hostInput2;
    float * hostOutput;
    cudaStream_t stream0, stream1, stream2, stream3;
    float *d_A0, *d_B0, *d_C0;
    float *d_A1, *d_B1, *d_C1;
    float *d_A2, *d_B2, *d_C2;
    float *d_A3, *d_B3, *d_C3;
    int SegSize = 256;

    args = wbArg_read(argc, argv);

    wbTime_start(Generic, "Importing data and creating memory on host");
    hostInput1 = (float *) wbImport(wbArg_getInputFile(args, 0), &inputLength);
    hostInput2 = (float *) wbImport(wbArg_getInputFile(args, 1), &inputLength);
    hostOutput = (float *) malloc(inputLength * sizeof(float));

    cudaMalloc((void**) &d_A0, 256*sizeof(float));
    cudaMalloc((void**) &d_A1, 256*sizeof(float));
    cudaMalloc((void**) &d_A2, 256*sizeof(float));
    cudaMalloc((void**) &d_A3, 256*sizeof(float));
    cudaMalloc((void**) &d_B0, 256*sizeof(float));
    cudaMalloc((void**) &d_B1, 256*sizeof(float));
    cudaMalloc((void**) &d_B2, 256*sizeof(float));
    cudaMalloc((void**) &d_B3, 256*sizeof(float));
    cudaMalloc((void**) &d_C0, 256*sizeof(float));
    cudaMalloc((void**) &d_C1, 256*sizeof(float));
    cudaMalloc((void**) &d_C2, 256*sizeof(float));
    cudaMalloc((void**) &d_C3, 256*sizeof(float));

    cudaStreamCreate(&stream0);
    cudaStreamCreate(&stream1);
    cudaStreamCreate(&stream2);
    cudaStreamCreate(&stream3);

    wbTime_stop(Generic, "Importing data and creating memory on host");

    for(int i=0; i<inputLength; i+=SegSize*4) {
        cudaStreamSynchronize(stream0);
        cudaStreamSynchronize(stream1);

        cudaMemcpyAsync(d_A0, hostInput1+i, remLength(SegSize, i, inputLength)*sizeof(float),cudaMemcpyHostToDevice, stream0);
        cudaMemcpyAsync(d_B0, hostInput2+i, remLength(SegSize, i, inputLength)*sizeof(float),cudaMemcpyHostToDevice, stream0);

        cudaMemcpyAsync(d_A1, hostInput1+i+SegSize, remLength(SegSize, i+SegSize, inputLength)*sizeof(float),cudaMemcpyHostToDevice, stream1);
        cudaMemcpyAsync(d_B1, hostInput2+i+SegSize, remLength(SegSize, i+SegSize, inputLength)*sizeof(float),cudaMemcpyHostToDevice, stream1);

        cudaStreamSynchronize(stream0);
        cudaStreamSynchronize(stream1);

        vecAdd<<<1, 256, 0, stream0>>>(d_A0, d_B0, d_C0, remLength(SegSize, i, inputLength));
        vecAdd<<<1, 256, 0, stream1>>>(d_A1, d_B1, d_C1, remLength(SegSize, i+SegSize, inputLength));

        cudaStreamSynchronize(stream0);
        cudaStreamSynchronize(stream1);

        cudaMemcpyAsync(hostOutput+i, d_C0, remLength(SegSize, i, inputLength)*sizeof(float),cudaMemcpyDeviceToHost, stream0);
        cudaMemcpyAsync(hostOutput+i+SegSize, d_C1, remLength(SegSize, i+SegSize, inputLength)*sizeof(float),cudaMemcpyDeviceToHost, stream1);

        cudaStreamSynchronize(stream2);
        cudaStreamSynchronize(stream3);

        cudaMemcpyAsync(d_A2, hostInput1+i+SegSize*2, remLength(SegSize, i+SegSize*2, inputLength)*sizeof(float),cudaMemcpyHostToDevice, stream2);
        cudaMemcpyAsync(d_B2, hostInput2+i+SegSize*2, remLength(SegSize, i+SegSize*2, inputLength)*sizeof(float),cudaMemcpyHostToDevice, stream2);

        cudaMemcpyAsync(d_A3, hostInput1+i+SegSize*3, remLength(SegSize, i+SegSize*3, inputLength)*sizeof(float),cudaMemcpyHostToDevice, stream3);
        cudaMemcpyAsync(d_B3, hostInput2+i+SegSize*3, remLength(SegSize, i+SegSize*3, inputLength)*sizeof(float),cudaMemcpyHostToDevice, stream3);

        cudaStreamSynchronize(stream2);
        cudaStreamSynchronize(stream3);

        vecAdd<<<1, 256, 0, stream2>>>(d_A2, d_B2, d_C2, remLength(SegSize, i+SegSize*2, inputLength));
        vecAdd<<<1, 256, 0, stream3>>>(d_A3, d_B3, d_C3, remLength(SegSize, i+SegSize*3, inputLength));

        cudaStreamSynchronize(stream2);
        cudaStreamSynchronize(stream3);

        cudaMemcpyAsync(hostOutput+i+SegSize*2, d_C2, remLength(SegSize, i+SegSize*2, inputLength)*sizeof(float),cudaMemcpyDeviceToHost, stream2);
        cudaMemcpyAsync(hostOutput+i+SegSize*3, d_C3, remLength(SegSize, i+SegSize*3, inputLength)*sizeof(float),cudaMemcpyDeviceToHost, stream3);

    }

    cudaDeviceSynchronize();

    wbSolution(args, hostOutput, inputLength);

    cudaFree(d_A0);
    cudaFree(d_A1);
    cudaFree(d_A2);
    cudaFree(d_A3);
    cudaFree(d_B0);
    cudaFree(d_B1);
    cudaFree(d_B2);
    cudaFree(d_B3);
    cudaFree(d_C0);
    cudaFree(d_C1);
    cudaFree(d_C2);
    cudaFree(d_C3);

    free(hostInput1);
    free(hostInput2);
    free(hostOutput);

    return 0;
}
