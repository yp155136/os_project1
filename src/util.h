#ifndef _UTIL_H_
#define _UTIL_H_

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sched.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/syscall.h>

#define UNIT_TIME { volatile unsigned long ii; for(ii=0;ii<1000000UL;ii++); } 

#define MAX_PROCESS_NAME 31

struct Process {
    char name[ MAX_PROCESS_NAME + 1 ]; // name
    int ready_time; // ready time
    int exec_time; // execution time
    int id; // index of the input
    int id2; // index of sorted input
    pid_t pid; // process id

    int running; // running or not
    int forked; // forked or not
};

int cmp_process(const void* aa, const void* bb);

void set_cpu(pid_t pid, int cpu_id);

void set_pri(struct Process *p, pid_t pid, int type);

void real_start_process(struct Process **p);

void start_process(struct Process *p);

#endif // _UTIL_H 
