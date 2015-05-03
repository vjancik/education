#ifndef SHARED_H_
#define SHARED_H_

#include "util.h"

//shared data structure
typedef struct {
    sem_t *outputMutex;
    sem_t *oxyQueue; //oxygen bonding queue
    sem_t *hydroQueue; //hydrogen bonding queue
    sem_t *readMutex; //mutex for reading counters
    //bond barrier semaphores
    sem_t *bondTurnstile;
    sem_t *bondTurnstile2;
    sem_t *bondMutex;
    //end barrier semaphores
    sem_t *endTurnstile;
    sem_t *endTurnstile2;
    sem_t *endMutex;

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
