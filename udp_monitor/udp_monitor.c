#include "udp_monitor.h"

#include "threads/thread_control.h"
#include "network/udp_sender.h"

void udp_exchange_loop(struct thread_context *thread){
  struct UdpExchangeArgs *arg = (struct UdpExchangeArgs*)(thread->arg);

  while(!atomic_load(&thread->stop)){

  }

  thread->state = FINISHED;
}
