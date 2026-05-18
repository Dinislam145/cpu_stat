#include <stdio.h>

#include "threads/thread_control.h"
#include "cpu_monitor/cpu_monitor.h"
#include "network/exchange/protocols.h"
#include "udp_monitor/udp_monitor.h"
#include "network/udp_sender.h"

int main()
{
  printf("Hello World!\n");

  struct cpu_stat_protocol protocol;
  init_cpu_stat_protocol(&protocol);

  struct thread_context stat_thread;
  //struct thread_context udp_thread;



  struct ProcStatArgs proc_stat_args;
  init_proc_stat_args(&proc_stat_args);
  proc_stat_args.target_buff = &protocol;
  init_thread_context(&stat_thread, "PROC_STAT_THREAD", &proc_stat_args, &proc_stat_loop);
  create_thread(&stat_thread);



  //struct UdpExchangeArgs udp_exch_args;
  //init_udp_exchange_args(&udp_exch_args);

  //struct UdpClient udp_client;
  //bool initing_client = init_udp_client(&udp_client, 1234, "127.0.0.1");

  //udp_exch_args.source_buf = &protocol;
  //udp_exch_args.client = &udp_client;
  //init_thread_context(&udp_thread, "PROC_STAT_THREAD", &udp_exch_args, &udp_exchange_loop);
  //create_thread(&udp_thread);



  pthread_join(stat_thread.thread, NULL);
  //pthread_join(udp_thread.thread, NULL);

  //close_udp_client(&udp_client);

  return 0;
}
