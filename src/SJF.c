#include "SJF.h"

void go_sjf(int n, struct Process* p) {
    struct Queue *waiting_queue = calloc(1, sizeof(struct Queue));
    init_queue(waiting_queue);
    struct Treap* root = NULL;
    int ptr = 0;
    for (int now_time = 0; ; now_time++) {
        // fprintf(stderr, "now_time = %d\n", now_time);
        while (ptr < n && p[ptr].ready_time == now_time) {
            start_process(&p[ptr]);
            push(waiting_queue, &p[ptr]);
            ++ptr;
        }

        if (root == NULL) {
            // fprintf(stderr, "now_time = %d\n", now_time);
            while (empty(waiting_queue) == 0) {
                struct Process *tmp = front(waiting_queue);
                pop(waiting_queue);
                insert_new(&root, tmp->exec_time, tmp->id2);
            }
            // fprintf(stderr, "finish insert\n");
            if (root != NULL) {
                int id = do_begin(root);
                // fprintf(stderr, "do_begin id = %d\n", id);
                set_pri(&p[id], p[id].pid, 1);
            }
        }

        UNIT_TIME

        if (root != NULL) {
            int id = do_begin(root);
            p[id].exec_time--;
            if (p[id].exec_time == 0) {
                wait(0);
                pop_begin(&root);
                // fprintf(stderr, "now_time = %d\n", now_time);
                while (empty(waiting_queue) == 0) {
                    struct Process *tmp = front(waiting_queue);
                    pop(waiting_queue);
                    insert_new(&root, tmp->exec_time, tmp->id2);
                }
                // fprintf(stderr, "finish insert\n");
                if (root != NULL) {
                    int idd = do_begin(root);
                    // fprintf(stderr, "do_begin id = %d\n", idd);
                    set_pri(&p[idd], p[idd].pid, 1);
                }
            }
        }

        if (root == NULL && ptr == n && empty(waiting_queue)) break;
    }
}
