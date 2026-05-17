#include <unistd.h>

#include "monitor.h"
#include "parser/stat_parser.h"
#include "threads/thread_control.h"

void proc_stat_loop(struct thread_context *thread){
  struct ProcStatArgs *arg = (struct ProcStatArgs*)(thread->arg);


  while(!atomic_load(&thread->stop)){
      stat_parser("/proc/stat");
      sleep(1);
  }

  thread->state = FINISHED;
}
