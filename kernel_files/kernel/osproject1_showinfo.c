#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/timer.h>

asmlinkage void sys_osproject1_showinfo(int pid, long st_sec, long st_nsec, long ed_sec, long ed_nsec) {
    printk("[Project 1] %d %ld.%09ld %ld.%09ld\n", pid, st_sec, st_nsec, ed_sec, ed_nsec);
}
