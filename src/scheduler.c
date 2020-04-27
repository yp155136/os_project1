#include "scheduler.h"

int get_policy() {
    // 1 --> FIFO
    // 2 --> SJF
    // 3 --> RR
    // 4 --> PSJF
    char str[10];
    assert(scanf("%s", str) == 1);
    if (strcmp(str, "FIFO") == 0) {
        return 1;
    }
    else if (strcmp(str, "SJF") == 0) {
        return 2;
    }
    else if (strcmp(str, "RR") == 0) {
        return 3;
    }
    else if (strcmp(str, "PSJF") == 0) {
        return 4;
    }
    else {
        fprintf(stderr, "Unknown policy %s\n", str);
        assert(0);
    }
}

int main () {
    int policy = get_policy();

    int n; assert(scanf("%d", &n) == 1);

    struct Process p[n];
    for (int i = 0; i < n; ++i) {
        assert(scanf("%s %d %d", p[i].name, &p[i].ready_time, &p[i].exec_time) == 3);
        p[i].id = i;
        p[i].running = 0;
        p[i].forked = 0;
    }

    qsort(p, n, sizeof(struct Process), cmp_process);

    for (int i = 0; i < n; ++i) {
        p[i].id2 = i;
    }

    set_cpu(getpid(), 0);

    if (policy == 1) {
        go_fifo(n, p);
    }
    else if (policy == 2) {
        go_sjf(n, p);
    }
    else if (policy == 3) {
        go_rr(n, p);
    }
    else if (policy == 4) {
        go_psjf(n, p);
    }

}
