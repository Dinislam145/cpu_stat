#ifndef MONITOR_H
#define MONITOR_H

struct thread_context;

struct ProcStatArgs{
    char *target_buff;
};

static inline void init_proc_stat_args(struct ProcStatArgs *target){
    if(target == NULL){
        return;
    }
    target->target_buff = NULL;
}

void proc_stat_loop(struct thread_context *thread);

#endif // MONITOR_H
