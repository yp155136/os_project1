#include "FIFO.h"

void go_fifo(int n, struct Process *p) {
    // fprintf(stderr, "start fifo\n");
    // fflush(stderr);
    int ptr = 0;
    struct Process *running_process = NULL;
    struct Queue *waiting_queue = calloc(1, sizeof(struct Queue));
    init_queue(waiting_queue);
    for (int now_time = 0; ; now_time++) {
        // fprintf(stderr, "now_time = %d, ptr = %d\n", now_time, ptr);
        // fflush(stderr);
        // if (now_time % 5000 == 0) fprintf(stderr, "now_time = %d\n", now_time);
        while (ptr < n && p[ptr].ready_time == now_time) {
            start_process(&p[ptr]);
            push(waiting_queue, &p[ptr]);
            ++ptr;
        }

        
        if (running_process != NULL) {
            // fprintf(stderr, "now_t = %d, someone is running\n", now_time);
            // fflush(stderr);
            // if (now_time % 100 == 0) fprintf(stderr, "id = %d, running = %d, addr = %p\n", running_process->id, running_process->running, &(*running_process));
            if (running_process->exec_time == 0) {
                // finish processing
                wait(0);
                running_process = NULL;
            }
        }
        

        if (running_process == NULL && empty(waiting_queue) == 0) {
            // fprintf(stderr, "ready to put a pid in waiting queue into running queue, now_t = %d\n", now_time);
            // fflush(stderr);
            struct Process *tmp = front(waiting_queue);
            pop(waiting_queue);
            set_pri(tmp, tmp->pid, 1);
            running_process = tmp;
        }

        if (running_process == NULL && empty(waiting_queue) == 1 && ptr == n) break;

        UNIT_TIME

        if (running_process != NULL) {
            running_process->exec_time--;
        }
    }
}
