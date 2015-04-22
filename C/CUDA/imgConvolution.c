#include    <wb.h>

#define MASK_WIDTH  5
#define MASK_RADIUS MASK_WIDTH/2
#define O_TILE_WIDTH 12
#define BLOCK_WIDTH (O_TILE_WIDTH+4)

//@@ INSERT CODE HERE

__global__ void convolution_2D_kernel(float *inputImage, float *outputImage, int width, int height, int channels, const float * __restrict__ mask) {

    __shared__ float sImage[BLOCK_WIDTH][BLOCK_WIDTH];

    int tx=threadIdx.x; int ty=threadIdx.y;
    int row_o = blockIdx.y*O_TILE_WIDTH + ty;
    int col_o = blockIdx.x*O_TILE_WIDTH + tx;
    int row_i = row_o - MASK_RADIUS;
    int col_i = col_o - MASK_RADIUS;
    int epsilon = 0.1;

    for(int channel=0;channel<channels;++channel) {
        if((row_i>=0) && (row_i < height) &&
           (col_i>=0) && (col_i < width)) {
            sImage[ty][tx] = inputImage[(row_i*width+col_i)*channels + channel];
        } else {
            sImage[ty][tx] = 0.0f;
        }

        __syncthreads();

        float output = 0.0f;

        if(ty < O_TILE_WIDTH && tx < O_TILE_WIDTH) {
            for(int i=0;i<MASK_WIDTH; ++i) {
                for(int j=0;j<MASK_WIDTH; ++j) {
                    output += mask[i*MASK_WIDTH+j]*sImage[i+ty][j+tx];
                }
            }

            __syncthreads();

            if(row_o<height && col_o < width) {
                outputImage[(row_o*width+col_o)*channels + channel] = output;
            }

            __syncthreads();
            //printf("%f ",output);
            //if((output<(0.274745+epsilon)&&output>(0.274745-epsilon))||(output<(0.486275+epsilon)&&output>(0.486275-epsilon))||(output==0.274745||output==0.486275))
            //  printf("BlockIdx.x:%d, BlockIdx.y:%d, ThreadIdx.x:%d, ThreadIdx.y:%d, Channel:%d, Value:%d\n", blockIdx.x, blockIdx.y, threadIdx.x, threadIdx.y, channel, output);
        }
        __syncthreads();
    }

}


int main(int argc, char* argv[]) {
    wbArg_t args;
    int maskRows;
    int maskColumns;
    int imageChannels;
    int imageWidth;
    int imageHeight;
    char * inputImageFile;
    char * inputMaskFile;
    wbImage_t inputImage;
    wbImage_t outputImage;
    float * hostInputImageData;
    float * hostOutputImageData;
    float * hostMaskData;
    float * deviceInputImageData;
    float * deviceOutputImageData;
    float * deviceMaskData;

    args = wbArg_read(argc, argv); /* parse the input arguments */

    inputImageFile = wbArg_getInputFile(args, 0);
    inputMaskFile = wbArg_getInputFile(args, 1);

    inputImage = wbImport(inputImageFile);
    hostMaskData = (float *) wbImport(inputMaskFile, &maskRows, &maskColumns);

    assert(maskRows == 5); /* mask height is fixed to 5 in this mp */
    assert(maskColumns == 5); /* mask width is fixed to 5 in this mp */

    imageWidth = wbImage_getWidth(inputImage);
    imageHeight = wbImage_getHeight(inputImage);
    imageChannels = wbImage_getChannels(inputImage);

    outputImage = wbImage_new(imageWidth, imageHeight, imageChannels);

    hostInputImageData = wbImage_getData(inputImage);
    hostOutputImageData = wbImage_getData(outputImage);

    wbTime_start(GPU, "Doing GPU Computation (memory + compute)");

    wbTime_start(GPU, "Doing GPU memory allocation");
    cudaMalloc((void **) &deviceInputImageData, imageWidth * imageHeight * imageChannels * sizeof(float));
    cudaMalloc((void **) &deviceOutputImageData, imageWidth * imageHeight * imageChannels * sizeof(float));
    cudaMalloc((void **) &deviceMaskData, maskRows * maskColumns * sizeof(float));
    wbTime_stop(GPU, "Doing GPU memory allocation");


    wbTime_start(Copy, "Copying data to the GPU");
    cudaMemcpy(deviceInputImageData,
               hostInputImageData,
               imageWidth * imageHeight * imageChannels * sizeof(float),
               cudaMemcpyHostToDevice);
    cudaMemcpy(deviceMaskData,
               hostMaskData,
               maskRows * maskColumns * sizeof(float),
               cudaMemcpyHostToDevice);
    wbTime_stop(Copy, "Copying data to the GPU");


    wbTime_start(Compute, "Doing the computation on the GPU");
    //@@ INSERT CODE HERE

    //for(int i=0; i<imageHeight; ++i){
    //  for(int j=0; j<imageWidth; ++j) {
    //      for(int channel=0; channel<3; ++channel) {
    //          printf("X:%d Y:%d Channel:%d = %f\n",i,j,channel,hostInputImageData[(i*imageWidth+j)*3+channel]);
    //      }
    //  }
    //  printf("\n");
    //}

    dim3 dimBlock(BLOCK_WIDTH, BLOCK_WIDTH, 1);
    dim3 dimGrid((imageWidth-1)/O_TILE_WIDTH+1,
                 (imageHeight-1)/O_TILE_WIDTH+1,1);

    convolution_2D_kernel<<<dimGrid,dimBlock>>>(deviceInputImageData, deviceOutputImageData, imageWidth, imageHeight, imageChannels, deviceMaskData);

    wbTime_stop(Compute, "Doing the computation on the GPU");


    wbTime_start(Copy, "Copying data from the GPU");
    cudaMemcpy(hostOutputImageData,
               deviceOutputImageData,
               imageWidth * imageHeight * imageChannels * sizeof(float),
               cudaMemcpyDeviceToHost);
    wbTime_stop(Copy, "Copying data from the GPU");

    outputImage->data = hostOutputImageData;

    wbTime_stop(GPU, "Doing GPU Computation (memory + compute)");

    wbSolution(args, outputImage);

    cudaFree(deviceInputImageData);
    cudaFree(deviceOutputImageData);
    cudaFree(deviceMaskData);

    free(hostMaskData);
    wbImage_delete(outputImage);
    wbImage_delete(inputImage);

    return 0;
}

