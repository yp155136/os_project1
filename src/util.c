#include "util.h"

int cmp_process(const void *aa, const void *bb) {
    struct Process *a = (struct Process*)aa, *b = (struct Process*)bb;
    if (a->ready_time > b->ready_time) {
        return 1;
    }
    else if (a->ready_time < b->ready_time) {
        return -1;
    }

    if (a->id > b->id) {
        return 1;
    }
    else if (a->id < b->id){
        return -1;
    }

    fprintf(stderr, "unknown result compare\n");
    assert(0);
} 

void set_cpu(pid_t pid, int cpu_id) {
    cpu_set_t cpu;
    CPU_ZERO(&cpu);
    CPU_SET(cpu_id, &cpu);

    if (sched_setaffinity(pid, sizeof(cpu), &cpu)) {
        fprintf(stderr, "CPU set error");
        assert(0);
    }
}

void set_pri(struct Process *p, pid_t pid, int type) {
    // type == 0: lowest
    // type == 1: highest
    struct sched_param param;
    // fprintf(stderr, "forked = %d, type = %d, pid = %d\n", p->forked, type, pid);
    if (type == 0 && p->forked == 0) return;
    else if (type == 0) {
        // param.sched_priority = 0;
        // sched_setscheduler(pid, SCHED_IDLE, &param);
        // return;
        
        param.sched_priority = sched_get_priority_min(SCHED_FIFO);
        // param.sched_priority = 1;
        p->running = 0;
    }
    else if (type == 1) {
        if (p->forked == 0) {
            real_start_process(&p);
            // fprintf(stderr, "forked\n");
        }
        // param.sched_priority = 0;
        // sched_setscheduler(pid, SCHED_OTHER, &param);
        
        param.sched_priority = sched_get_priority_max(SCHED_FIFO);
        p->running = 1;
    }
    // fprintf(stderr, "pid = %d, type = %d, pri = %d\n", pid, type, param.sched_priority);
    pid = p->pid;
    if (sched_setscheduler(pid, SCHED_FIFO, &param)) {
        fprintf(stderr, "set prioirty fail\n");
        assert(0);
    }
}

void real_start_process(struct Process **p) {
    // fprintf(stderr, "start process %d\n", p->id);

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "fork error");
        assert(0);
    }
    else if (pid == 0) {
        // parent process
        struct timespec st, ed;
        syscall(334, &st);
        
        for (int i = 0; i < (*p)->exec_time; ++i) {
            UNIT_TIME
        }
        // int status; wait(&status);
        syscall(334, &ed);
        syscall(335, getpid(), st.tv_sec, st.tv_nsec, ed.tv_sec, ed.tv_nsec);

        // p->running = 0;
        // p->id = 7122;
        // fprintf(stderr, "wwwwwww p->id = %d, addr = %p, run = %d\n", p->id, &(*p), p->running);
        // fflush(stderr);
        exit(0);
    }
    else if (pid > 0) {
        // child process
        (*p)->pid = pid;
        (*p)->forked = 1;

        set_cpu(pid, 1);
        // set_pri(p, pid, 0);

        printf("%s %d\n", (*p)->name, (*p)->pid);
        fflush(stdout);
        
        /* for (int i = 0; i < p->exec_time; ++i) {
            UNIT_TIME
        } */

    }
}

void start_process(struct Process *p) {
    return;
    // fprintf(stderr, "start process %d\n", p->id);

    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "fork error");
        assert(0);
    }
    else if (pid == 0) {
        // parent process
        struct timespec st, ed;
        syscall(334, &st);
        
        for (int i = 0; i < p->exec_time; ++i) {
            UNIT_TIME
        }
        // int status; wait(&status);
        syscall(334, &ed);
        syscall(335, getpid(), st.tv_sec, st.tv_nsec, ed.tv_sec, ed.tv_nsec);

        // p->running = 0;
        // p->id = 7122;
        // fprintf(stderr, "wwwwwww p->id = %d, addr = %p, run = %d\n", p->id, &(*p), p->running);
        // fflush(stderr);
        exit(0);
    }
    else if (pid > 0) {
        // child process
        p->pid = pid;
        p->forked = 1;

        set_cpu(pid, 1);
        set_pri(p, pid, 0);

        printf("%s %d\n", p->name, p->pid);
        fflush(stdout);
        
        /* for (int i = 0; i < p->exec_time; ++i) {
            UNIT_TIME
        } */

    }
}

