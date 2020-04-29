#include "PSJF.h"

void go_psjf(int n, struct Process *p) {
    // preemptive shortest job first algorithm
    struct Treap* root = NULL; // the merge-split treap (balanced binary search tree) to store all the processes
    int ptr = 0;
    int last_id = -1; // record the last time unit's running processing id
    for (int now_time = 0; ; now_time++) {
        while (ptr < n && p[ptr].ready_time == now_time) {
            // same as FIFO, SJF, RR
            // the only difference is that I put all the processes into the treap
            start_process(&p[ptr]);
            insert_new(&root, p[ptr].exec_time, ptr);
            ptr++;
        }

        UNIT_TIME

        if (root != NULL) {
            int id = do_begin(root);
            if (last_id != -1 && last_id != id) {
                // the running process now and the running process in the last time unit is not the same 
                // --> set the last time unit's running process's prioirty to low
                set_pri(&p[last_id], p[last_id].pid, 0);
            }
            p[id].exec_time--;
            if (last_id != id) set_pri(&p[id], p[id].pid, 1); // set this process's priority to high
            if (p[id].exec_time == 0) {
                // the process is finished
                wait(0);
                pop_begin(&root);
                id = -1;
            }
            last_id = id;
        }

        if (root == NULL && ptr == n) { 
            // all processes are forked and executed, Hooray!!!
            break;
        }
    }
}
