#include "error.h"

void Warning(const char *fmt, ...) {
    va_list argptr;
    va_start(argptr, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, argptr);
    va_end(argptr);
}

void FatalError(const char *fmt, ...) {
    va_list argptr;
    va_start(argptr, fmt);
    fprintf(stderr, "CHYBA: ");
    vfprintf(stderr, fmt, argptr);
    va_end(argptr);
    exit(1);
}
