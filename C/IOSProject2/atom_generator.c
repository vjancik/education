#include "atom_generator.h"

void generate_oxygen(Shared *shm) {
    pid_t pid;
    srand(time(NULL));
    for(int i=0;i<shm->atomNum;++i) {
        pid=fork();
        if(pid < 0)
            perror_exit("fork");
        else if (pid == 0) {
            oxygen_logic(shm);
            exit(0);
        }
        usleep(random_interval(shm->oxyGenTime));
    }
}


void generate_hydrogen(Shared *shm) {
    pid_t pid;
    srand(time(NULL));
    for(int i=0;i<(2*shm->atomNum);++i) {
        pid=fork();
        if(pid < 0)
            perror_exit("fork");
        else if (pid == 0) {
            hydrogen_logic(shm);
            exit(0);
        }
        usleep(random_interval(shm->hydroGenTime));
    }
}
