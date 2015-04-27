#ifndef SHARED_H_
#define SHARED_H_

#include "util.h"

typedef struct {
    sem_t *outputMutex;
    sem_t *oxyQueue;
    sem_t *hydroQueue;
    sem_t *readMutex;
    sem_t *bondTurnstile;
    sem_t *bondTurnstile2;
    sem_t *bondMutex;
    sem_t *endTurnstile;
    sem_t *endTurnstile2;
    sem_t *endMutex;
    sem_t *finishedCountMutex;
    long oxyID;
    long hydroID;
    long oxyReady;
    long hydroReady;
    long atomNum;
    long actionNum;
    long oxyGenTime;
    long hydroGenTime;
    long bondTime;

    long bondCounter;
    long endCounter;

    FILE *outputFile;
} Shared;

void make_shared(Shared *shm, long atomNum, int hydroGenTime, int oxyGenTime, int bondTime);

void close_semaphores();

#endif
