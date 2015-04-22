#include <wb.h>

int main(int argc, char **argv) {
  wbArg_t args;
  int inputLength;
  float *restrict hostInput1;
  float *restrict hostInput2;
  float *restrict hostOutput;

  args = wbArg_read(argc, argv);

  wbTime_start(Generic, "Importing data and creating memory on host");
  hostInput1 = (float *)wbImport(wbArg_getInputFile(args, 0), &inputLength);
  hostInput2 = (float *)wbImport(wbArg_getInputFile(args, 1), &inputLength);
  hostOutput = (float *)malloc(inputLength * sizeof(float));
  wbTime_stop(Generic, "Importing data and creating memory on host");

  wbLog(TRACE, "The input length is ", inputLength);

  #pragma acc parallel loop copyin(hostInput1[0:inputLength]) copyin(hostInput2[0:inputLength]) copyout(hostOutput[0:inputLength])
  for(int i = 0; i<inputLength; ++i) {
        hostOutput[i] = hostInput1[i] + hostInput2[i];
  }

  wbSolution(args, hostOutput, inputLength);

  free(hostInput1);
  free(hostInput2);
  free(hostOutput);

  return 0;
}
