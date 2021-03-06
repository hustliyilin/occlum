#define _GNU_SOURCE
#include <sched.h>
#include <unistd.h>
#include "ocalls.h"

int occlum_ocall_sched_getaffinity(size_t cpusize, unsigned char* buf) {
    int ret;
    cpu_set_t mask;
    CPU_ZERO(&mask);

    ret = syscall(__NR_sched_getaffinity, gettid(), sizeof(cpu_set_t), &mask);
    memcpy(buf, &mask, cpusize);
    return ret;
}

int occlum_ocall_sched_setaffinity(int host_tid, size_t cpusize, const unsigned char* buf) {
    return syscall(__NR_sched_setaffinity, host_tid, cpusize, buf);
}

/* In the Linux implementation, sched_yield() always succeeds */
void occlum_ocall_sched_yield(void) {
    sched_yield();
}

int occlum_ocall_ncores(void) {
    return sysconf(_SC_NPROCESSORS_CONF);
}
