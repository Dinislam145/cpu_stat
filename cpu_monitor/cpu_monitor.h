#ifndef CPU_MONITOR_H
#define CPU_MONITOR_H

struct thread_context;
struct cpu_stat_protocol;

struct ProcStatArgs{
    struct cpu_stat_protocol *target_buff;
    void *mutex;
    void *cond_notify;
    bool *ready_to_send;
};

static inline void init_proc_stat_args(struct ProcStatArgs *target){
    if(target == nullptr){
        return;
    }

    target->target_buff = nullptr;
    target->mutex = nullptr;
    target->cond_notify = nullptr;
    target->ready_to_send = nullptr;
}

void proc_stat_loop(struct thread_context *thread);

#endif // CPU_MONITOR_H
