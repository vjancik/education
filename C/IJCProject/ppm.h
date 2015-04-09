#ifndef PPM_H_
#define PPM_H_

#include <stdio.h>
#include <string.h>
#include "error.h"

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];
};

struct ppm * ppm_read(const char * filename);
int ppm_write(struct ppm *p, const char * filename);

#endif
