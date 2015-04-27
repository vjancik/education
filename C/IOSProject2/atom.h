#ifndef ATOM_H_
#define ATOM_H_

#include <errno.h>

#include "shared.h"
#include "util.h"

typedef enum {HYDROGEN, OXYGEN} atom_t;

typedef enum {STARTED, WAITING ,READY, BEGIN_B, END_B, FINISHED} status_t;

void output_status(Shared *shm, long *id, status_t status, atom_t atom);

void oxygen_logic(Shared *shm);

void hydrogen_logic(Shared *shm);

#endif
