#include "eratosthenes.h"
#include "bit-array.h"
#include <stdio.h>

void printPrimes(BitArray_t array) {
    unsigned long primes[10];
    int i=9;
    unsigned long bit = BA_size(array) - 1;
    while(bit >=0 && i>=0) {
        if(BA_get_bit(array, bit)==0) {
            primes[i]=bit;
            --i;
        }
        --bit;
    }

    for(int i=0; i<10; ++i) {
        printf("%lu\n", primes[i]);
    }
}

int main() {
    BA_create(array, 201000000);
    Eratosthenes(array);
    printPrimes(array);
    //for(int i=0;i<100;++i) {
    //    printf("%lu, ", BA_get_bit(array, i));
    //}
    return 0;
}

