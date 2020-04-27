#include "PSJF.h"

void go_psjf(int n, struct Process *p) {
    struct Treap* root = NULL;
    int ptr = 0;
    int last_id = -1;
    for (int now_time = 0; ; now_time++) {
        // if (now_time % 1000 == 0) fprintf(stderr, "now_t = %d\n", now_time);
        while (ptr < n && p[ptr].ready_time == now_time) {
            start_process(&p[ptr]);
            insert_new(&root, p[ptr].exec_time, ptr);
            ptr++;
        }

        UNIT_TIME

        if (root != NULL) {
            int id = do_begin(root);
            if (last_id != -1 && last_id != id) {
                set_pri(&p[last_id], p[last_id].pid, 0);
            }
            p[id].exec_time--;
            if (last_id != id) set_pri(&p[id], p[id].pid, 1);
            // if (now_time % 1000 == 0) fprintf(stderr, "id = %d, run = %d\n", id, p[id].exec_time);
            if (p[id].exec_time == 0) {
                wait(0);
                pop_begin(&root);
                id = -1;
            }
            last_id = id;
        }

        if (root == NULL && ptr == n) break;
    }
}
