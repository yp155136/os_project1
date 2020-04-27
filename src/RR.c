#include "RR.h"

#define TIME_QUANTUM 500

void go_rr(int n, struct Process *p) {
    struct Queue *waiting_queue = calloc(1, sizeof(struct Queue));
    init_queue(waiting_queue);
    int ptr = 0;
    int run_id = -1;
    int left = -1;
    for (int now_time = 0; ; now_time++) {
        // if (now_time % 500 == 0) fprintf(stderr, "now_t = %d, %d, %d\n", now_time, run_id, ptr);
        while (ptr < n && p[ptr].ready_time == now_time) {
            start_process(&p[ptr]);
            push(waiting_queue, &p[ptr]);
            ++ptr;
        }

        if (run_id == -1) {
            if (empty(waiting_queue) == 0) {
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
                set_pri(&p[run_id], p[run_id].pid, 0);
                if (left == 0 && p[run_id].exec_time != 0) {
                    push(waiting_queue, &p[run_id]);
                }
                else if (p[run_id].exec_time == 0) {
                    wait(0);
                }
                run_id = -1;
            }
        }

        if (run_id == -1 && empty(waiting_queue) == 1 && ptr == n) break;
    }
}
