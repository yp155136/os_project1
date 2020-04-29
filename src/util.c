#include "util.h"

int cmp_process(const void *aa, const void *bb) {
    // sort the process by ready time
    // if ready time is the same, then sort by their order in the input
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
    // let process pid runs in cpu_id
    cpu_set_t cpu;
    CPU_ZERO(&cpu);
    CPU_SET(cpu_id, &cpu);

    if (sched_setaffinity(pid, sizeof(cpu), &cpu)) {
        fprintf(stderr, "CPU set error");
        assert(0);
    }
}

void set_pri(struct Process *p, pid_t pid, int type) {
    // set process p to the corresponding weight
    // type == 0: lowest weight
    // type == 1: highest weight
    struct sched_param param;
    if (type == 0 && p->forked == 0) {
        // if it is not forked and the priority is low, then I don't need to do anything
        return;
    }
    else if (type == 0) {
        // set to the lowest priority
        param.sched_priority = sched_get_priority_min(SCHED_FIFO);
    }
    else if (type == 1) {
        // set to high priority
        if (p->forked == 0) {
            // if it is not forked, fork it
            real_start_process(&p);
        }
        param.sched_priority = sched_get_priority_max(SCHED_FIFO);
    }
    pid = p->pid;
    if (sched_setscheduler(pid, SCHED_FIFO, &param)) {
        fprintf(stderr, "set prioirty fail\n");
        assert(0);
    }
}

void real_start_process(struct Process **p) {
    // fork the process
    pid_t pid = fork();

    if (pid < 0) {
        fprintf(stderr, "fork error");
        assert(0);
    }
    else if (pid == 0) {
        // child process
        struct timespec st, ed;
        syscall(334, &st);
        
        for (int i = 0; i < (*p)->exec_time; ++i) {
            UNIT_TIME
        }

        syscall(334, &ed);
        syscall(335, getpid(), st.tv_sec, st.tv_nsec, ed.tv_sec, ed.tv_nsec);

        exit(0);
    }
    else if (pid > 0) {
        // parent process
        (*p)->pid = pid;
        (*p)->forked = 1;

        set_cpu(pid, 1);

        printf("%s %d\n", (*p)->name, (*p)->pid);
        fflush(stdout);
    }
}

void start_process(struct Process *p) {
    // based on my design, this function needs to do nothing
    // but if you want to change it to "what real process looks like to do", you can delete line 103
    return;

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
        syscall(334, &ed);
        syscall(335, getpid(), st.tv_sec, st.tv_nsec, ed.tv_sec, ed.tv_nsec);

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
    }
}

