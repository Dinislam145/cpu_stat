#include <unistd.h>

#include "cpu_monitor.h"
#include "parser/stat_parser.h"
#include "threads/thread_control.h"

void proc_stat_loop(struct thread_context *thread){
  struct ProcStatArgs *arg = (struct ProcStatArgs*)(thread->arg);

  struct CpuStat cpu_stat;

  while(!atomic_load(&thread->stop)){
      init_cpu_stat(&cpu_stat);
      stat_parser("/proc/stat", &cpu_stat);
      debug_cpu_stat(&cpu_stat);
      sleep(1);
  }

  thread->state = FINISHED;
}
