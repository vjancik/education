#include <stdio.h>
#include "ppm.h"
#include "bit-array.h"
#include "eratosthenes.h"


int main(int argc, const char *argv[])
{
    unsigned long msgi=0;
    BA_create(message, 4394304);
    char * msgp = (char *) &message[1];
    struct ppm * ppmFile = ppm_read(argv[1]);
    BA_create(array, 5000*5000*3);
    Eratosthenes(array);

    for(unsigned long i=0; i<ppmFile->xsize*ppmFile->ysize*3; ++i) {
        if(BA_get_bit(array,i)==0) {
            BA_set_bit(message,msgi,ppmFile->data[i]&1);
            ++msgi;
        }
    }
    while(*msgp!='\0') {
        printf("%c", *msgp);
        ++msgp;
    }
    printf("\n");

    free(ppmFile);
    return 0;
}
