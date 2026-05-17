#include <stdio.h>

#include "threads/thread_control.h"
#include "cpu_monitor/monitor.h"

int main()
{
  printf("Hello World!\n");

  struct ProcStatArgs args;
  init_proc_stat_args(&args);

  struct thread_context stat_thread;

  init_thread_context(&stat_thread, "PROC_STAT_THREAD", &args, &proc_stat_loop);
  create_thread(&stat_thread);

  pthread_join(stat_thread.thread, NULL);

  return 0;
}
