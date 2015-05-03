#include "shared.h"

//shared memory initialization function
void make_shared(Shared* shm, long atomNum, int hydroGenTime, int oxyGenTime, int bondTime) {
    shm->outputMutex = make_semaphore("/outputMutex",1);

    shm->oxyQueue = make_semaphore("/oxyQueue",0);
    shm->hydroQueue = make_semaphore("/hydroQueue",0);

    shm->readMutex = make_semaphore("/readMutex",1);

    shm->bondTurnstile = make_semaphore("/bondTurnstile", 0);
    shm->bondTurnstile2 = make_semaphore("/bondTurnstile2", 1);
    shm->bondMutex = make_semaphore("/bondMutex",1);

    shm->endTurnstile = make_semaphore("/endTurnstile", 0);
    shm->endTurnstile2 = make_semaphore("/endTurnstile2", 1);
    shm->endMutex = make_semaphore("/endMutex", 1);

    shm->oxyID = 1;
    shm->hydroID = 1;
    shm->oxyReady = 0;
    shm->hydroReady = 0;
    shm->atomNum = atomNum;
    shm->actionNum = 1;
    shm->oxyGenTime = oxyGenTime;
    shm->hydroGenTime = hydroGenTime;
    shm->bondTime = bondTime;

    shm->bondCounter = 0;
    shm->endCounter = 0;

    shm->outputFile = fopen("h2o.out", "w"); //output file
}

void close_semaphores() {
    sem_unlink("/outputMutex");

    sem_unlink("/oxyQueue");
    sem_unlink("/hydroQueue");

    sem_unlink("/readMutex");

    sem_unlink("/bondTurnstile");
    sem_unlink("/bondTurnstile2");
    sem_unlink("/bondMutex");

    sem_unlink("/endTurnstile");
    sem_unlink("/endTurnstile2");
    sem_unlink("/endMutex");
}
