#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

#include "util.h"
#include "shared.h"
#include "atom_generator.h"

int main(int argc, const char *argv[])
{
    if(argc!=5) {
       fprintf(stderr,"Insufficient arguments\n");
       return 1;
    }

    int shmid;
    Shared *shm;

    pid_t pid;
    parent_pid = getpid();

    //shared memory allocation
    if((shmid = shmget(IPC_PRIVATE, sizeof(Shared), IPC_CREAT | 0666)) < 0)
        perror_exit("shmget");

    //attaching shared memory to process
    if((shm = shmat(shmid, NULL, 0)) == (void *) -1)
        perror_exit("shmat");

    long options[4];
    parse_input(argv, options);

    make_shared(shm, options[0], options[1], options[2], options[3]);

    //signal handling function assignment
    signal(SIGINT, error_signal_handler);
    signal(SIGUSR1, error_signal_handler);

    int genCounter=0;

    //forking of the generators
    for(int i = 0; i<2; ++i) {
        pid = fork();
        if(pid < 0)
            perror_exit("fork");
        else if(pid==0) {
            if(genCounter==0)
                generate_oxygen(shm);
            else
                generate_hydrogen(shm);
            int finishCount=0;
            while(wait(NULL)) {
                if(errno == ECHILD)
                    break;
                ++finishCount;
            }
            exit(0);
        }
        ++genCounter;
    }

    //waiting for all child processes to finish
    int finishCount=0;
    while(wait(NULL)) {
        if(errno == ECHILD)
            break;
        ++finishCount;
    }

    //closing output file
    fclose(shm->outputFile);
    //closing semaphores
    close_semaphores(shm);

    //detaching and deallocating shared memory
    shmdt((void *)shm);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
