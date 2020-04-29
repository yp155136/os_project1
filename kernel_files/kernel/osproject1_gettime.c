#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/timer.h>

asmlinkage void sys_osproject1_gettime(struct timespec *t) {
    getnstimeofday(t);
}
