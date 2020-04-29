#include "RR.h"

#define TIME_QUANTUM 500
// time quantum in the RR algorithm

void go_rr(int n, struct Process *p) {
    // RR's scheduler algorithm
    struct Queue *waiting_queue = calloc(1, sizeof(struct Queue)); // queue in the RR algorithm
    init_queue(waiting_queue);
    int ptr = 0;
    int run_id = -1; // current running process id
    int left = -1; // the time that p[run_id] process can do
    for (int now_time = 0; ; now_time++) {
        while (ptr < n && p[ptr].ready_time == now_time) {
            // push all available processes into the queue
            start_process(&p[ptr]);
            push(waiting_queue, &p[ptr]);
            ++ptr;
        }

        if (run_id == -1) {
            if (empty(waiting_queue) == 0) {
                // no process is running and there is some process in the queue
                struct Process *tmp = front(waiting_queue);
                pop(waiting_queue);
                run_id = tmp->id2;
                left = TIME_QUANTUM;
                set_pri(tmp, tmp->pid, 1);
            }
        }

        UNIT_TIME

        if (run_id != -1) {
            left--;
            p[run_id].exec_time--;
            if (p[run_id].exec_time == 0 || left == 0) {
                // either the process is finished or it has already executed a time quantum
                set_pri(&p[run_id], p[run_id].pid, 0);
                if (left == 0 && p[run_id].exec_time != 0) {
                    // has something left to do --> put it in the back of the queue
                    push(waiting_queue, &p[run_id]);
                }
                else if (p[run_id].exec_time == 0) {
                    // finished
                    wait(0);
                }
                run_id = -1;
            }
        }

        if (run_id == -1 && empty(waiting_queue) == 1 && ptr == n) {
            // all processes are forked and executed
            break;
        }
    }
}
