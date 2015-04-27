#include "parity.h"

short count_ones(char character) {
    short parity = 0;
    for(short i=0; i<8; ++i) {
        parity^=(character>>i)&1;
    }
    return parity;
}

short calc_parity(char *filename) {
    char parity=0;
    long long size;
    char character;
    FILE *fp;
    fp = fopen(filename, "r");
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    for(long long i=0; i<size; ++i) {
        character=fgetc(fp);
        parity ^= character;
    }
    return count_ones(parity)%2;
}
