#include <stdio.h>

#include "udp_monitor.h"
#include "threads/thread_control.h"
#include "network/udp_sender.h"
#include "network/exchange/protocols.h"

void udp_exchange_loop(struct thread_context *thread){
  struct UdpExchangeArgs *arg = (struct UdpExchangeArgs*)(thread->arg);

  while(!atomic_load(&thread->stop)){
    char *msg = pack_cpu_stat(arg->source_buf);
    int bytes_sent = send_msg(arg->client, msg, size_cpu_stat(arg->source_buf));

    printf("Sent %d bytes!\n", bytes_sent);
  }

  thread->state = FINISHED;
}
