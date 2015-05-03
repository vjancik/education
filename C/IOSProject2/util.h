#ifndef UTIL_H_
#define UTIL_H_

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

//macro to deal with "unused parameter" warning in signal handling function
#define UNUSED(x) (void)(x)

//main process PID
pid_t parent_pid;

void perror_exit(char *s);

void *check_malloc(int size);

int random_interval(int limit);

sem_t *make_semaphore(const char* name, int n);

int sem_signal(sem_t *sem);

int parse_input(const char *argv[], long *options);

void error_signal_handler(int signum);

#endif
