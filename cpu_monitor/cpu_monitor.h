#ifndef CPU_MONITOR_H
#define CPU_MONITOR_H

struct thread_context;

struct ProcStatArgs{
    char *target_buff;
};

static inline void init_proc_stat_args(struct ProcStatArgs *target){
    if(target == nullptr){
        return;
    }

    target->target_buff = nullptr;
}

void proc_stat_loop(struct thread_context *thread);

#endif // CPU_MONITOR_H
