#include <stdio.h>

#include "threads/thread_control.h"
#include "cpu_monitor/cpu_monitor.h"
#include "network/exchange/protocols.h"
#include "udp_monitor/udp_monitor.h"
#include "network/udp_sender.h"

int main()
{
  printf("Hello World!\n");

  bool ready_udp_send = false;

  struct cpu_stat_protocol protocol;
  init_cpu_stat_protocol(&protocol);

  struct thread_context stat_thread;
  struct thread_context udp_thread;

  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;

  struct ProcStatArgs proc_stat_args;
  init_proc_stat_args(&proc_stat_args);
  proc_stat_args.target_buff = &protocol;
  proc_stat_args.mutex = &mutex;
  proc_stat_args.cond_notify = &cond_var;
  proc_stat_args.ready_to_send = &ready_udp_send;
  init_thread_context(&stat_thread, "PROC_STAT_THREAD", &proc_stat_args, &proc_stat_loop);
  create_thread(&stat_thread);



  struct UdpExchangeArgs udp_exch_args;
  init_udp_exchange_args(&udp_exch_args);

  struct UdpClient udp_client;
  bool initing_client = init_udp_client(&udp_client, 1234, "192.168.31.65");
  if(!initing_client){
    printf("Failed to init UDP client with target port %d and ip %s", 1234, "192.168.31.65");
    return 1;
  }

  udp_exch_args.source_buf = &protocol;
  udp_exch_args.client = &udp_client;
  udp_exch_args.mutex = &mutex;
  udp_exch_args.cond_wait = &cond_var;
  udp_exch_args.ready_to_send = &ready_udp_send;
  init_thread_context(&udp_thread, "PROC_STAT_THREAD", &udp_exch_args, &udp_exchange_loop);
  create_thread(&udp_thread);



  pthread_join(stat_thread.thread, NULL);
  pthread_join(udp_thread.thread, NULL);

  close_udp_client(&udp_client);

  return 0;
}
