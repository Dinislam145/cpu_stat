#include <unistd.h>
#include <stdlib.h>

#include "cpu_monitor.h"
#include "parser/stat_parser.h"
#include "threads/thread_control.h"
#include "network/exchange/protocols.h"

void fill_protocol(struct cpu_stat_protocol *target, const struct CpuStat *source){
  if(!target || !source){
    return;
  }

  target->cores_count = source->cores_count;
  //free(target->cores_stat);
  //target->cores_stat = malloc((1 + target->cores_count) * sizeof(struct core_stat_protocol));

  for(int i = 0; i <= target->cores_count; i++){
    target->cores_stat[i].user = source->cores_stat[i].user;
    target->cores_stat[i].nice = source->cores_stat[i].nice;
    target->cores_stat[i].system = source->cores_stat[i].system;
    target->cores_stat[i].idle = source->cores_stat[i].idle;
    target->cores_stat[i].iowait = source->cores_stat[i].iowait;
    target->cores_stat[i].irq = source->cores_stat[i].irq;
    target->cores_stat[i].softirq = source->cores_stat[i].softirq;
    target->cores_stat[i].steal = source->cores_stat[i].steal;
    target->cores_stat[i].guest = source->cores_stat[i].guest;
    target->cores_stat[i].guest_nice = source->cores_stat[i].guest_nice;
  }
}

void proc_stat_loop(struct thread_context *thread){
  struct ProcStatArgs *arg = (struct ProcStatArgs*)(thread->arg);

  struct CpuStat cpu_stat;

  init_cpu_stat(&cpu_stat);
  stat_parser("/proc/stat", &cpu_stat);
  free(arg->target_buff->cores_stat);
  arg->target_buff->cores_stat = malloc((1 + cpu_stat.cores_count) * sizeof(struct core_stat_protocol));
  fill_protocol(arg->target_buff, &cpu_stat);
  debug_cpu_stat(&cpu_stat);

  while(!atomic_load(&thread->stop)){
    sleep(1);
    init_cpu_stat(&cpu_stat);
    stat_parser("/proc/stat", &cpu_stat);
    fill_protocol(arg->target_buff, &cpu_stat);
    debug_cpu_stat(&cpu_stat);
  }

  thread->state = FINISHED;
}
