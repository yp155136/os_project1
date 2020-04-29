#include "SJF.h"

void go_sjf(int n, struct Process* p) {
    // shortest job first scheduler
    struct Queue *waiting_queue = calloc(1, sizeof(struct Queue)); // collect
    init_queue(waiting_queue);
    struct Treap* root = NULL; // merge-split treap(one kind of balanced binary search tree) to save the processes
    int ptr = 0;
    int updated = -1; // if one process is finished
    // here I use one trick
    // I only stored the available process in treap, stored the unavailable process in queue
    // when one process is finished, it pops all elements in queue and stored them in treap!
    for (int now_time = 0; ; now_time++) {
        while (ptr < n && p[ptr].ready_time == now_time) {
            // the same as it is in FIFO
            start_process(&p[ptr]);
            push(waiting_queue, &p[ptr]);
            ++ptr;
        }

        if (root == NULL || updated == 1) {
            // put all the elements in queue into the treap
            while (empty(waiting_queue) == 0) {
                struct Process *tmp = front(waiting_queue);
                pop(waiting_queue);
                insert_new(&root, tmp->exec_time, tmp->id2);
            }
            if (root != NULL) {
                int id = do_begin(root);
                set_pri(&p[id], p[id].pid, 1);
            }
        }

        UNIT_TIME
        updated = 0;

        if (root != NULL) {
            // execute the first element in treap
            int id = do_begin(root);
            p[id].exec_time--;
            if (p[id].exec_time == 0) {
                // finish the process, set updated to 1
                wait(0);
                pop_begin(&root);
                updated = 1;
            }
        }

        if (root == NULL && ptr == n && empty(waiting_queue)) {
            // all processes are forked and executed
            break;
        }
    }
}
