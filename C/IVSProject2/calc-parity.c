#include <stdio.h>
#include "downloader.h"
#include "parity.h"

int main(int argc, char *argv[])
{
    int ret;
    if(argc==2) {
        printf("%hd\n", calc_parity(argv[1]));
        return 0;
    }
    for(int i=1;i<argc-1; i+=2) {
        ret = download_webpage(argv[i], argv[i+1]);
        if(ret==1)
            return 1;
        printf("%hd", calc_parity(argv[i+1]));
    }
    printf("\n");
    return 0;
}
