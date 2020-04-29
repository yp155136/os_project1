#include "FIFO.h"

void go_fifo(int n, struct Process *p) {
    // FIFO policy
    int ptr = 0;
    struct Process *running_process = NULL;
    struct Queue *waiting_queue = calloc(1, sizeof(struct Queue));
    init_queue(waiting_queue);
    for (int now_time = 0; ; now_time++) {
        while (ptr < n && p[ptr].ready_time == now_time) {
            // put all the available process into the ready queue
            start_process(&p[ptr]);
            push(waiting_queue, &p[ptr]);
            ++ptr;
        }

        
        if (running_process != NULL) {
            if (running_process->exec_time == 0) {
                // finish processing
                wait(0);
                running_process = NULL;
            }
        }
        

        if (running_process == NULL && empty(waiting_queue) == 0) {
            // pop the front element of the ready queue to execute
            struct Process *tmp = front(waiting_queue);
            pop(waiting_queue);
            set_pri(tmp, tmp->pid, 1);
            running_process = tmp;
        }

        if (running_process == NULL && empty(waiting_queue) == 1 && ptr == n) {
            // all processed are executed and finished
            // exit the scheduler
            break;
        }

        UNIT_TIME

        if (running_process != NULL) {
            running_process->exec_time--;
        }
    }
}
