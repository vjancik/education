#include "atom.h"

void barrier_phase1(sem_t *mutex, sem_t *turnstile, sem_t *turnstile2, long *counter, long size) {
    sem_wait(mutex);
    ++(*counter);
    if(*counter==size) {
        sem_wait(turnstile2);
        sem_signal(turnstile);
    }
    sem_signal(mutex);

    sem_wait(turnstile);
    sem_signal(turnstile);
}

void barrier_phase2(sem_t *mutex, sem_t *turnstile, sem_t* turnstile2, long *counter, long size) {
    sem_wait(mutex);
    --(*counter);
    if(*counter==0) {
        sem_wait(turnstile);
        sem_signal(turnstile2);
    }
    sem_signal(mutex);

    sem_wait(turnstile2);
    sem_signal(turnstile2);
}

void output_status(Shared *shm, long *id, status_t status, atom_t atom) {
    sem_wait(shm->outputMutex);
    char atomChar = 'H';
    if(atom==OXYGEN) atomChar = 'O';
    FILE *file = shm->outputFile;
    switch(status) {
        case STARTED:
            if(atom==HYDROGEN) {
                *id = shm->hydroID;
                ++(shm->hydroID);
            }
            else {
                *id = shm->oxyID;
                ++(shm->oxyID);
            }
            fprintf(file, "%ld\t: %c %ld\t: started\n", shm->actionNum, atomChar, *id);
            break;
        case WAITING:
            fprintf(file, "%ld\t: %c %ld\t: waiting\n", shm->actionNum, atomChar, *id);
            break;
        case READY:
            fprintf(file, "%ld\t: %c %ld\t: ready\n", shm->actionNum, atomChar, *id);
            break;
        case BEGIN_B:
            fprintf(file, "%ld\t: %c %ld\t: begin bonding\n", shm->actionNum, atomChar, *id);
            break;
        case END_B:
            fprintf(file, "%ld\t: %c %ld\t: bonded\n", shm->actionNum, atomChar, *id);
            break;
        case FINISHED:
            fprintf(file, "%ld\t: %c %ld\t: finished\n", shm->actionNum, atomChar, *id);
            break;
        default:
            break;
    }
    fflush(shm->outputFile);
    ++(shm->actionNum);
    sem_signal(shm->outputMutex);
}

void oxygen_logic(Shared *shm) {
    long atomID;
    output_status(shm, &atomID, STARTED, OXYGEN);

    sem_wait(shm->readMutex);
    ++(shm->oxyReady);
    if (shm->hydroReady >= 2) {
        output_status(shm, &atomID, READY, OXYGEN);
        sem_signal(shm->hydroQueue);
        sem_signal(shm->hydroQueue);
        shm->hydroReady -= 2;
        sem_signal(shm->oxyQueue);
        shm->oxyReady -= 1;
    } else {
        output_status(shm, &atomID, WAITING, OXYGEN);
        sem_signal(shm->readMutex);
    }

    sem_wait(shm->oxyQueue);
    //bond
    output_status(shm, &atomID, BEGIN_B, OXYGEN);
    usleep(random_interval(shm->bondTime));

    barrier_phase1(shm->bondMutex, shm->bondTurnstile, shm->bondTurnstile2, &(shm->bondCounter), 3);
    output_status(shm, &atomID, END_B, OXYGEN);
    barrier_phase2(shm->bondMutex, shm->bondTurnstile, shm->bondTurnstile2, &(shm->bondCounter), 3);

    sem_signal(shm->readMutex);

    barrier_phase1(shm->endMutex, shm->endTurnstile, shm->endTurnstile2, &(shm->endCounter), 3*(shm->atomNum));
    output_status(shm, &atomID, FINISHED, OXYGEN);
}

void hydrogen_logic(Shared *shm) {
    long atomID;
    output_status(shm, &atomID, STARTED, HYDROGEN);

    sem_wait(shm->readMutex);
    ++(shm->hydroReady);
    if (shm->hydroReady >= 2 && shm->oxyReady >= 1) {
        output_status(shm, &atomID, READY, HYDROGEN);
        sem_signal(shm->hydroQueue);
        sem_signal(shm->hydroQueue);
        shm->hydroReady -= 2;
        sem_signal(shm->oxyQueue);
        shm->oxyReady -= 1;
    } else {
        output_status(shm, &atomID, WAITING, HYDROGEN);
        sem_signal(shm->readMutex);
    }

    sem_wait(shm->hydroQueue);
    //bond
    output_status(shm, &atomID, BEGIN_B, HYDROGEN);
    usleep(random_interval(shm->bondTime));

    barrier_phase1(shm->bondMutex, shm->bondTurnstile, shm->bondTurnstile2, &(shm->bondCounter), 3);
    output_status(shm, &atomID, END_B, HYDROGEN);
    barrier_phase2(shm->bondMutex, shm->bondTurnstile, shm->bondTurnstile2, &(shm->bondCounter), 3);

    barrier_phase1(shm->endMutex, shm->endTurnstile, shm->endTurnstile2, &(shm->endCounter), 3*(shm->atomNum));
    output_status(shm, &atomID, FINISHED, HYDROGEN);
}
