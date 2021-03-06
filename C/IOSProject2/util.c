#include "util.h"

//perror with exit wrapper function
void perror_exit(char *s) {
    perror(s);
    kill(-parent_pid, SIGUSR1);
    exit(2);
}

//malloc with checking shortcut function
void *check_malloc(int size){
    void *p = malloc(size);
    if(p == NULL) perror_exit("malloc_failed");
    return p;
}

//random interval generator
int random_interval(int limit) {
    return (rand() % (limit+1))*1000;
}

//semaphore creation abstraction function
sem_t *make_semaphore(const char* name, int n) {
    sem_t *sem;
    sem=sem_open(name, O_CREAT | O_EXCL, 0644, n);
    return sem;
}

//sem_post alias function
int sem_signal(sem_t *sem) {
    return sem_post(sem);
}

//input handling function
int parse_input(const char *argv[], long *options) {
    char *rest;
    int restLen = 0;

    long atomNum = strtol(argv[1],&rest, 10);
    restLen += strlen(rest);
    long hydroGenTime = strtol(argv[2], &rest, 10);
    restLen += strlen(rest);
    long oxyGenTime = strtol(argv[3], &rest, 10);
    restLen += strlen(rest);
    long bondTime = strtol(argv[4], &rest, 10);
    restLen += strlen(rest);

    if(restLen!=0) return 1; //checks for nonnumeric components

    //range checking
    if(atomNum         <= 0 ||
       hydroGenTime     < 0 ||
       hydroGenTime >= 5001 ||
       oxyGenTime       < 0 ||
       oxyGenTime   >= 5001 ||
       bondTime         < 0 ||
       bondTime     >= 5001   )
    {
        return 1;
    }

    //connects input arguments with corresponding program options
    options[0] = atomNum;
    options[1] = hydroGenTime;
    options[2] = oxyGenTime;
    options[3] = bondTime;
    return 0;
}

//signal handling function for killing all processes in the group
void error_signal_handler(int signum) {
    UNUSED(signum);
    if(getpid() != parent_pid) {
        exit(2);
    }
}
