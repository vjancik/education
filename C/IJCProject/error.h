#ifndef ERROR_H_
#define ERROR_H_

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void Warning(const char *fmt, ...);
void FatalError(const char *fmt, ...);

#endif
